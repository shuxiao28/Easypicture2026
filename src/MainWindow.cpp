#include "MainWindow.h"
#include "FileManager.h"
#include <QColorDialog>
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      m_penColor(Qt::black),
      m_fillColor(Qt::white),
      m_penWidth(2)
{
    ui->setupUi(this);
    
    m_scene = new GraphicsScene(this);
    m_view = new GraphicsView(this);
    m_view->setScene(m_scene);
    
    ui->centralLayout->addWidget(m_view);
    
    m_drawActionGroup = new QActionGroup(this);
    m_drawActionGroup->addAction(ui->actionSelect);
    m_drawActionGroup->addAction(ui->actionTriangle);
    m_drawActionGroup->addAction(ui->actionRectangle);
    m_drawActionGroup->addAction(ui->actionEllipse);
    m_drawActionGroup->addAction(ui->actionPolygon);
    m_drawActionGroup->addAction(ui->actionCurve);
    
    ui->penWidthSpinBox->setValue(m_penWidth);
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