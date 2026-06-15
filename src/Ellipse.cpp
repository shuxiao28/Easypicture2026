#include "Ellipse.h"

Ellipse::Ellipse() {
}

Ellipse::Ellipse(const QRect& rect)
    : m_rect(rect)
{
}

void Ellipse::draw(QPainter* painter) const {
}

bool Ellipse::contains(const QPoint& point) const {
    return false;
}

void Ellipse::translate(const QPoint& offset) {
}

void Ellipse::rotate(qreal angle, const QPoint& center) {
}

void Ellipse::scale(qreal factor, const QPoint& center) {
}

QRect Ellipse::boundingRect() const {
    return m_rect;
}

Shape::ShapeType Ellipse::type() const {
    return Ellipse;
}

void Ellipse::setRect(const QRect& rect) {
    m_rect = rect;
}

QRect Ellipse::rect() const {
    return m_rect;
}