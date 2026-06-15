#include "GraphicsScene.h"

GraphicsScene::GraphicsScene(QObject* parent)
    : QObject(parent)
{
}

GraphicsScene::~GraphicsScene() {
    clear();
}

void GraphicsScene::addShape(Shape* shape) {
    if (shape) {
        m_shapes.append(shape);
        emit shapeAdded(shape);
    }
}

void GraphicsScene::removeShape(Shape* shape) {
    if (m_shapes.removeOne(shape)) {
        m_selectedShapes.removeOne(shape);
        delete shape;
        emit shapeRemoved(shape);
        emit selectionChanged();
    }
}

void GraphicsScene::selectShape(Shape* shape) {
    if (!shape) return;
    
    for (Shape* s : m_selectedShapes) {
        s->setSelected(false);
    }
    m_selectedShapes.clear();
    
    shape->setSelected(true);
    m_selectedShapes.append(shape);
    emit selectionChanged();
}

void GraphicsScene::deselectAll() {
    for (Shape* s : m_selectedShapes) {
        s->setSelected(false);
    }
    m_selectedShapes.clear();
    emit selectionChanged();
}

void GraphicsScene::clear() {
    for (Shape* s : m_shapes) {
        delete s;
    }
    m_shapes.clear();
    m_selectedShapes.clear();
    emit sceneCleared();
}

QList<Shape*> GraphicsScene::shapes() const {
    return m_shapes;
}

QList<Shape*> GraphicsScene::selectedShapes() const {
    return m_selectedShapes;
}

Shape* GraphicsScene::shapeAt(const QPoint& point) const {
    for (auto it = m_shapes.rbegin(); it != m_shapes.rend(); ++it) {
        if ((*it)->contains(point)) {
            return *it;
        }
    }
    return nullptr;
}

void GraphicsScene::translateSelected(const QPoint& offset) {
    for (Shape* s : m_selectedShapes) {
        s->translate(offset);
    }
}

void GraphicsScene::rotateSelected(qreal angle, const QPoint& center) {
    for (Shape* s : m_selectedShapes) {
        s->rotate(angle, center);
    }
}

void GraphicsScene::scaleSelected(qreal factor, const QPoint& center) {
    for (Shape* s : m_selectedShapes) {
        s->scale(factor, center);
    }
}