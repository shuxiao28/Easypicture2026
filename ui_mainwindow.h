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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
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
    QAction *actionMoveUp;
    QAction *actionMoveDown;
    QAction *actionMoveLeft;
    QAction *actionMoveRight;
    QAction *actionRotateCW;
    QAction *actionRotateCCW;
    QWidget *centralWidget;
    QHBoxLayout *centralLayout;
    QWidget *canvasPanel;
    QVBoxLayout *canvasPanelLayout;
    QListWidget *canvasListWidget;
    QPushButton *addCanvasButton;
    QPushButton *removeCanvasButton;
    QPushButton *renameCanvasButton;
    QWidget *drawArea;
    QVBoxLayout *drawAreaLayout;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuEdit;
    QMenu *menuDraw;
    QMenu *menuTransform;
    QToolBar *drawToolBar;
    QToolBar *propertyToolBar;
    QLabel *colorLabel;
    QLabel *penWidthLabel;
    QSpinBox *penWidthSpinBox;
    QSpinBox *translateDistanceSpinBox;
    QSpinBox *rotateAngleSpinBox;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1200, 800);
        MainWindow->setStyleSheet(QString::fromUtf8("QMainWindow {\n"
"    background-color: #f5f5f5;\n"
"}\n"
"QToolBar {\n"
"    background-color: #e8e8e8;\n"
"    border: 1px solid #d0d0d0;\n"
"    spacing: 5px;\n"
"    padding: 3px;\n"
"}\n"
"QToolBar QToolButton {\n"
"    background-color: transparent;\n"
"    border: 1px solid transparent;\n"
"    border-radius: 4px;\n"
"    padding: 5px;\n"
"    min-width: 30px;\n"
"    min-height: 30px;\n"
"}\n"
"QToolBar QToolButton:hover {\n"
"    background-color: #d4e6f1;\n"
"    border: 1px solid #b8d4e8;\n"
"}\n"
"QToolBar QToolButton:checked {\n"
"    background-color: #3498db;\n"
"    color: white;\n"
"    border: 1px solid #2980b9;\n"
"}\n"
"QMenuBar {\n"
"    background-color: #e8e8e8;\n"
"    border-bottom: 1px solid #d0d0d0;\n"
"}\n"
"QMenuBar::item {\n"
"    padding: 5px 10px;\n"
"    background-color: transparent;\n"
"}\n"
"QMenuBar::item:selected {\n"
"    background-color: #d4e6f1;\n"
"}\n"
"QMenu {\n"
"    background-color: #ffffff;\n"
"    border: 1px solid #d0d0d0;\n"
"}\n"
"QMenu::item {\n"
"    paddi"
                        "ng: 5px 30px;\n"
"}\n"
"QMenu::item:selected {\n"
"    background-color: #3498db;\n"
"    color: white;\n"
"}\n"
"QStatusBar {\n"
"    background-color: #e8e8e8;\n"
"    border-top: 1px solid #d0d0d0;\n"
"}\n"
"QSpinBox {\n"
"    background-color: white;\n"
"    border: 1px solid #c0c0c0;\n"
"    border-radius: 3px;\n"
"    padding: 2px;\n"
"}\n"
"QSpinBox:focus {\n"
"    border: 1px solid #3498db;\n"
"}\n"
"QListWidget {\n"
"    background-color: white;\n"
"    border: 1px solid #d0d0d0;\n"
"    border-radius: 4px;\n"
"}\n"
"QListWidget::item {\n"
"    padding: 5px;\n"
"    border-bottom: 1px solid #e0e0e0;\n"
"}\n"
"QListWidget::item:selected {\n"
"    background-color: #3498db;\n"
"    color: white;\n"
"}\n"
"QPushButton {\n"
"    background-color: #3498db;\n"
"    color: white;\n"
"    border: none;\n"
"    border-radius: 4px;\n"
"    padding: 8px 15px;\n"
"    min-width: 80px;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #2980b9;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #1c6ea4"
                        ";\n"
"}\n"
"QLabel {\n"
"    color: #333333;\n"
"}"));
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
        actionMoveUp = new QAction(MainWindow);
        actionMoveUp->setObjectName(QString::fromUtf8("actionMoveUp"));
        actionMoveDown = new QAction(MainWindow);
        actionMoveDown->setObjectName(QString::fromUtf8("actionMoveDown"));
        actionMoveLeft = new QAction(MainWindow);
        actionMoveLeft->setObjectName(QString::fromUtf8("actionMoveLeft"));
        actionMoveRight = new QAction(MainWindow);
        actionMoveRight->setObjectName(QString::fromUtf8("actionMoveRight"));
        actionRotateCW = new QAction(MainWindow);
        actionRotateCW->setObjectName(QString::fromUtf8("actionRotateCW"));
        actionRotateCCW = new QAction(MainWindow);
        actionRotateCCW->setObjectName(QString::fromUtf8("actionRotateCCW"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        centralLayout = new QHBoxLayout(centralWidget);
        centralLayout->setSpacing(6);
        centralLayout->setContentsMargins(11, 11, 11, 11);
        centralLayout->setObjectName(QString::fromUtf8("centralLayout"));
        canvasPanel = new QWidget(centralWidget);
        canvasPanel->setObjectName(QString::fromUtf8("canvasPanel"));
        canvasPanelLayout = new QVBoxLayout(canvasPanel);
        canvasPanelLayout->setSpacing(6);
        canvasPanelLayout->setContentsMargins(11, 11, 11, 11);
        canvasPanelLayout->setObjectName(QString::fromUtf8("canvasPanelLayout"));
        canvasPanelLayout->setContentsMargins(0, 0, 0, 0);
        canvasListWidget = new QListWidget(canvasPanel);
        canvasListWidget->setObjectName(QString::fromUtf8("canvasListWidget"));

        canvasPanelLayout->addWidget(canvasListWidget);

        addCanvasButton = new QPushButton(canvasPanel);
        addCanvasButton->setObjectName(QString::fromUtf8("addCanvasButton"));

        canvasPanelLayout->addWidget(addCanvasButton);

        removeCanvasButton = new QPushButton(canvasPanel);
        removeCanvasButton->setObjectName(QString::fromUtf8("removeCanvasButton"));

        canvasPanelLayout->addWidget(removeCanvasButton);

        renameCanvasButton = new QPushButton(canvasPanel);
        renameCanvasButton->setObjectName(QString::fromUtf8("renameCanvasButton"));

        canvasPanelLayout->addWidget(renameCanvasButton);


        centralLayout->addWidget(canvasPanel);

        drawArea = new QWidget(centralWidget);
        drawArea->setObjectName(QString::fromUtf8("drawArea"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(1);
        sizePolicy.setVerticalStretch(1);
        sizePolicy.setHeightForWidth(drawArea->sizePolicy().hasHeightForWidth());
        drawArea->setSizePolicy(sizePolicy);
        drawAreaLayout = new QVBoxLayout(drawArea);
        drawAreaLayout->setSpacing(6);
        drawAreaLayout->setContentsMargins(0, 0, 0, 0);
        drawAreaLayout->setObjectName(QString::fromUtf8("drawAreaLayout"));
        drawAreaLayout->setContentsMargins(0, 0, 0, 0);

        centralLayout->addWidget(drawArea);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1200, 23));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuEdit = new QMenu(menuBar);
        menuEdit->setObjectName(QString::fromUtf8("menuEdit"));
        menuDraw = new QMenu(menuBar);
        menuDraw->setObjectName(QString::fromUtf8("menuDraw"));
        menuTransform = new QMenu(menuBar);
        menuTransform->setObjectName(QString::fromUtf8("menuTransform"));
        MainWindow->setMenuBar(menuBar);
        drawToolBar = new QToolBar(MainWindow);
        drawToolBar->setObjectName(QString::fromUtf8("drawToolBar"));
        MainWindow->addToolBar(drawToolBar);
        propertyToolBar = new QToolBar(MainWindow);
        propertyToolBar->setObjectName(QString::fromUtf8("propertyToolBar"));
        propertyToolBar->setToolButtonStyle(Qt::ToolButtonTextOnly);
        colorLabel = new QLabel(propertyToolBar);
        colorLabel->setObjectName(QString::fromUtf8("colorLabel"));
        propertyToolBar->addWidget(colorLabel);
        penWidthLabel = new QLabel(propertyToolBar);
        penWidthLabel->setObjectName(QString::fromUtf8("penWidthLabel"));
        propertyToolBar->addWidget(penWidthLabel);
        penWidthSpinBox = new QSpinBox(propertyToolBar);
        penWidthSpinBox->setObjectName(QString::fromUtf8("penWidthSpinBox"));
        penWidthSpinBox->setMinimum(1);
        penWidthSpinBox->setMaximum(20);
        penWidthSpinBox->setValue(2);
        penWidthSpinBox->setFixedWidth(60);
        propertyToolBar->addWidget(penWidthSpinBox);
        translateDistanceSpinBox = new QSpinBox(propertyToolBar);
        translateDistanceSpinBox->setObjectName(QString::fromUtf8("translateDistanceSpinBox"));
        translateDistanceSpinBox->setMinimum(1);
        translateDistanceSpinBox->setMaximum(100);
        translateDistanceSpinBox->setValue(10);
        translateDistanceSpinBox->setFixedWidth(60);
        propertyToolBar->addWidget(translateDistanceSpinBox);
        rotateAngleSpinBox = new QSpinBox(propertyToolBar);
        rotateAngleSpinBox->setObjectName(QString::fromUtf8("rotateAngleSpinBox"));
        rotateAngleSpinBox->setMinimum(1);
        rotateAngleSpinBox->setMaximum(90);
        rotateAngleSpinBox->setValue(15);
        rotateAngleSpinBox->setFixedWidth(60);
        propertyToolBar->addWidget(rotateAngleSpinBox);
        MainWindow->addToolBar(propertyToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuEdit->menuAction());
        menuBar->addAction(menuDraw->menuAction());
        menuBar->addAction(menuTransform->menuAction());
        menuFile->addAction(actionNew);
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionSave);
        menuFile->addSeparator();
        menuFile->addAction(actionExit);
        menuDraw->addAction(actionSelect);
        menuDraw->addSeparator();
        menuDraw->addAction(actionTriangle);
        menuDraw->addAction(actionRectangle);
        menuDraw->addAction(actionEllipse);
        menuDraw->addAction(actionPolygon);
        menuDraw->addAction(actionCurve);
        menuTransform->addAction(actionMoveUp);
        menuTransform->addAction(actionMoveDown);
        menuTransform->addAction(actionMoveLeft);
        menuTransform->addAction(actionMoveRight);
        menuTransform->addSeparator();
        menuTransform->addAction(actionRotateCW);
        menuTransform->addAction(actionRotateCCW);
        drawToolBar->addAction(actionSelect);
        drawToolBar->addSeparator();
        drawToolBar->addAction(actionTriangle);
        drawToolBar->addAction(actionRectangle);
        drawToolBar->addAction(actionEllipse);
        drawToolBar->addAction(actionPolygon);
        drawToolBar->addAction(actionCurve);
        drawToolBar->addSeparator();
        drawToolBar->addAction(actionMoveUp);
        drawToolBar->addAction(actionMoveDown);
        drawToolBar->addAction(actionMoveLeft);
        drawToolBar->addAction(actionMoveRight);
        drawToolBar->addSeparator();
        drawToolBar->addAction(actionRotateCW);
        drawToolBar->addAction(actionRotateCCW);
        propertyToolBar->addAction(actionPenColor);
        propertyToolBar->addAction(actionFillColor);
        propertyToolBar->addSeparator();
        propertyToolBar->addAction(actionClearCanvas);
        propertyToolBar->addAction(actionDeleteSelected);

        retranslateUi(MainWindow);

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
        actionMoveUp->setText(QApplication::translate("MainWindow", "\345\220\221\344\270\212\347\247\273\345\212\250", nullptr));
#ifndef QT_NO_SHORTCUT
        actionMoveUp->setShortcut(QApplication::translate("MainWindow", "Ctrl+Up", nullptr));
#endif // QT_NO_SHORTCUT
        actionMoveDown->setText(QApplication::translate("MainWindow", "\345\220\221\344\270\213\347\247\273\345\212\250", nullptr));
#ifndef QT_NO_SHORTCUT
        actionMoveDown->setShortcut(QApplication::translate("MainWindow", "Ctrl+Down", nullptr));
#endif // QT_NO_SHORTCUT
        actionMoveLeft->setText(QApplication::translate("MainWindow", "\345\220\221\345\267\246\347\247\273\345\212\250", nullptr));
#ifndef QT_NO_SHORTCUT
        actionMoveLeft->setShortcut(QApplication::translate("MainWindow", "Ctrl+Left", nullptr));
#endif // QT_NO_SHORTCUT
        actionMoveRight->setText(QApplication::translate("MainWindow", "\345\220\221\345\217\263\347\247\273\345\212\250", nullptr));
#ifndef QT_NO_SHORTCUT
        actionMoveRight->setShortcut(QApplication::translate("MainWindow", "Ctrl+Right", nullptr));
#endif // QT_NO_SHORTCUT
        actionRotateCW->setText(QApplication::translate("MainWindow", "\351\241\272\346\227\266\351\222\210\346\227\213\350\275\254", nullptr));
#ifndef QT_NO_SHORTCUT
        actionRotateCW->setShortcut(QApplication::translate("MainWindow", "Ctrl+R", nullptr));
#endif // QT_NO_SHORTCUT
        actionRotateCCW->setText(QApplication::translate("MainWindow", "\351\200\206\346\227\266\351\222\210\346\227\213\350\275\254", nullptr));
#ifndef QT_NO_SHORTCUT
        actionRotateCCW->setShortcut(QApplication::translate("MainWindow", "Ctrl+Shift+R", nullptr));
#endif // QT_NO_SHORTCUT
        addCanvasButton->setText(QApplication::translate("MainWindow", "+ \346\267\273\345\212\240\347\224\273\345\270\203", nullptr));
        removeCanvasButton->setText(QApplication::translate("MainWindow", "- \345\210\240\351\231\244\347\224\273\345\270\203", nullptr));
        renameCanvasButton->setText(QApplication::translate("MainWindow", "\351\207\215\345\221\275\345\220\215", nullptr));
        menuFile->setTitle(QApplication::translate("MainWindow", "\346\226\207\344\273\266", nullptr));
        menuEdit->setTitle(QApplication::translate("MainWindow", "\347\274\226\350\276\221", nullptr));
        menuDraw->setTitle(QApplication::translate("MainWindow", "\347\273\230\345\210\266", nullptr));
        menuTransform->setTitle(QApplication::translate("MainWindow", "\345\217\230\346\215\242", nullptr));
        drawToolBar->setWindowTitle(QApplication::translate("MainWindow", "\347\273\230\345\210\266\345\267\245\345\205\267", nullptr));
        propertyToolBar->setWindowTitle(QApplication::translate("MainWindow", "\345\261\236\346\200\247\350\256\276\347\275\256", nullptr));
        colorLabel->setText(QApplication::translate("MainWindow", "\347\272\277\346\235\241\351\242\234\350\211\262/\345\241\253\345\205\205\351\242\234\350\211\262:", nullptr));
        penWidthLabel->setText(QApplication::translate("MainWindow", "\347\272\277\345\256\275:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
