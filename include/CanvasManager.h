#ifndef CANVASMANAGER_H
#define CANVASMANAGER_H

#include <QString>
#include <QList>
#include "GraphicsScene.h"

class CanvasManager {
public:
    CanvasManager();
    
    void addCanvas();
    void addCanvas(const QString& name);
    void removeCanvas(int index);
    void renameCanvas(int index, const QString& name);
    void switchCanvas(int index);
    
    GraphicsScene* currentScene() const;
    QStringList canvasNames() const;
    int currentIndex() const;
    int canvasCount() const;

private:
    QList<GraphicsScene*> m_scenes;
    QList<QString> m_names;
    int m_currentIndex;
};

#endif