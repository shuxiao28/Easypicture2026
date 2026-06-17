#include "CanvasManager.h"

CanvasManager::CanvasManager()
    : m_currentIndex(-1)
{
}

void CanvasManager::addCanvas() {
    QString name = QString("Canvas %1").arg(m_scenes.size() + 1);
    addCanvas(name);
}

void CanvasManager::addCanvas(const QString& name) {
    GraphicsScene* scene = new GraphicsScene();
    m_scenes.append(scene);
    m_names.append(name);
    m_currentIndex = m_scenes.size() - 1;
}

void CanvasManager::removeCanvas(int index) {
    if (index < 0 || index >= m_scenes.size()) return;
    
    GraphicsScene* scene = m_scenes.takeAt(index);
    m_names.takeAt(index);
    delete scene;
    
    if (m_currentIndex >= m_scenes.size()) {
        m_currentIndex = qMax(0, m_scenes.size() - 1);
    }
}

void CanvasManager::renameCanvas(int index, const QString& name) {
    if (index < 0 || index >= m_names.size()) return;
    
    m_names[index] = name;
}

void CanvasManager::switchCanvas(int index) {
    if (index < 0 || index >= m_scenes.size()) return;
    
    m_currentIndex = index;
}

GraphicsScene* CanvasManager::currentScene() const {
    if (m_currentIndex >= 0 && m_currentIndex < m_scenes.size()) {
        return m_scenes[m_currentIndex];
    }
    return nullptr;
}

QStringList CanvasManager::canvasNames() const {
    return m_names;
}

int CanvasManager::currentIndex() const {
    return m_currentIndex;
}

int CanvasManager::canvasCount() const {
    return m_scenes.size();
}