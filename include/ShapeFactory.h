#ifndef SHAPEFACTORY_H
#define SHAPEFACTORY_H

#include "Shape.h"
#include "Triangle.h"
#include "Rectangle.h"
#include "Ellipse.h"
#include "Polygon.h"
#include "Curve.h"

class ShapeFactory {
public:
    static Shape* createShape(Shape::ShapeType type);
    static Triangle* createTriangle(const QPoint& p1, const QPoint& p2, const QPoint& p3);
    static Rectangle* createRectangle(const QRect& rect);
    static Ellipse* createEllipse(const QRect& rect);
    static Polygon* createPolygon(const QVector<QPoint>& points);
    static Curve* createCurve(const QVector<QPoint>& controlPoints);
};

#endif