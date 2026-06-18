#include "PropertiesDialog.h"
#include "ui_PropertiesDialog.h"
#include "Rectangle.h"
#include "Ellipse.h"
#include "Triangle.h"
#include "Polygon.h"
#include "Curve.h"
#include <QApplication>
#include <QColorDialog>
#include <QPainter>
#include <QPainterPath>
#include <QTimer>
#include <QtMath>

PropertiesDialog::PropertiesDialog(Shape* shape, QWidget* parent)
    : QDialog(parent),
      ui(new Ui::PropertiesDialog),
      m_shape(shape),
      m_isCreateMode(false),
      m_createShapeType(Shape::Rectangle),
      m_penWidth(2),
      m_centerX(0),
      m_centerY(0),
      m_width(100),
      m_height(80),
      m_pointCount(0)
{
    ui->setupUi(this);
    initCommon();

    QPushButton* okBtn = ui->buttonBox->button(QDialogButtonBox::Ok);
    QPushButton* cancelBtn = ui->buttonBox->button(QDialogButtonBox::Cancel);
    if (okBtn) {
        okBtn->disconnect();
        connect(okBtn, &QPushButton::clicked, this, &PropertiesDialog::handleAccepted);
    }
    if (cancelBtn) {
        cancelBtn->disconnect();
        connect(cancelBtn, &QPushButton::clicked, this, &PropertiesDialog::on_buttonBox_rejected);
    }

    if (!shape) {
        return;
    }

    m_penColor = shape->penColor();
    m_brushColor = shape->brushColor();
    m_penWidth = shape->penWidth();
    QPointF center = shape->center();
    m_centerX = center.x();
    m_centerY = center.y();
    QRect br = shape->boundingRect();
    m_width = br.width();
    m_height = br.height();

    QString typeName;
    QString widthLabel;
    QString heightLabel;
    
    switch (shape->type()) {
    case Shape::Rectangle:
        typeName = "矩形";
        widthLabel = "宽";
        heightLabel = "高";
        break;
    case Shape::Ellipse:
        typeName = "椭圆";
        widthLabel = "长轴长";
        heightLabel = "短轴长";
        break;
    case Shape::Triangle:
        typeName = "三角形";
        widthLabel = "底边";
        heightLabel = "高";
        break;
    case Shape::Polygon:
        typeName = "多边形";
        widthLabel = "宽";
        heightLabel = "高";
        break;
    case Shape::Curve:
        typeName = "曲线";
        widthLabel = "控制点";
        heightLabel = "数量";
        break;
    default:
        typeName = "图形";
        widthLabel = "宽";
        heightLabel = "高";
    }
    
    ui->shapeTypeLabel->setText(QString("图形类型：%1").arg(typeName));
    ui->label_3->setText(widthLabel + "：");
    ui->label_4->setText(heightLabel + "：");

    ui->penWidthSpin->setValue(m_penWidth);
    ui->centerXSpin->setValue(m_centerX);
    ui->centerYSpin->setValue(m_centerY);
    ui->widthSpin->setValue(m_width);
    ui->heightSpin->setValue(m_height);

    updateColorButton(ui->penColorBtn, m_penColor);
    updateColorButton(ui->brushColorBtn, m_brushColor);

    setWindowTitle("图形属性");
}

PropertiesDialog::PropertiesDialog(Shape::ShapeType type, QWidget* parent)
    : QDialog(parent),
      ui(new Ui::PropertiesDialog),
      m_shape(nullptr),
      m_isCreateMode(true),
      m_createShapeType(type),
      m_penWidth(2),
      m_centerX(200),
      m_centerY(200),
      m_width(100),
      m_height(80),
      m_pointCount(0)
{
    ui->setupUi(this);
    initCommon();
    QPushButton* okBtn = ui->buttonBox->button(QDialogButtonBox::Ok);
    QPushButton* cancelBtn = ui->buttonBox->button(QDialogButtonBox::Cancel);
    if (okBtn) {
        okBtn->disconnect();
        connect(okBtn, &QPushButton::clicked, this, &PropertiesDialog::handleAccepted);
    }
    if (cancelBtn) {
        cancelBtn->disconnect();
        connect(cancelBtn, &QPushButton::clicked, this, &PropertiesDialog::on_buttonBox_rejected);
    }
    setupCreateMode(type);
}

