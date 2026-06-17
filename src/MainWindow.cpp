#include "MainWindow.h"
#include "FileManager.h"
#include <QColorDialog>
#include <QFileDialog>
#include <QInputDialog>
#include <QMessageBox>
#include <QListWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QIcon>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      m_penColor(Qt::black),
      m_fillColor(Qt::white),
      m_penWidth(2),
      m_translateDistance(10),
      m_rotateAngle(15)
{
    ui->setupUi(this);
    
    m_canvasManager = new CanvasManager();
    setupCanvasManager();
    setupTransformActions();
    setupCanvasList();
    setupIcons();
    
    m_drawActionGroup = new QActionGroup(this);
    m_drawActionGroup->addAction(ui->actionSelect);
    m_drawActionGroup->addAction(ui->actionTriangle);
    m_drawActionGroup->addAction(ui->actionRectangle);
    m_drawActionGroup->addAction(ui->actionEllipse);
    m_drawActionGroup->addAction(ui->actionPolygon);
    m_drawActionGroup->addAction(ui->actionCurve);
    
    ui->penWidthSpinBox->setValue(m_penWidth);
    
    m_canvasManager->addCanvas("Canvas 1");
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_actionNew_triggered() {
    if (!m_scene->shapes().isEmpty()) {
        QMessageBox::StandardButton reply = QMessageBox::question(this, "确认新建", 
            "当前画布有内容，确定要新建吗？",
            QMessageBox::Yes | QMessageBox::No);
        if (reply != QMessageBox::Yes) {
            return;
        }
    }
    m_scene->clear();
    statusBar()->showMessage("新建文件");
}

void MainWindow::on_actionOpen_triggered() {
    QString filePath = QFileDialog::getOpenFileName(this, "打开文件", "", 
        "矢量图形文件 (*.svg);;所有文件 (*.*)");
    
    if (!filePath.isEmpty()) {
        FileManager manager;
        manager.loadScene(m_scene, filePath);
        statusBar()->showMessage("打开文件: " + filePath);
    }
}

void MainWindow::on_actionSave_triggered() {
    QString filePath = QFileDialog::getSaveFileName(this, "保存文件", "", 
        "SVG文件 (*.svg);;所有文件 (*.*)");
    
    if (!filePath.isEmpty()) {
        FileManager manager;
        manager.saveScene(m_scene, filePath);
        statusBar()->showMessage("保存文件: " + filePath);
    }
}

void MainWindow::on_actionExit_triggered() {
    if (!m_scene->shapes().isEmpty()) {
        QMessageBox::StandardButton reply = QMessageBox::question(this, "确认退出", 
            "当前画布有内容，确定要退出吗？",
            QMessageBox::Yes | QMessageBox::No);
        if (reply != QMessageBox::Yes) {
            return;
        }
    }
    close();
}

void MainWindow::on_actionSelect_triggered() {
    m_view->setCurrentTool(GraphicsView::SelectTool);
    statusBar()->showMessage("选择工具 - 点击选择图形，拖拽移动");
}

void MainWindow::on_actionTriangle_triggered() {
    m_view->setCurrentTool(GraphicsView::DrawTriangle);
    statusBar()->showMessage("绘制三角形 - 拖拽鼠标绘制");
}

void MainWindow::on_actionRectangle_triggered() {
    m_view->setCurrentTool(GraphicsView::DrawRectangle);
    statusBar()->showMessage("绘制矩形 - 拖拽鼠标绘制");
}

void MainWindow::on_actionEllipse_triggered() {
    m_view->setCurrentTool(GraphicsView::DrawEllipse);
    statusBar()->showMessage("绘制椭圆 - 拖拽鼠标绘制");
}

void MainWindow::on_actionPolygon_triggered() {
    m_view->setCurrentTool(GraphicsView::DrawPolygon);
    statusBar()->showMessage("绘制多边形 - 点击添加顶点，右键完成");
}

void MainWindow::on_actionCurve_triggered() {
    m_view->setCurrentTool(GraphicsView::DrawCurve);
    statusBar()->showMessage("绘制曲线 - 点击添加控制点，右键完成");
}

void MainWindow::on_actionPenColor_triggered() {
    QColor color = QColorDialog::getColor(m_penColor, this, "选择线条颜色");
    if (color.isValid()) {
        m_penColor = color;
        m_view->setDrawColor(color);
        statusBar()->showMessage("线条颜色已设置");
    }
}

void MainWindow::on_actionFillColor_triggered() {
    QColor color = QColorDialog::getColor(m_fillColor, this, "选择填充颜色");
    if (color.isValid()) {
        m_fillColor = color;
        m_view->setFillColor(color);
        statusBar()->showMessage("填充颜色已设置");
    }
}

void MainWindow::on_penWidthSpinBox_valueChanged(int width) {
    m_penWidth = width;
    m_view->setPenWidth(width);
    statusBar()->showMessage("线条宽度: " + QString::number(width) + "px");
}

void MainWindow::on_actionClearCanvas_triggered() {
    if (m_scene->shapes().isEmpty()) {
        QMessageBox::information(this, "提示", "画布已经是空的");
        return;
    }
    
    QMessageBox::StandardButton reply = QMessageBox::question(this, "确认清空", 
        "确定要清空画布吗？",
        QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        m_scene->clear();
        statusBar()->showMessage("画布已清空");
    }
}

void MainWindow::on_actionDeleteSelected_triggered() {
    if (!m_scene->hasSelection()) {
        QMessageBox::information(this, "提示", "请先选择要删除的图形");
        return;
    }
    
    m_scene->deleteSelected();
    statusBar()->showMessage("已删除选中图形");
}

void MainWindow::setupCanvasManager() {
}

void MainWindow::setupTransformActions() {
    connect(ui->translateDistanceSpinBox, QOverload<int>::of(&QSpinBox::valueChanged),
            [this](int value) { m_translateDistance = value; });
    connect(ui->rotateAngleSpinBox, QOverload<int>::of(&QSpinBox::valueChanged),
            [this](int value) { m_rotateAngle = value; });
}

void MainWindow::setupCanvasList() {
    m_view = new GraphicsView(this);
    ui->drawAreaLayout->addWidget(m_view);
    
    connect(ui->canvasListWidget, &QListWidget::itemClicked,
            this, &MainWindow::onCanvasListClicked);
    connect(ui->addCanvasButton, &QPushButton::clicked,
            this, &MainWindow::onAddCanvas);
    connect(ui->removeCanvasButton, &QPushButton::clicked,
            this, &MainWindow::onRemoveCanvas);
    connect(ui->renameCanvasButton, &QPushButton::clicked,
            this, &MainWindow::onRenameCanvas);
}

void MainWindow::setupIcons() {
    ui->actionSelect->setIcon(QIcon::fromTheme("cursor"));
    ui->actionTriangle->setIcon(QIcon::fromTheme("shape-triangle"));
    ui->actionRectangle->setIcon(QIcon::fromTheme("shape-square"));
    ui->actionEllipse->setIcon(QIcon::fromTheme("shape-circle"));
    ui->actionPolygon->setIcon(QIcon::fromTheme("shape-polygon"));
    ui->actionCurve->setIcon(QIcon::fromTheme("curve"));
    ui->actionDeleteSelected->setIcon(QIcon::fromTheme("edit-delete"));
    ui->actionNew->setIcon(QIcon::fromTheme("document-new"));
    ui->actionSave->setIcon(QIcon::fromTheme("document-save"));
    ui->actionOpen->setIcon(QIcon::fromTheme("document-open"));
    ui->actionMoveUp->setIcon(QIcon::fromTheme("arrow-up"));
    ui->actionMoveDown->setIcon(QIcon::fromTheme("arrow-down"));
    ui->actionMoveLeft->setIcon(QIcon::fromTheme("arrow-left"));
    ui->actionMoveRight->setIcon(QIcon::fromTheme("arrow-right"));
    ui->actionRotateCW->setIcon(QIcon::fromTheme("rotate-cw"));
    ui->actionRotateCCW->setIcon(QIcon::fromTheme("rotate-ccw"));
    ui->actionPenColor->setIcon(QIcon::fromTheme("color-picker"));
    ui->actionFillColor->setIcon(QIcon::fromTheme("fill-color"));
    ui->actionClearCanvas->setIcon(QIcon::fromTheme("edit-clear"));
}

void MainWindow::closeEvent(QCloseEvent* event) {
    if (maybeSave()) {
        event->accept();
    } else {
        event->ignore();
    }
}

void MainWindow::contextMenuEvent(QContextMenuEvent* event) {
    showShapeContextMenu(event->globalPos());
}

bool MainWindow::maybeSave() {
    if (m_scene && !m_scene->shapes().isEmpty()) {
        QMessageBox::StandardButton reply = QMessageBox::question(this, "保存提示",
            "当前画布有未保存的内容，是否保存？",
            QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        
        if (reply == QMessageBox::Save) {
            on_actionSave_triggered();
            return true;
        } else if (reply == QMessageBox::Discard) {
            return true;
        } else {
            return false;
        }
    }
    return true;
}

void MainWindow::on_actionMoveUp_triggered() {
    if (m_scene && m_scene->hasSelection()) {
        m_scene->translateSelected(QPoint(0, -m_translateDistance));
        updateStatusBar();
    }
}

void MainWindow::on_actionMoveDown_triggered() {
    if (m_scene && m_scene->hasSelection()) {
        m_scene->translateSelected(QPoint(0, m_translateDistance));
        updateStatusBar();
    }
}

void MainWindow::on_actionMoveLeft_triggered() {
    if (m_scene && m_scene->hasSelection()) {
        m_scene->translateSelected(QPoint(-m_translateDistance, 0));
        updateStatusBar();
    }
}

void MainWindow::on_actionMoveRight_triggered() {
    if (m_scene && m_scene->hasSelection()) {
        m_scene->translateSelected(QPoint(m_translateDistance, 0));
        updateStatusBar();
    }
}

void MainWindow::on_actionRotateCW_triggered() {
    if (m_scene && m_scene->hasSelection()) {
        QList<Shape*> selected = m_scene->selectedShapes();
        if (!selected.isEmpty()) {
            QPoint center = selected.first()->center().toPoint();
            m_scene->rotateSelected(m_rotateAngle, center);
            updateStatusBar();
        }
    }
}

void MainWindow::on_actionRotateCCW_triggered() {
    if (m_scene && m_scene->hasSelection()) {
        QList<Shape*> selected = m_scene->selectedShapes();
        if (!selected.isEmpty()) {
            QPoint center = selected.first()->center().toPoint();
            m_scene->rotateSelected(-m_rotateAngle, center);
            updateStatusBar();
        }
    }
}

void MainWindow::onCanvasAdded(const QString& name) {
    QListWidgetItem* item = new QListWidgetItem(name);
    item->setFlags(item->flags() | Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    ui->canvasListWidget->addItem(item);
    ui->canvasListWidget->setCurrentItem(item);
}

void MainWindow::onCanvasSwitched(int index) {
    m_scene = m_canvasManager->currentScene();
    if (m_view && m_scene) {
        m_view->setScene(m_scene);
    }
    updateStatusBar();
}

void MainWindow::onCanvasListClicked(QListWidgetItem* item) {
    int index = ui->canvasListWidget->row(item);
    m_canvasManager->switchCanvas(index);
    
    m_scene = m_canvasManager->currentScene();
    if (m_view && m_scene) {
        m_view->setScene(m_scene);
    }
    updateStatusBar();
}

void MainWindow::onAddCanvas() {
    QString name = QString("Canvas %1").arg(ui->canvasListWidget->count() + 1);
    m_canvasManager->addCanvas(name);
    
    QListWidgetItem* item = new QListWidgetItem(name);
    item->setFlags(item->flags() | Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    ui->canvasListWidget->addItem(item);
    ui->canvasListWidget->setCurrentItem(item);
    
    m_scene = m_canvasManager->currentScene();
    if (m_view && m_scene) {
        m_view->setScene(m_scene);
    }
}

void MainWindow::onRemoveCanvas() {
    int index = ui->canvasListWidget->currentRow();
    if (index >= 0 && ui->canvasListWidget->count() > 1) {
        delete ui->canvasListWidget->takeItem(index);
        m_canvasManager->removeCanvas(index);
    }
}

void MainWindow::onRenameCanvas() {
    int index = ui->canvasListWidget->currentRow();
    if (index >= 0) {
        QListWidgetItem* item = ui->canvasListWidget->item(index);
        QString newName = QInputDialog::getText(this, "重命名画布", "输入新名称:",
            QLineEdit::Normal, item->text());
        if (!newName.isEmpty()) {
            m_canvasManager->renameCanvas(index, newName);
            item->setText(newName);
        }
    }
}

void MainWindow::updateStatusBar() {
    if (m_scene && m_scene->hasSelection()) {
        QList<Shape*> selected = m_scene->selectedShapes();
        if (!selected.isEmpty()) {
            Shape* shape = selected.first();
            statusBar()->showMessage(shape->getInfo());
            return;
        }
    }
    statusBar()->showMessage("就绪");
}

void MainWindow::showShapeContextMenu(const QPoint& pos) {
    QMenu menu(this);
    QAction* editAction = menu.addAction("编辑属性");
    QAction* deleteAction = menu.addAction("删除");
    
    connect(editAction, &QAction::triggered, this, &MainWindow::onEditShapeProperties);
    connect(deleteAction, &QAction::triggered, this, &MainWindow::on_actionDeleteSelected_triggered);
    
    menu.exec(pos);
}

void MainWindow::onEditShapeProperties() {
    QMessageBox::information(this, "提示", "图形属性编辑功能");
}