QT       += core gui widgets svg

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
    src/ShapeFactory.cpp

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
    include/ShapeFactory.h

INCLUDEPATH += $$PWD/include

RESOURCES += \
    resources/resources.qrc

FORMS += \
    ui/mainwindow.ui

CONFIG += c++11

QMAKE_CXXFLAGS += -Wall -Wextra

