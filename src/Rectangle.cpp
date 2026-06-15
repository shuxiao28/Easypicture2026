#include "Rectangle.h"

Rectangle::Rectangle() {
}

Rectangle::Rectangle(const QRect& rect)
    : m_rect(rect)
{
}

Rectangle::Rectangle(const QPoint& topLeft, const QPoint& bottomRight)
    : m_rect(QRect(topLeft, bottomRight))
{
}

void Rectangle::draw(QPainter* painter) const {
}

bool Rectangle::contains(const QPoint& point) const {
    return false;
}

void Rectangle::translate(const QPoint& offset) {
}

void Rectangle::rotate(qreal angle, const QPoint& center) {
}

void Rectangle::scale(qreal factor, const QPoint& center) {
}

QRect Rectangle::boundingRect() const {
    return m_rect;
}

Shape::ShapeType Rectangle::type() const {
    return Rectangle;
}

void Rectangle::setRect(const QRect& rect) {
    m_rect = rect;
}

QRect Rectangle::rect() const {
    return m_rect;
}