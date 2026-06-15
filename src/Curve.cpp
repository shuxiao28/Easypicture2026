#include "Curve.h"

Curve::Curve() {
}

Curve::Curve(const QVector<QPoint>& controlPoints)
    : m_controlPoints(controlPoints)
{
}

void Curve::draw(QPainter* painter) const {
}

bool Curve::contains(const QPoint& point) const {
    return false;
}

void Curve::translate(const QPoint& offset) {
}

void Curve::rotate(qreal angle, const QPoint& center) {
}

void Curve::scale(qreal factor, const QPoint& center) {
}

QRect Curve::boundingRect() const {
    return QRect();
}

Shape::ShapeType Curve::type() const {
    return Curve;
}

void Curve::setControlPoints(const QVector<QPoint>& points) {
    m_controlPoints = points;
}

QVector<QPoint> Curve::controlPoints() const {
    return m_controlPoints;
}