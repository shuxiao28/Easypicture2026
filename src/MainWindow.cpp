#include "MainWindow.h"
#include <QColorDialog>
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
      m_penColor(Qt::black),
      m_fillColor(Qt::white),
      m_penWidth(2)
{
    m_scene = new GraphicsScene(this);
    m_view = new GraphicsView(this);
    m_view->setScene(m_scene);
    
    setCentralWidget(m_view);
    
    createActions();
    createToolBar();
    createStatusBar();
    setupConnections();
    
    setWindowTitle("EasyPicture 2026");
    resize(1000, 700);
}

MainWindow::~MainWindow() {
}

void MainWindow::createActions() {
    m_newAction = new QAction(QIcon(":/icons/new.png"), "新建", this);
    m_newAction->setShortcut(QKeySequence::New);
    
    m_openAction = new QAction(QIcon(":/icons/open.png"), "打开", this);
    m_openAction->setShortcut(QKeySequence::Open);
    
    m_saveAction = new QAction(QIcon(":/icons/save.png"), "保存", this);
    m_saveAction->setShortcut(QKeySequence::Save);
    
    m_exitAction = new QAction(QIcon(":/icons/exit.png"), "退出", this);
    m_exitAction->setShortcut(QKeySequence::Quit);
    
    m_selectAction = new QAction(QIcon(":/icons/select.png"), "选择", this);
    m_selectAction->setCheckable(true);
    m_selectAction->setChecked(true);
    
    m_triangleAction = new QAction(QIcon(":/icons/triangle.png"), "三角形", this);
    m_triangleAction->setCheckable(true);
    
    m_rectangleAction = new QAction(QIcon(":/icons/rectangle.png"), "矩形", this);
    m_rectangleAction->setCheckable(true);
    
    m_ellipseAction = new QAction(QIcon(":/icons/ellipse.png"), "椭圆", this);
    m_ellipseAction->setCheckable(true);
    
    m_polygonAction = new QAction(QIcon(":/icons/polygon.png"), "多边形", this);
    m_polygonAction->setCheckable(true);
    
    m_curveAction = new QAction(QIcon(":/icons/curve.png"), "曲线", this);
    m_curveAction->setCheckable(true);
    
    QActionGroup* drawGroup = new QActionGroup(this);
    drawGroup->addAction(m_selectAction);
    drawGroup->addAction(m_triangleAction);
    drawGroup->addAction(m_rectangleAction);
    drawGroup->addAction(m_ellipseAction);
    drawGroup->addAction(m_polygonAction);
    drawGroup->addAction(m_curveAction);
    
    m_penColorAction = new QAction("线条颜色", this);
    
    m_fillColorAction = new QAction("填充颜色", this);
    
    m_penWidthSpinBox = new QSpinBox(this);
    m_penWidthSpinBox->setRange(1, 20);
    m_penWidthSpinBox->setValue(m_penWidth);
    m_penWidthSpinBox->setFixedWidth(60);
    
    m_clearAction = new QAction("清空画布", this);
    
    m_deleteAction = new QAction("删除选中", this);
    m_deleteAction->setShortcut(QKeySequence::Delete);
}

void MainWindow::createToolBar() {
    m_mainToolBar = addToolBar("文件操作");
    m_mainToolBar->addAction(m_newAction);
    m_mainToolBar->addAction(m_openAction);
    m_mainToolBar->addAction(m_saveAction);
    m_mainToolBar->addSeparator();
    m_mainToolBar->addAction(m_exitAction);
    
    m_drawToolBar = addToolBar("绘制工具");
    m_drawToolBar->addAction(m_selectAction);
    m_drawToolBar->addSeparator();
    m_drawToolBar->addAction(m_triangleAction);
    m_drawToolBar->addAction(m_rectangleAction);
    m_drawToolBar->addAction(m_ellipseAction);
    m_drawToolBar->addAction(m_polygonAction);
    m_drawToolBar->addAction(m_curveAction);
    
    m_propertyToolBar = addToolBar("属性设置");
    m_propertyToolBar->addAction(m_penColorAction);
    m_propertyToolBar->addAction(m_fillColorAction);
    m_propertyToolBar->addWidget(m_penWidthSpinBox);
    m_propertyToolBar->addSeparator();
    m_propertyToolBar->addAction(m_clearAction);
    m_propertyToolBar->addAction(m_deleteAction);
}

void MainWindow::createStatusBar() {
    statusBar()->showMessage("就绪");
}

