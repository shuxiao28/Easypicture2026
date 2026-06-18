#-------------------------------------------------
# EasyPicture 2026 - Qt Vector Graphics Editor
#-------------------------------------------------

QT       += core gui widgets svg

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Easypicture2026
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    src/main.cpp \
    src/Shape.cpp \
    src/Triangle.cpp \
    src/Rectangle.cpp \
    src/Ellipse.cpp \
    src/Polygon.cpp \
    src/Curve.cpp \
    src/GraphicsScene.cpp \
    src/GraphicsView.cpp \
    src/MainWindow.cpp \
    src/FileManager.cpp \
    src/ShapeFactory.cpp \
    src/CanvasManager.cpp \
    src/PropertiesDialog.cpp

HEADERS += \
    include/Shape.h \
    include/Triangle.h \
    include/Rectangle.h \
    include/Ellipse.h \
    include/Polygon.h \
    include/Curve.h \
    include/GraphicsScene.h \
    include/GraphicsView.h \
    include/MainWindow.h \
    include/FileManager.h \
    include/ShapeFactory.h \
    include/CanvasManager.h \
    include/PropertiesDialog.h \
    ui_mainwindow.h

INCLUDEPATH += $$PWD/include

RESOURCES += \
    resources/resources.qrc

FORMS += \
    ui/mainwindow.ui \
    ui/PropertiesDialog.ui

CONFIG += c++11

QMAKE_CXXFLAGS += -Wall -Wextra

win32 {
    QMAKE_CXXFLAGS += -D_WIN32_WINNT=0x0601
}

unix {
    QMAKE_CXXFLAGS += -fPIC
}

contains(QT_CONFIG, svg): QT += svg