PropertiesDialog::~PropertiesDialog() {
    delete ui;
}

void PropertiesDialog::initCommon() {
    m_penColor = Qt::black;
    m_brushColor = Qt::white;
}

void PropertiesDialog::setupCreateMode(Shape::ShapeType type) {
    // 显示类型标签，隐藏下拉框（用户已在工具栏选择类型）
    ui->shapeTypeCombo->setVisible(false);
    ui->shapeTypeLabel->setVisible(true);

    // 根据图形类型设置标签文本
    QString typeName;
    QString widthLabel;
    QString heightLabel;
    switch (type) {
    case Shape::Rectangle:
        typeName = "矩形"; widthLabel = "宽"; heightLabel = "高"; break;
    case Shape::Ellipse:
        typeName = "椭圆"; widthLabel = "长轴"; heightLabel = "短轴"; break;
    case Shape::Triangle:
        typeName = "三角形"; widthLabel = "底边"; heightLabel = "高"; break;
    case Shape::Polygon:
        typeName = "多边形"; widthLabel = "宽"; heightLabel = "高"; break;
    case Shape::Curve:
        typeName = "曲线"; widthLabel = "宽"; heightLabel = "高"; break;
    }

    ui->shapeTypeLabel->setText(QString("创建图形：%1").arg(typeName));
    ui->label_3->setText(widthLabel + "：");
    ui->label_4->setText(heightLabel + "：");

    setWindowTitle("创建" + typeName);

    m_penWidth = 2;
    m_centerX = 200;
    m_centerY = 200;
    m_width = 100;
    m_height = 80;

    ui->penWidthSpin->setValue(m_penWidth);
    ui->centerXSpin->setValue(m_centerX);
    ui->centerYSpin->setValue(m_centerY);
    ui->widthSpin->setValue(m_width);
    ui->heightSpin->setValue(m_height);

    updateColorButton(ui->penColorBtn, m_penColor);
    updateColorButton(ui->brushColorBtn, m_brushColor);
}

Shape* PropertiesDialog::createShapeByType(Shape::ShapeType type) {
    int left = qRound(m_centerX - m_width / 2);
    int top = qRound(m_centerY - m_height / 2);
    QRect rect(QPoint(left, top), QSize(qRound(m_width), qRound(m_height)));

    Shape* shape = nullptr;
    switch (type) {
    case Shape::Rectangle:
        shape = new Rectangle(rect);
        break;
    case Shape::Ellipse:
        shape = new Ellipse(rect);
        break;
    case Shape::Triangle: {
        QPoint p1(left, top);
        QPoint p2(left + qRound(m_width), top);
        QPoint p3(left + qRound(m_width / 2), top + qRound(m_height));
        shape = new Triangle(p1, p2, p3);
        break;
    }
    case Shape::Polygon: {
        QVector<QPoint> points;
        int cx = qRound(m_centerX);
        int cy = qRound(m_centerY);
        int rx = qRound(m_width / 2);
        int ry = qRound(m_height / 2);
        for (int i = 0; i < 6; ++i) {
            qreal angle = (2 * M_PI * i / 6) - M_PI / 2;
            points.append(QPoint(cx + qRound(rx * qCos(angle)),
                                 cy + qRound(ry * qSin(angle))));
        }
        shape = new Polygon(points);
        break;
    }
    case Shape::Curve: {
        QVector<QPoint> points;
        int cx = qRound(m_centerX);
        int cy = qRound(m_centerY);
        int w = qRound(m_width);
        points.append(QPoint(cx - w/2, cy));
        points.append(QPoint(cx - w/4, cy - qRound(m_height / 2)));
        points.append(QPoint(cx + w/4, cy + qRound(m_height / 2)));
        points.append(QPoint(cx + w/2, cy));
        shape = new Curve(points);
        break;
    }
    default:
        break;
    }

    if (shape) {
        shape->setPenColor(m_penColor);
        shape->setBrushColor(m_brushColor);
        shape->setPenWidth(m_penWidth);
    }

    return shape;
}