void MainWindow::setupConnections() {
    connect(m_newAction, &QAction::triggered, this, &MainWindow::onNewFile);
    connect(m_openAction, &QAction::triggered, this, &MainWindow::onOpenFile);
    connect(m_saveAction, &QAction::triggered, this, &MainWindow::onSaveFile);
    connect(m_exitAction, &QAction::triggered, this, &MainWindow::onExit);
    
    connect(m_selectAction, &QAction::triggered, this, &MainWindow::onSelectTool);
    connect(m_triangleAction, &QAction::triggered, this, &MainWindow::onDrawTriangle);
    connect(m_rectangleAction, &QAction::triggered, this, &MainWindow::onDrawRectangle);
    connect(m_ellipseAction, &QAction::triggered, this, &MainWindow::onDrawEllipse);
    connect(m_polygonAction, &QAction::triggered, this, &MainWindow::onDrawPolygon);
    connect(m_curveAction, &QAction::triggered, this, &MainWindow::onDrawCurve);
    
    connect(m_penColorAction, &QAction::triggered, this, &MainWindow::onSetPenColor);
    connect(m_fillColorAction, &QAction::triggered, this, &MainWindow::onSetFillColor);
    connect(m_penWidthSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), 
            this, &MainWindow::onPenWidthChanged);
    
    connect(m_clearAction, &QAction::triggered, this, &MainWindow::onClearCanvas);
    connect(m_deleteAction, &QAction::triggered, this, &MainWindow::onDeleteSelected);
}

void MainWindow::onNewFile() {
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

void MainWindow::onOpenFile() {
    QString filePath = QFileDialog::getOpenFileName(this, "打开文件", "", 
        "矢量图形文件 (*.svg);;所有文件 (*.*)");
    
    if (!filePath.isEmpty()) {
        statusBar()->showMessage("打开文件: " + filePath);
    }
}

void MainWindow::onSaveFile() {
    QString filePath = QFileDialog::getSaveFileName(this, "保存文件", "", 
        "SVG文件 (*.svg);;所有文件 (*.*)");
    
    if (!filePath.isEmpty()) {
        statusBar()->showMessage("保存文件: " + filePath);
    }
}

void MainWindow::onExit() {
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

void MainWindow::onSelectTool() {
    m_view->setCurrentTool(GraphicsView::SelectTool);
    statusBar()->showMessage("选择工具 - 点击选择图形，拖拽移动");
}

void MainWindow::onDrawTriangle() {
    m_view->setCurrentTool(GraphicsView::DrawTriangle);
    statusBar()->showMessage("绘制三角形 - 拖拽鼠标绘制");
}

void MainWindow::onDrawRectangle() {
    m_view->setCurrentTool(GraphicsView::DrawRectangle);
    statusBar()->showMessage("绘制矩形 - 拖拽鼠标绘制");
}

void MainWindow::onDrawEllipse() {
    m_view->setCurrentTool(GraphicsView::DrawEllipse);
    statusBar()->showMessage("绘制椭圆 - 拖拽鼠标绘制");
}

void MainWindow::onDrawPolygon() {
    m_view->setCurrentTool(GraphicsView::DrawPolygon);
    statusBar()->showMessage("绘制多边形 - 点击添加顶点，右键完成");
}

void MainWindow::onDrawCurve() {
    m_view->setCurrentTool(GraphicsView::DrawCurve);
    statusBar()->showMessage("绘制曲线 - 点击添加控制点，右键完成");
}

void MainWindow::onSetPenColor() {
    QColor color = QColorDialog::getColor(m_penColor, this, "选择线条颜色");
    if (color.isValid()) {
        m_penColor = color;
        m_view->setDrawColor(color);
        statusBar()->showMessage("线条颜色已设置");
    }
}

void MainWindow::onSetFillColor() {
    QColor color = QColorDialog::getColor(m_fillColor, this, "选择填充颜色");
    if (color.isValid()) {
        m_fillColor = color;
        m_view->setFillColor(color);
        statusBar()->showMessage("填充颜色已设置");
    }
}

void MainWindow::onPenWidthChanged(int width) {
    m_penWidth = width;
    m_view->setPenWidth(width);
    statusBar()->showMessage("线条宽度: " + QString::number(width) + "px");
}

void MainWindow::onClearCanvas() {
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

void MainWindow::onDeleteSelected() {
    if (!m_scene->hasSelection()) {
        QMessageBox::information(this, "提示", "请先选择要删除的图形");
        return;
    }
    
    m_scene->deleteSelected();
    statusBar()->showMessage("已删除选中图形");
}