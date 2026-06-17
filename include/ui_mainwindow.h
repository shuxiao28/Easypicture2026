#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
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

class Ui_MainWindow {
public:
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
    QToolBar *mainToolBar;
    QToolBar *drawToolBar;
    QToolBar *transformToolBar;
    QToolBar *propertyToolBar;
    QStatusBar *statusBar;
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
    QSpinBox *penWidthSpinBox;
    QSpinBox *translateDistanceSpinBox;
    QSpinBox *rotateAngleSpinBox;

    void setupUi(QMainWindow *MainWindow) {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1200, 700);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralLayout = new QHBoxLayout(centralWidget);
        centralLayout->setObjectName(QStringLiteral("centralLayout"));
        centralLayout->setContentsMargins(0, 0, 0, 0);
        
        canvasPanel = new QWidget(centralWidget);
        canvasPanel->setObjectName(QStringLiteral("canvasPanel"));
        canvasPanel->setFixedWidth(150);
        canvasPanel->setStyleSheet(QStringLiteral("background-color: #f0f0f0;"));
        canvasPanelLayout = new QVBoxLayout(canvasPanel);
        canvasPanelLayout->setObjectName(QStringLiteral("canvasPanelLayout"));
        canvasPanelLayout->setContentsMargins(5, 5, 5, 5);
        
        canvasListWidget = new QListWidget(canvasPanel);
        canvasListWidget->setObjectName(QStringLiteral("canvasListWidget"));
        canvasListWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        canvasPanelLayout->addWidget(canvasListWidget);
        
        addCanvasButton = new QPushButton(canvasPanel);
        addCanvasButton->setObjectName(QStringLiteral("addCanvasButton"));
        canvasPanelLayout->addWidget(addCanvasButton);
        
        removeCanvasButton = new QPushButton(canvasPanel);
        removeCanvasButton->setObjectName(QStringLiteral("removeCanvasButton"));
        canvasPanelLayout->addWidget(removeCanvasButton);
        
        renameCanvasButton = new QPushButton(canvasPanel);
        renameCanvasButton->setObjectName(QStringLiteral("renameCanvasButton"));
        canvasPanelLayout->addWidget(renameCanvasButton);
        
        centralLayout->addWidget(canvasPanel);
        
        drawArea = new QWidget(centralWidget);
        drawArea->setObjectName(QStringLiteral("drawArea"));
        drawAreaLayout = new QVBoxLayout(drawArea);
        drawAreaLayout->setObjectName(QStringLiteral("drawAreaLayout"));
        drawAreaLayout->setContentsMargins(0, 0, 0, 0);
        centralLayout->addWidget(drawArea);
        
