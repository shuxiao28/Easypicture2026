#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H

#include <QObject>
#include <QList>
#include <QPoint>
#include "Shape.h"

class GraphicsScene : public QObject {
    Q_OBJECT

public:
    GraphicsScene(QObject* parent = nullptr);
    ~GraphicsScene() override;

    void addShape(Shape* shape);
    void removeShape(Shape* shape);
    void selectShape(Shape* shape);
    void selectMultiple(const QList<Shape*>& shapes);
    void deselectAll();
    void clear();
    void deleteSelected();

    QList<Shape*> shapes() const;
    QList<Shape*> selectedShapes() const;
    Shape* shapeAt(const QPoint& point) const;
    bool hasSelection() const;

    void translateSelected(const QPoint& offset);
    void rotateSelected(qreal angle, const QPoint& center);
    void scaleSelected(qreal factor, const QPoint& center);

signals:
    void shapeAdded(Shape* shape);
    void shapeRemoved(Shape* shape);
    void selectionChanged();
    void sceneCleared();

private:
    QList<Shape*> m_shapes;
    QList<Shape*> m_selectedShapes;
};

#endif