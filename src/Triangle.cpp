#include "Triangle.h"

Triangle::Triangle() {
}

Triangle::Triangle(const QPoint& p1, const QPoint& p2, const QPoint& p3)
    : m_p1(p1), m_p2(p2), m_p3(p3)
{
}

void Triangle::draw(QPainter* painter) const {
}

bool Triangle::contains(const QPoint& point) const {
    return false;
}

void Triangle::translate(const QPoint& offset) {
}

void Triangle::rotate(qreal angle, const QPoint& center) {
}

void Triangle::scale(qreal factor, const QPoint& center) {
}

QRect Triangle::boundingRect() const {
    return QRect();
}

Shape::ShapeType Triangle::type() const {
    return Triangle;
}

void Triangle::setPoints(const QPoint& p1, const QPoint& p2, const QPoint& p3) {
    m_p1 = p1;
    m_p2 = p2;
    m_p3 = p3;
}

QPoint Triangle::p1() const {
    return m_p1;
}

QPoint Triangle::p2() const {
    return m_p2;
}

QPoint Triangle::p3() const {
    return m_p3;
}