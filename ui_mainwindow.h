/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionNew;
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionExit;
    QAction *actionSelect;
    QAction *actionTriangle;
    QAction *actionRectangle;
    QAction *actionEllipse;
    QAction *actionPolygon;
    QAction *actionCurve;
    QAction *actionPenColor;
    QAction *actionFillColor;
    QAction *actionClearCanvas;
    QAction *actionDeleteSelected;
    QWidget *centralWidget;
    QVBoxLayout *centralLayout;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuEdit;
    QMenu *menuDraw;
    QToolBar *mainToolBar;
    QToolBar *drawToolBar;
    QToolBar *propertyToolBar;
    QSpinBox *penWidthSpinBox;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1000, 700);
        actionNew = new QAction(MainWindow);
        actionNew->setObjectName(QString::fromUtf8("actionNew"));
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        actionSelect = new QAction(MainWindow);
        actionSelect->setObjectName(QString::fromUtf8("actionSelect"));
        actionSelect->setCheckable(true);
        actionSelect->setChecked(true);
        actionTriangle = new QAction(MainWindow);
        actionTriangle->setObjectName(QString::fromUtf8("actionTriangle"));
        actionTriangle->setCheckable(true);
        actionRectangle = new QAction(MainWindow);
        actionRectangle->setObjectName(QString::fromUtf8("actionRectangle"));
        actionRectangle->setCheckable(true);
        actionEllipse = new QAction(MainWindow);
        actionEllipse->setObjectName(QString::fromUtf8("actionEllipse"));
        actionEllipse->setCheckable(true);
        actionPolygon = new QAction(MainWindow);
        actionPolygon->setObjectName(QString::fromUtf8("actionPolygon"));
        actionPolygon->setCheckable(true);
        actionCurve = new QAction(MainWindow);
        actionCurve->setObjectName(QString::fromUtf8("actionCurve"));
        actionCurve->setCheckable(true);
        actionPenColor = new QAction(MainWindow);
        actionPenColor->setObjectName(QString::fromUtf8("actionPenColor"));
        actionFillColor = new QAction(MainWindow);
        actionFillColor->setObjectName(QString::fromUtf8("actionFillColor"));
        actionClearCanvas = new QAction(MainWindow);
        actionClearCanvas->setObjectName(QString::fromUtf8("actionClearCanvas"));
        actionDeleteSelected = new QAction(MainWindow);
        actionDeleteSelected->setObjectName(QString::fromUtf8("actionDeleteSelected"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        centralLayout = new QVBoxLayout(centralWidget);
        centralLayout->setSpacing(6);
        centralLayout->setContentsMargins(11, 11, 11, 11);
        centralLayout->setObjectName(QString::fromUtf8("centralLayout"));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1000, 23));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuEdit = new QMenu(menuBar);
        menuEdit->setObjectName(QString::fromUtf8("menuEdit"));
        menuDraw = new QMenu(menuBar);
        menuDraw->setObjectName(QString::fromUtf8("menuDraw"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(mainToolBar);
        drawToolBar = new QToolBar(MainWindow);
        drawToolBar->setObjectName(QString::fromUtf8("drawToolBar"));
        MainWindow->addToolBar(drawToolBar);
        propertyToolBar = new QToolBar(MainWindow);
        propertyToolBar->setObjectName(QString::fromUtf8("propertyToolBar"));
        penWidthSpinBox = new QSpinBox(propertyToolBar);
        penWidthSpinBox->setObjectName(QString::fromUtf8("penWidthSpinBox"));
        penWidthSpinBox->setMinimum(1);
        penWidthSpinBox->setMaximum(20);
        penWidthSpinBox->setValue(2);
        penWidthSpinBox->setFixedWidth(60);
        propertyToolBar->addWidget(penWidthSpinBox);
        MainWindow->addToolBar(propertyToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuEdit->menuAction());
        menuBar->addAction(menuDraw->menuAction());
        menuFile->addAction(actionNew);
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionSave);
        menuFile->addSeparator();
        menuFile->addAction(actionExit);
        menuEdit->addAction(actionClearCanvas);
        menuEdit->addAction(actionDeleteSelected);
        menuDraw->addAction(actionSelect);
        menuDraw->addSeparator();
        menuDraw->addAction(actionTriangle);
        menuDraw->addAction(actionRectangle);
        menuDraw->addAction(actionEllipse);
        menuDraw->addAction(actionPolygon);
        menuDraw->addAction(actionCurve);
        mainToolBar->addAction(actionNew);
        mainToolBar->addAction(actionOpen);
        mainToolBar->addAction(actionSave);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionExit);
        drawToolBar->addAction(actionSelect);
        drawToolBar->addSeparator();
        drawToolBar->addAction(actionTriangle);
        drawToolBar->addAction(actionRectangle);
        drawToolBar->addAction(actionEllipse);
        drawToolBar->addAction(actionPolygon);
        drawToolBar->addAction(actionCurve);
        propertyToolBar->addAction(actionPenColor);
        propertyToolBar->addAction(actionFillColor);
        propertyToolBar->addSeparator();
        propertyToolBar->addAction(actionClearCanvas);
        propertyToolBar->addAction(actionDeleteSelected);

        retranslateUi(MainWindow);
        QObject::connect(actionNew, SIGNAL(triggered()), MainWindow, SLOT(on_actionNew_triggered()));
        QObject::connect(actionOpen, SIGNAL(triggered()), MainWindow, SLOT(on_actionOpen_triggered()));
        QObject::connect(actionSave, SIGNAL(triggered()), MainWindow, SLOT(on_actionSave_triggered()));
        QObject::connect(actionExit, SIGNAL(triggered()), MainWindow, SLOT(on_actionExit_triggered()));
        QObject::connect(actionSelect, SIGNAL(triggered()), MainWindow, SLOT(on_actionSelect_triggered()));
        QObject::connect(actionTriangle, SIGNAL(triggered()), MainWindow, SLOT(on_actionTriangle_triggered()));
        QObject::connect(actionRectangle, SIGNAL(triggered()), MainWindow, SLOT(on_actionRectangle_triggered()));
        QObject::connect(actionEllipse, SIGNAL(triggered()), MainWindow, SLOT(on_actionEllipse_triggered()));
        QObject::connect(actionPolygon, SIGNAL(triggered()), MainWindow, SLOT(on_actionPolygon_triggered()));
        QObject::connect(actionCurve, SIGNAL(triggered()), MainWindow, SLOT(on_actionCurve_triggered()));
        QObject::connect(actionPenColor, SIGNAL(triggered()), MainWindow, SLOT(on_actionPenColor_triggered()));
        QObject::connect(actionFillColor, SIGNAL(triggered()), MainWindow, SLOT(on_actionFillColor_triggered()));
        QObject::connect(penWidthSpinBox, SIGNAL(valueChanged(int)), MainWindow, SLOT(on_penWidthSpinBox_valueChanged(int)));
        QObject::connect(actionClearCanvas, SIGNAL(triggered()), MainWindow, SLOT(on_actionClearCanvas_triggered()));
        QObject::connect(actionDeleteSelected, SIGNAL(triggered()), MainWindow, SLOT(on_actionDeleteSelected_triggered()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "EasyPicture 2026", nullptr));
        actionNew->setText(QApplication::translate("MainWindow", "\346\226\260\345\273\272", nullptr));
