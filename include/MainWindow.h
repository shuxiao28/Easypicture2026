#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QToolBar>
#include <QAction>
#include <QComboBox>
#include <QSpinBox>
#include <QColorDialog>
#include "GraphicsScene.h"
#include "GraphicsView.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow() override;

private slots:
    void onNewFile();
    void onOpenFile();
    void onSaveFile();
    void onExit();
    void onSelectTool();
    void onDrawTriangle();
    void onDrawRectangle();
    void onDrawEllipse();
    void onDrawPolygon();
    void onDrawCurve();
    void onSetPenColor();
    void onSetFillColor();
    void onPenWidthChanged(int width);
    void onClearCanvas();
    void onClearSelection();
    void onDeleteSelected();

private:
    void createActions();
    void createToolBar();
    void createStatusBar();
    void setupConnections();

    GraphicsScene* m_scene;
    GraphicsView* m_view;

    QToolBar* m_mainToolBar;
    QToolBar* m_drawToolBar;
    QToolBar* m_propertyToolBar;

    QAction* m_newAction;
    QAction* m_openAction;
    QAction* m_saveAction;
    QAction* m_exitAction;

    QAction* m_selectAction;
    QAction* m_triangleAction;
    QAction* m_rectangleAction;
    QAction* m_ellipseAction;
    QAction* m_polygonAction;
    QAction* m_curveAction;

    QAction* m_penColorAction;
    QAction* m_fillColorAction;
    QSpinBox* m_penWidthSpinBox;

    QAction* m_clearAction;
    QAction* m_deleteAction;

    QColor m_penColor;
    QColor m_fillColor;
    int m_penWidth;
};

#endif