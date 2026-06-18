#ifndef PROPERTIESDIALOG_H
#define PROPERTIESDIALOG_H

#include <QDialog>
#include <QPushButton>
#include "Shape.h"

namespace Ui {
class PropertiesDialog;
}

class PropertiesDialog : public QDialog {
    Q_OBJECT

public:
    // shape 为 nullptr 时为创建新图形模式
    explicit PropertiesDialog(Shape* shape, QWidget* parent = nullptr);
    // 创建新图形的构造函数，指定图形类型
    explicit PropertiesDialog(Shape::ShapeType type, QWidget* parent = nullptr);
    ~PropertiesDialog() override;

    // 应用修改到图形
    void applyTo(Shape* shape);

    // 获取创建的图形（创建模式使用）
    Shape* takeCreatedShape();

private slots:
    void on_penColorBtn_clicked();
    void on_brushColorBtn_clicked();
    void on_penWidthSpin_valueChanged(int value);
    void handleAccepted();
    void on_buttonBox_rejected();
    void on_shapeTypeCombo_currentIndexChanged(int index);

private:
    void initCommon();
    void setupCreateMode(Shape::ShapeType type);
    Shape* createShapeByType(Shape::ShapeType type);
    void updateColorButton(QPushButton* btn, const QColor& color);
    QString colorToStyleSheet(const QColor& color) const;

    Ui::PropertiesDialog* ui;
    Shape* m_shape;
    bool m_isCreateMode;
    Shape::ShapeType m_createShapeType;

    QColor m_penColor;
    QColor m_brushColor;
    int m_penWidth;
    qreal m_centerX;
    qreal m_centerY;
    qreal m_width;
    qreal m_height;
    int m_pointCount;
};

#endif