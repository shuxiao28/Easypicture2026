#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"
#include "GraphicsScene.h"
#include "GraphicsView.h"
#include <QActionGroup>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow() override;

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

private:
    Ui::MainWindow* ui;
    GraphicsScene* m_scene;
    GraphicsView* m_view;
    QActionGroup* m_drawActionGroup;
    
    QColor m_penColor;
    QColor m_fillColor;
    int m_penWidth;
};

#endif