void PropertiesDialog::on_penColorBtn_clicked() {
    ui->penWidthSpin->setFocus();

    ui->penColorBtn->setEnabled(false);
    ui->brushColorBtn->setEnabled(false);
    QPushButton* okBtn = ui->buttonBox->button(QDialogButtonBox::Ok);
    QPushButton* cancelBtn = ui->buttonBox->button(QDialogButtonBox::Cancel);
    if (okBtn) okBtn->setEnabled(false);
    if (cancelBtn) cancelBtn->setEnabled(false);

    QColor color = QColorDialog::getColor(m_penColor, this, "选择线条颜色");

    if (color.isValid()) {
        m_penColor = color;
        updateColorButton(ui->penColorBtn, color);
    }

    QTimer::singleShot(100, this, [this]() {
        ui->penColorBtn->setEnabled(true);
        ui->brushColorBtn->setEnabled(true);
        QPushButton* okBtn = ui->buttonBox->button(QDialogButtonBox::Ok);
        QPushButton* cancelBtn = ui->buttonBox->button(QDialogButtonBox::Cancel);
        if (okBtn) okBtn->setEnabled(true);
        if (cancelBtn) cancelBtn->setEnabled(true);
    });
}

void PropertiesDialog::on_brushColorBtn_clicked() {
    ui->penWidthSpin->setFocus();

    ui->penColorBtn->setEnabled(false);
    ui->brushColorBtn->setEnabled(false);
    QPushButton* okBtn = ui->buttonBox->button(QDialogButtonBox::Ok);
    QPushButton* cancelBtn = ui->buttonBox->button(QDialogButtonBox::Cancel);
    if (okBtn) okBtn->setEnabled(false);
    if (cancelBtn) cancelBtn->setEnabled(false);

    QColor color = QColorDialog::getColor(m_brushColor, this, "选择填充颜色");

    if (color.isValid()) {
        m_brushColor = color;
        updateColorButton(ui->brushColorBtn, color);
    }

    QTimer::singleShot(100, this, [this]() {
        ui->penColorBtn->setEnabled(true);
        ui->brushColorBtn->setEnabled(true);
        QPushButton* okBtn = ui->buttonBox->button(QDialogButtonBox::Ok);
        QPushButton* cancelBtn = ui->buttonBox->button(QDialogButtonBox::Cancel);
        if (okBtn) okBtn->setEnabled(true);
        if (cancelBtn) cancelBtn->setEnabled(true);
    });
}

void PropertiesDialog::on_penWidthSpin_valueChanged(int value) {
    m_penWidth = value;
}

void PropertiesDialog::handleAccepted() {
    m_penWidth = ui->penWidthSpin->value();
    m_centerX = ui->centerXSpin->value();
    m_centerY = ui->centerYSpin->value();
    m_width = ui->widthSpin->value();
    m_height = ui->heightSpin->value();

    if (m_isCreateMode) {
        m_createShapeType = static_cast<Shape::ShapeType>(ui->shapeTypeCombo->currentIndex());
    }

    accept();
}

void PropertiesDialog::on_buttonBox_rejected() {
    reject();
}

void PropertiesDialog::on_shapeTypeCombo_currentIndexChanged(int index) {
    m_createShapeType = static_cast<Shape::ShapeType>(index);
}

void PropertiesDialog::applyTo(Shape* shape) {
    if (!shape) return;
    shape->setPenColor(m_penColor);
    shape->setBrushColor(m_brushColor);
    shape->setPenWidth(m_penWidth);

    QPointF oldCenter = shape->center();
    QPoint offset(m_centerX - oldCenter.x(), m_centerY - oldCenter.y());
    shape->translate(offset);

    QRect br = shape->boundingRect();
    if (br.width() > 0 && br.height() > 0 && (qAbs(m_width - br.width()) > 0.5 || qAbs(m_height - br.height()) > 0.5)) {
        qreal factor = qMax(m_width / br.width(), m_height / br.height());
        shape->scale(factor, QPoint(qRound(m_centerX), qRound(m_centerY)));
    }
}

Shape* PropertiesDialog::takeCreatedShape() {
    if (!m_isCreateMode) return nullptr;
    return createShapeByType(m_createShapeType);
}

void PropertiesDialog::updateColorButton(QPushButton* btn, const QColor& color) {
    btn->setText(color.name());
    btn->setStyleSheet(QString("background-color: %1; color: %2;")
                       .arg(color.name())
                       .arg(color.lightness() > 128 ? "black" : "white"));
}

QString PropertiesDialog::colorToStyleSheet(const QColor& color) const {
    return QString("background-color: %1;").arg(color.name());
}