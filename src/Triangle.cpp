#define _USE_MATH_DEFINES
#include "Triangle.h"
#include <QPainterPath>
#include <cmath>

Triangle::Triangle() {
}

Triangle::Triangle(const QPoint& p1, const QPoint& p2, const QPoint& p3)
    : m_p1(p1), m_p2(p2), m_p3(p3)
{
}

void Triangle::draw(QPainter* painter) const {
    painter->save();
    
    QPen pen(m_penColor, m_penWidth);
    if (m_selected) {
        pen.setStyle(Qt::DashLine);
    }
    painter->setPen(pen);
    painter->setBrush(m_brushColor);
    
    QPolygon polygon;
    polygon << m_p1 << m_p2 << m_p3;
    painter->drawPolygon(polygon);
    
    if (m_selected) {
        painter->setPen(QPen(Qt::blue, 1));
        painter->setBrush(Qt::blue);
        painter->drawEllipse(m_p1, 4, 4);
        painter->drawEllipse(m_p2, 4, 4);
        painter->drawEllipse(m_p3, 4, 4);
    }
    
    painter->restore();
}

bool Triangle::contains(const QPoint& point) const {
    QPolygon polygon;
    polygon << m_p1 << m_p2 << m_p3;
    return polygon.containsPoint(point, Qt::OddEvenFill);
}

void Triangle::translate(const QPoint& offset) {
    m_p1 += offset;
    m_p2 += offset;
    m_p3 += offset;
}

void Triangle::rotate(qreal angle, const QPoint& center) {
    qreal rad = angle * M_PI / 180.0;
    qreal cosA = cos(rad);
    qreal sinA = sin(rad);
    
    auto rotatePoint = [&](QPoint& p) {
        int dx = p.x() - center.x();
        int dy = p.y() - center.y();
        p.setX(center.x() + dx * cosA - dy * sinA);
        p.setY(center.y() + dx * sinA + dy * cosA);
    };
    
    rotatePoint(m_p1);
    rotatePoint(m_p2);
    rotatePoint(m_p3);
}

void Triangle::scale(qreal factor, const QPoint& center) {
    auto scalePoint = [&](QPoint& p) {
        int dx = p.x() - center.x();
        int dy = p.y() - center.y();
        p.setX(center.x() + dx * factor);
        p.setY(center.y() + dy * factor);
    };
    
    scalePoint(m_p1);
    scalePoint(m_p2);
    scalePoint(m_p3);
}

QRect Triangle::boundingRect() const {
    QPolygon polygon;
    polygon << m_p1 << m_p2 << m_p3;
    return polygon.boundingRect().adjusted(-5, -5, 5, 5);
}

Shape::ShapeType Triangle::type() const {
    return Shape::Triangle;
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