#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QActionGroup>
#include <QCloseEvent>
#include <QContextMenuEvent>
#include "ui_mainwindow.h"
#include "GraphicsScene.h"
#include "GraphicsView.h"
#include "CanvasManager.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow() override;

protected:
    void closeEvent(QCloseEvent* event) override;
    void contextMenuEvent(QContextMenuEvent* event) override;

private slots:
    void on_actionNew_triggered();
    void on_actionOpen_triggered();
    void on_actionSave_triggered();
    void on_actionExit_triggered();
    void on_actionSelect_triggered();
    void on_actionTriangle_triggered();
    void on_actionRectangle_triggered();
    void on_actionEllipse_triggered();
    void on_actionPolygon_triggered();
    void on_actionCurve_triggered();
    void on_actionPenColor_triggered();
    void on_actionFillColor_triggered();
    void on_penWidthSpinBox_valueChanged(int width);
    void on_actionClearCanvas_triggered();
    void on_actionDeleteSelected_triggered();
    
    void on_actionMoveUp_triggered();
    void on_actionMoveDown_triggered();
    void on_actionMoveLeft_triggered();
    void on_actionMoveRight_triggered();
    void on_actionRotateCW_triggered();
    void on_actionRotateCCW_triggered();
    
    void onCanvasAdded(const QString& name);
    void onCanvasSwitched(int index);
    void onCanvasListClicked(QListWidgetItem* item);
    void onAddCanvas();
    void onRemoveCanvas();
    void onRenameCanvas();
    
    void updateStatusBar();
    void showShapeContextMenu(const QPoint& pos);
    void onEditShapeProperties();

private:
    void setupCanvasManager();
    void setupTransformActions();
    void setupCanvasList();
    bool maybeSave();
    
    Ui::MainWindow* ui;
    GraphicsScene* m_scene;
    GraphicsView* m_view;
    CanvasManager* m_canvasManager;
    QActionGroup* m_drawActionGroup;
    
    QColor m_penColor;
    QColor m_fillColor;
    int m_penWidth;
    int m_translateDistance;
    int m_rotateAngle;
};

#endif