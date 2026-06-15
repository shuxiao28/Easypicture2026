#include "Polygon.h"

Polygon::Polygon() {
}

Polygon::Polygon(const QVector<QPoint>& points)
    : m_points(points)
{
}

void Polygon::draw(QPainter* painter) const {
}

bool Polygon::contains(const QPoint& point) const {
    return false;
}

void Polygon::translate(const QPoint& offset) {
}

void Polygon::rotate(qreal angle, const QPoint& center) {
}

void Polygon::scale(qreal factor, const QPoint& center) {
}

QRect Polygon::boundingRect() const {
    return QRect();
}

Shape::ShapeType Polygon::type() const {
    return Polygon;
}

void Polygon::setPoints(const QVector<QPoint>& points) {
    m_points = points;
}

QVector<QPoint> Polygon::points() const {
    return m_points;
}