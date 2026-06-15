#include "ShapeFactory.h"

Shape* ShapeFactory::createShape(Shape::ShapeType type) {
    switch (type) {
    case Shape::Triangle:
        return new Triangle(QPoint(0, 0), QPoint(50, 0), QPoint(25, 50));
    case Shape::Rectangle:
        return new Rectangle(QRect(0, 0, 50, 50));
    case Shape::Ellipse:
        return new Ellipse(QRect(0, 0, 50, 50));
    case Shape::Polygon:
        return new Polygon(QVector<QPoint>());
    case Shape::Curve:
        return new Curve();
    default:
        return nullptr;
    }
}

Triangle* ShapeFactory::createTriangle(const QPoint& p1, const QPoint& p2, const QPoint& p3) {
    return new Triangle(p1, p2, p3);
}

Rectangle* ShapeFactory::createRectangle(const QRect& rect) {
    return new Rectangle(rect);
}

Ellipse* ShapeFactory::createEllipse(const QRect& rect) {
    return new Ellipse(rect);
}

Polygon* ShapeFactory::createPolygon(const QVector<QPoint>& points) {
    return new Polygon(points);
}

Curve* ShapeFactory::createCurve(const QVector<QPoint>& controlPoints) {
    return new Curve(controlPoints);
}