        MainWindow->setCentralWidget(centralWidget);
        
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1200, 23));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuEdit = new QMenu(menuBar);
        menuEdit->setObjectName(QStringLiteral("menuEdit"));
        menuDraw = new QMenu(menuBar);
        menuDraw->setObjectName(QStringLiteral("menuDraw"));
        menuTransform = new QMenu(menuBar);
        menuTransform->setObjectName(QStringLiteral("menuTransform"));
        MainWindow->setMenuBar(menuBar);
        
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        
        drawToolBar = new QToolBar(MainWindow);
        drawToolBar->setObjectName(QStringLiteral("drawToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, drawToolBar);
        
        transformToolBar = new QToolBar(MainWindow);
        transformToolBar->setObjectName(QStringLiteral("transformToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, transformToolBar);
        
        propertyToolBar = new QToolBar(MainWindow);
        propertyToolBar->setObjectName(QStringLiteral("propertyToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, propertyToolBar);
        
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        actionNew = new QAction(MainWindow);
        actionNew->setObjectName(QStringLiteral("actionNew"));
        actionNew->setShortcut(QKeySequence::New);
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        actionOpen->setShortcut(QKeySequence::Open);
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        actionSave->setShortcut(QKeySequence::Save);
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        actionExit->setShortcut(QKeySequence::Quit);
        actionSelect = new QAction(MainWindow);
        actionSelect->setObjectName(QStringLiteral("actionSelect"));
        actionSelect->setCheckable(true);
        actionSelect->setChecked(true);
        actionTriangle = new QAction(MainWindow);
        actionTriangle->setObjectName(QStringLiteral("actionTriangle"));
        actionTriangle->setCheckable(true);
        actionRectangle = new QAction(MainWindow);
        actionRectangle->setObjectName(QStringLiteral("actionRectangle"));
        actionRectangle->setCheckable(true);
        actionEllipse = new QAction(MainWindow);
        actionEllipse->setObjectName(QStringLiteral("actionEllipse"));
        actionEllipse->setCheckable(true);
        actionPolygon = new QAction(MainWindow);
        actionPolygon->setObjectName(QStringLiteral("actionPolygon"));
        actionPolygon->setCheckable(true);
        actionCurve = new QAction(MainWindow);
        actionCurve->setObjectName(QStringLiteral("actionCurve"));
        actionCurve->setCheckable(true);
        actionPenColor = new QAction(MainWindow);
        actionPenColor->setObjectName(QStringLiteral("actionPenColor"));
        actionFillColor = new QAction(MainWindow);
        actionFillColor->setObjectName(QStringLiteral("actionFillColor"));
        actionClearCanvas = new QAction(MainWindow);
        actionClearCanvas->setObjectName(QStringLiteral("actionClearCanvas"));
        actionDeleteSelected = new QAction(MainWindow);
        actionDeleteSelected->setObjectName(QStringLiteral("actionDeleteSelected"));
        actionDeleteSelected->setShortcut(QKeySequence::Delete);
        
        actionMoveUp = new QAction(MainWindow);
        actionMoveUp->setObjectName(QStringLiteral("actionMoveUp"));
        actionMoveDown = new QAction(MainWindow);
        actionMoveDown->setObjectName(QStringLiteral("actionMoveDown"));
        actionMoveLeft = new QAction(MainWindow);
        actionMoveLeft->setObjectName(QStringLiteral("actionMoveLeft"));
        actionMoveRight = new QAction(MainWindow);
        actionMoveRight->setObjectName(QStringLiteral("actionMoveRight"));
        actionRotateCW = new QAction(MainWindow);
        actionRotateCW->setObjectName(QStringLiteral("actionRotateCW"));
        actionRotateCCW = new QAction(MainWindow);
        actionRotateCCW->setObjectName(QStringLiteral("actionRotateCCW"));

        penWidthSpinBox = new QSpinBox(propertyToolBar);
        penWidthSpinBox->setObjectName(QStringLiteral("penWidthSpinBox"));
        penWidthSpinBox->setRange(1, 20);
        penWidthSpinBox->setValue(2);
        penWidthSpinBox->setFixedWidth(60);
        
        translateDistanceSpinBox = new QSpinBox(transformToolBar);
        translateDistanceSpinBox->setObjectName(QStringLiteral("translateDistanceSpinBox"));
        translateDistanceSpinBox->setRange(1, 100);
        translateDistanceSpinBox->setValue(10);
        translateDistanceSpinBox->setFixedWidth(60);
        
        rotateAngleSpinBox = new QSpinBox(transformToolBar);
        rotateAngleSpinBox->setObjectName(QStringLiteral("rotateAngleSpinBox"));
        rotateAngleSpinBox->setRange(1, 180);
        rotateAngleSpinBox->setValue(15);
        rotateAngleSpinBox->setFixedWidth(60);

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
        
        menuTransform->addAction(actionMoveUp);
        menuTransform->addAction(actionMoveDown);
        menuTransform->addAction(actionMoveLeft);
        menuTransform->addAction(actionMoveRight);
        menuTransform->addSeparator();
        menuTransform->addAction(actionRotateCW);
        menuTransform->addAction(actionRotateCCW);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuEdit->menuAction());
        menuBar->addAction(menuDraw->menuAction());
        menuBar->addAction(menuTransform->menuAction());

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
        
        transformToolBar->addAction(actionMoveUp);
        transformToolBar->addAction(actionMoveDown);
        transformToolBar->addAction(actionMoveLeft);
        transformToolBar->addAction(actionMoveRight);
        transformToolBar->addSeparator();
        transformToolBar->addWidget(translateDistanceSpinBox);
        transformToolBar->addSeparator();
        transformToolBar->addAction(actionRotateCW);
        transformToolBar->addAction(actionRotateCCW);
        transformToolBar->addWidget(rotateAngleSpinBox);

        propertyToolBar->addAction(actionPenColor);
        propertyToolBar->addAction(actionFillColor);
        propertyToolBar->addWidget(penWidthSpinBox);
        propertyToolBar->addSeparator();
        propertyToolBar->addAction(actionClearCanvas);
        propertyToolBar->addAction(actionDeleteSelected);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    }

    void retranslateUi(QMainWindow *MainWindow) {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "EasyPicture 2026", nullptr));
        menuFile->setTitle(QApplication::translate("MainWindow", "文件", nullptr));
        menuEdit->setTitle(QApplication::translate("MainWindow", "编辑", nullptr));
        menuDraw->setTitle(QApplication::translate("MainWindow", "绘制", nullptr));
        menuTransform->setTitle(QApplication::translate("MainWindow", "变换", nullptr));
        mainToolBar->setWindowTitle(QApplication::translate("MainWindow", "文件操作", nullptr));
        drawToolBar->setWindowTitle(QApplication::translate("MainWindow", "绘制工具", nullptr));
        transformToolBar->setWindowTitle(QApplication::translate("MainWindow", "变换工具", nullptr));
        propertyToolBar->setWindowTitle(QApplication::translate("MainWindow", "属性设置", nullptr));
        actionNew->setText(QApplication::translate("MainWindow", "新建", nullptr));
        actionOpen->setText(QApplication::translate("MainWindow", "打开", nullptr));
        actionSave->setText(QApplication::translate("MainWindow", "保存", nullptr));
        actionExit->setText(QApplication::translate("MainWindow", "退出", nullptr));
        actionSelect->setText(QApplication::translate("MainWindow", "选择", nullptr));
        actionTriangle->setText(QApplication::translate("MainWindow", "三角形", nullptr));
        actionRectangle->setText(QApplication::translate("MainWindow", "矩形", nullptr));
        actionEllipse->setText(QApplication::translate("MainWindow", "椭圆", nullptr));
        actionPolygon->setText(QApplication::translate("MainWindow", "多边形", nullptr));
        actionCurve->setText(QApplication::translate("MainWindow", "曲线", nullptr));
        actionPenColor->setText(QApplication::translate("MainWindow", "线条颜色", nullptr));
        actionFillColor->setText(QApplication::translate("MainWindow", "填充颜色", nullptr));
        actionClearCanvas->setText(QApplication::translate("MainWindow", "清空画布", nullptr));
        actionDeleteSelected->setText(QApplication::translate("MainWindow", "删除选中", nullptr));
        actionMoveUp->setText(QApplication::translate("MainWindow", "上移", nullptr));
        actionMoveDown->setText(QApplication::translate("MainWindow", "下移", nullptr));
        actionMoveLeft->setText(QApplication::translate("MainWindow", "左移", nullptr));
        actionMoveRight->setText(QApplication::translate("MainWindow", "右移", nullptr));
        actionRotateCW->setText(QApplication::translate("MainWindow", "顺时针", nullptr));
        actionRotateCCW->setText(QApplication::translate("MainWindow", "逆时针", nullptr));
        addCanvasButton->setText(QApplication::translate("MainWindow", "+ 添加画布", nullptr));
        removeCanvasButton->setText(QApplication::translate("MainWindow", "- 删除画布", nullptr));
        renameCanvasButton->setText(QApplication::translate("MainWindow", "重命名", nullptr));
        translateDistanceSpinBox->setToolTip(QApplication::translate("MainWindow", "平移距离", nullptr));
        rotateAngleSpinBox->setToolTip(QApplication::translate("MainWindow", "旋转角度", nullptr));
    }
};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
}

QT_END_NAMESPACE

#endif