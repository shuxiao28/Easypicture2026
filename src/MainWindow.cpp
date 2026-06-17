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
      m_rotateAngle(15),
      m_hasUnsavedChanges(false),
      m_currentFilePath("")
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
    QListWidgetItem* firstCanvas = new QListWidgetItem("Canvas 1");
    firstCanvas->setFlags(firstCanvas->flags() | Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    ui->canvasListWidget->addItem(firstCanvas);
    ui->canvasListWidget->setCurrentItem(firstCanvas);
    
    m_scene = m_canvasManager->currentScene();
    if (m_view && m_scene) {
        m_view->setScene(m_scene);
    }
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
    // 先检查是否有未保存的修改
    if (m_hasUnsavedChanges) {
        QMessageBox::StandardButton reply = QMessageBox::question(this, "保存提示",
            "当前有未保存的修改，是否先保存？",
            QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        
        if (reply == QMessageBox::Save) {
            on_actionSave_triggered();
            if (m_hasUnsavedChanges) return; // 保存失败或取消
        } else if (reply == QMessageBox::Cancel) {
            return;
        }
    }
    
    QString filePath = QFileDialog::getOpenFileName(this, "打开文件", "", 
        "文本图形文件 (*.txt);;SVG文件 (*.svg);;所有文件 (*.*)");
    
    if (!filePath.isEmpty()) {
        FileManager manager;
        if (manager.loadScene(m_scene, filePath)) {
            m_currentFilePath = filePath;
            m_hasUnsavedChanges = false;
            setWindowTitle("EasyPicture 2026 - " + filePath);
            setWindowModified(false);
            statusBar()->showMessage("打开文件: " + filePath);
        } else {
            QMessageBox::warning(this, "错误", "无法打开文件: " + filePath);
        }
    }
}

void MainWindow::on_actionSave_triggered() {
    QString filePath = m_currentFilePath;
    
    if (filePath.isEmpty()) {
        filePath = QFileDialog::getSaveFileName(this, "保存文件", "", 
            "文本图形文件 (*.txt);;SVG文件 (*.svg);;所有文件 (*.*)");
    }
    
    if (!filePath.isEmpty()) {
        FileManager manager;
        if (manager.saveScene(m_scene, filePath)) {
            m_currentFilePath = filePath;
            m_hasUnsavedChanges = false;
            setWindowTitle("EasyPicture 2026 - " + filePath);
            setWindowModified(false);
            statusBar()->showMessage("保存文件: " + filePath);
        } else {
            QMessageBox::warning(this, "错误", "无法保存文件: " + filePath);
        }
    }
}

void MainWindow::on_actionExit_triggered() {
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

QIcon MainWindow::createShapeIcon(Shape::ShapeType type) {
    QPixmap pixmap(24, 24);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.setPen(QPen(Qt::black, 2));
    painter.setBrush(Qt::white);
    
    switch (type) {
    case Shape::Triangle: {
        QPolygon polygon;
        polygon << QPoint(12, 2) << QPoint(22, 20) << QPoint(2, 20);
        painter.drawPolygon(polygon);
        break;
    }
    case Shape::Rectangle:
        painter.drawRect(2, 4, 20, 16);
        break;
    case Shape::Ellipse:
        painter.drawEllipse(2, 4, 20, 16);
        break;
    case Shape::Polygon: {
        QPolygon polygon;
        polygon << QPoint(12, 2) << QPoint(22, 10) << QPoint(18, 22) << QPoint(6, 22) << QPoint(2, 10);
        painter.drawPolygon(polygon);
        break;
    }
    case Shape::Curve: {
        QPainterPath path;
        path.moveTo(2, 12);
        path.cubicTo(6, 2, 18, 22, 22, 12);
        painter.drawPath(path);
        break;
    }
    }
    
    return QIcon(pixmap);
}

QIcon MainWindow::createActionIcon(const QString& actionName) {
    QPixmap pixmap(24, 24);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.setPen(QPen(Qt::black, 2));
    painter.setBrush(Qt::white);
    
    if (actionName == "select") {
        painter.drawRect(2, 2, 10, 10);
        painter.drawLine(12, 12, 20, 20);
        painter.drawLine(20, 12, 12, 20);
    } else if (actionName == "delete") {
        painter.drawRect(4, 6, 16, 12);
        painter.drawLine(6, 6, 18, 18);
        painter.drawLine(18, 6, 6, 18);
    } else if (actionName == "new") {
        painter.drawRect(4, 4, 16, 16);
        painter.drawLine(4, 12, 20, 12);
        painter.drawLine(12, 4, 12, 20);
    } else if (actionName == "save") {
        painter.drawRect(4, 8, 16, 12);
        painter.drawLine(4, 8, 12, 2);
        painter.drawLine(12, 2, 20, 8);
    } else if (actionName == "open") {
        painter.drawRect(4, 6, 16, 14);
        painter.drawRect(8, 2, 8, 8);
    } else if (actionName == "moveup") {
        painter.drawLine(12, 4, 12, 18);
        painter.drawLine(12, 4, 6, 10);
        painter.drawLine(12, 4, 18, 10);
    } else if (actionName == "movedown") {
        painter.drawLine(12, 6, 12, 20);
        painter.drawLine(12, 20, 6, 14);
        painter.drawLine(12, 20, 18, 14);
    } else if (actionName == "moveleft") {
        painter.drawLine(6, 12, 20, 12);
        painter.drawLine(6, 12, 12, 6);
        painter.drawLine(6, 12, 12, 18);
    } else if (actionName == "moveright") {
        painter.drawLine(4, 12, 18, 12);
        painter.drawLine(18, 12, 12, 6);
        painter.drawLine(18, 12, 12, 18);
    } else if (actionName == "rotatecw") {
        painter.drawArc(4, 4, 16, 16, 90 * 16, -270 * 16);
        painter.drawLine(12, 6, 12, 2);
        painter.drawLine(12, 6, 16, 4);
    } else if (actionName == "rotateccw") {
        painter.drawArc(4, 4, 16, 16, 90 * 16, 270 * 16);
        painter.drawLine(12, 6, 12, 2);
        painter.drawLine(12, 6, 8, 4);
    } else if (actionName == "pencolor") {
        painter.setBrush(QColor(255, 0, 0));
        painter.drawEllipse(4, 4, 16, 16);
    } else if (actionName == "fillcolor") {
        painter.setBrush(QColor(0, 255, 0));
        painter.drawRect(4, 4, 16, 16);
    } else if (actionName == "clear") {
        painter.drawRect(4, 4, 16, 16);
        painter.drawLine(4, 4, 20, 20);
        painter.drawLine(20, 4, 4, 20);
    }
    
    return QIcon(pixmap);
}

void MainWindow::setupIcons() {
    ui->actionSelect->setIcon(createActionIcon("select"));
    ui->actionTriangle->setIcon(createShapeIcon(Shape::Triangle));
    ui->actionRectangle->setIcon(createShapeIcon(Shape::Rectangle));
    ui->actionEllipse->setIcon(createShapeIcon(Shape::Ellipse));
    ui->actionPolygon->setIcon(createShapeIcon(Shape::Polygon));
    ui->actionCurve->setIcon(createShapeIcon(Shape::Curve));
    ui->actionDeleteSelected->setIcon(createActionIcon("delete"));
    ui->actionNew->setIcon(createActionIcon("new"));
    ui->actionSave->setIcon(createActionIcon("save"));
    ui->actionOpen->setIcon(createActionIcon("open"));
    ui->actionMoveUp->setIcon(createActionIcon("moveup"));
    ui->actionMoveDown->setIcon(createActionIcon("movedown"));
    ui->actionMoveLeft->setIcon(createActionIcon("moveleft"));
    ui->actionMoveRight->setIcon(createActionIcon("moveright"));
    ui->actionRotateCW->setIcon(createActionIcon("rotatecw"));
    ui->actionRotateCCW->setIcon(createActionIcon("rotateccw"));
    ui->actionPenColor->setIcon(createActionIcon("pencolor"));
    ui->actionFillColor->setIcon(createActionIcon("fillcolor"));
    ui->actionClearCanvas->setIcon(createActionIcon("clear"));
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
    bool hasShapes = false;
    for (int i = 0; i < m_canvasManager->canvasCount(); ++i) {
        GraphicsScene* scene = m_canvasManager->currentScene();
        if (scene && !scene->shapes().isEmpty()) {
            hasShapes = true;
            break;
        }
    }
    
    if (!m_hasUnsavedChanges && !hasShapes) {
        return true;
    }
    
    QString message = "当前画布有未保存的图形内容";
    if (!m_currentFilePath.isEmpty()) {
        message += QString("，当前文件路径：%1").arg(m_currentFilePath);
    }
    message += "。是否保存？";
    
    QMessageBox::StandardButton reply = QMessageBox::question(this, "退出提示",
        message,
        QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    
    if (reply == QMessageBox::Save) {
        if (m_currentFilePath.isEmpty()) {
            QString filePath = QFileDialog::getSaveFileName(this, "保存文件",
                QDir::homePath(), "矢量图形文件 (*.svg);;所有文件 (*.*)");
            
            if (!filePath.isEmpty()) {
                if (!filePath.endsWith(".svg", Qt::CaseInsensitive)) {
                    filePath += ".svg";
                }
                m_currentFilePath = filePath;
            } else {
                return false;
            }
        }
        
        bool prevHasUnsaved = m_hasUnsavedChanges;
        on_actionSave_triggered();
        
        if (prevHasUnsaved && m_hasUnsavedChanges) {
            return false;
        }
        return true;
    } else if (reply == QMessageBox::Discard) {
        return true;
    } else {
        return false;
    }
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
        // 连接场景变化信号
        connect(m_scene, &GraphicsScene::shapeAdded, this, &MainWindow::onSceneChanged);
        connect(m_scene, &GraphicsScene::shapeRemoved, this, &MainWindow::onSceneChanged);
        connect(m_scene, &GraphicsScene::sceneCleared, this, &MainWindow::onSceneChanged);
    }
    updateStatusBar();
}

void MainWindow::onSceneChanged() {
    m_hasUnsavedChanges = true;
    // 更新窗口标题显示修改状态
    if (!m_currentFilePath.isEmpty()) {
        setWindowTitle("EasyPicture 2026 - " + m_currentFilePath + " [*]");
    } else {
        setWindowTitle("EasyPicture 2026 - 未保存 [*]");
    }
    setWindowModified(true);
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