#ifndef QT_NO_SHORTCUT
        actionNew->setShortcut(QApplication::translate("MainWindow", "Ctrl+N", nullptr));
#endif // QT_NO_SHORTCUT
        actionOpen->setText(QApplication::translate("MainWindow", "\346\211\223\345\274\200", nullptr));
#ifndef QT_NO_SHORTCUT
        actionOpen->setShortcut(QApplication::translate("MainWindow", "Ctrl+O", nullptr));
#endif // QT_NO_SHORTCUT
        actionSave->setText(QApplication::translate("MainWindow", "\344\277\235\345\255\230", nullptr));
#ifndef QT_NO_SHORTCUT
        actionSave->setShortcut(QApplication::translate("MainWindow", "Ctrl+S", nullptr));
#endif // QT_NO_SHORTCUT
        actionExit->setText(QApplication::translate("MainWindow", "\351\200\200\345\207\272", nullptr));
#ifndef QT_NO_SHORTCUT
        actionExit->setShortcut(QApplication::translate("MainWindow", "Ctrl+Q", nullptr));
#endif // QT_NO_SHORTCUT
        actionSelect->setText(QApplication::translate("MainWindow", "\351\200\211\346\213\251", nullptr));
        actionTriangle->setText(QApplication::translate("MainWindow", "\344\270\211\350\247\222\345\275\242", nullptr));
        actionRectangle->setText(QApplication::translate("MainWindow", "\347\237\251\345\275\242", nullptr));
        actionEllipse->setText(QApplication::translate("MainWindow", "\346\244\255\345\234\206", nullptr));
        actionPolygon->setText(QApplication::translate("MainWindow", "\345\244\232\350\276\271\345\275\242", nullptr));
        actionCurve->setText(QApplication::translate("MainWindow", "\346\233\262\347\272\277", nullptr));
        actionPenColor->setText(QApplication::translate("MainWindow", "\347\272\277\346\235\241\351\242\234\350\211\262", nullptr));
        actionFillColor->setText(QApplication::translate("MainWindow", "\345\241\253\345\205\205\351\242\234\350\211\262", nullptr));
        actionClearCanvas->setText(QApplication::translate("MainWindow", "\346\270\205\347\251\272\347\224\273\345\270\203", nullptr));
        actionDeleteSelected->setText(QApplication::translate("MainWindow", "\345\210\240\351\231\244\351\200\211\344\270\255", nullptr));
#ifndef QT_NO_SHORTCUT
        actionDeleteSelected->setShortcut(QApplication::translate("MainWindow", "Delete", nullptr));
#endif // QT_NO_SHORTCUT
        menuFile->setTitle(QApplication::translate("MainWindow", "\346\226\207\344\273\266", nullptr));
        menuEdit->setTitle(QApplication::translate("MainWindow", "\347\274\226\350\276\221", nullptr));
        menuDraw->setTitle(QApplication::translate("MainWindow", "\347\273\230\345\210\266", nullptr));
        mainToolBar->setWindowTitle(QApplication::translate("MainWindow", "\346\226\207\344\273\266\346\223\215\344\275\234", nullptr));
        drawToolBar->setWindowTitle(QApplication::translate("MainWindow", "\347\273\230\345\210\266\345\267\245\345\205\267", nullptr));
        propertyToolBar->setWindowTitle(QApplication::translate("MainWindow", "\345\261\236\346\200\247\350\256\276\347\275\256", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
