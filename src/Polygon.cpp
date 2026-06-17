#define _USE_MATH_DEFINES
#include "Polygon.h"
#include <cmath>

Polygon::Polygon() {
}

Polygon::Polygon(const QVector<QPoint>& points)
    : m_points(points)
{
}

void Polygon::draw(QPainter* painter) const {
    if (m_points.size() < 3) return;
    
    painter->save();
    
    QPen pen(m_penColor, m_penWidth);
    if (m_selected) {
        pen.setStyle(Qt::DashLine);
    }
    painter->setPen(pen);
    painter->setBrush(m_brushColor);
    
    painter->drawPolygon(m_points);
    
    if (m_selected) {
        painter->setPen(QPen(Qt::blue, 1));
        painter->setBrush(Qt::blue);
        for (const QPoint& p : m_points) {
            painter->drawEllipse(p, 4, 4);
        }
    }
    
    painter->restore();
}

bool Polygon::contains(const QPoint& point) const {
    if (m_points.size() < 3) return false;
    
    QPolygon polygon(m_points);
    return polygon.containsPoint(point, Qt::OddEvenFill);
}

void Polygon::translate(const QPoint& offset) {
    for (int i = 0; i < m_points.size(); ++i) {
        m_points[i] += offset;
    }
}

void Polygon::rotate(qreal angle, const QPoint& center) {
    if (angle == 0) return;
    
    qreal rad = angle * M_PI / 180.0;
    qreal cosA = cos(rad);
    qreal sinA = sin(rad);
    
    for (int i = 0; i < m_points.size(); ++i) {
        int dx = m_points[i].x() - center.x();
        int dy = m_points[i].y() - center.y();
        m_points[i].setX(center.x() + dx * cosA - dy * sinA);
        m_points[i].setY(center.y() + dx * sinA + dy * cosA);
    }
}

void Polygon::scale(qreal factor, const QPoint& center) {
    for (int i = 0; i < m_points.size(); ++i) {
        int dx = m_points[i].x() - center.x();
        int dy = m_points[i].y() - center.y();
        m_points[i].setX(center.x() + dx * factor);
        m_points[i].setY(center.y() + dy * factor);
    }
}

QRect Polygon::boundingRect() const {
    if (m_points.isEmpty()) return QRect();
    
    int minX = m_points[0].x();
    int maxX = m_points[0].x();
    int minY = m_points[0].y();
    int maxY = m_points[0].y();
    
    for (const QPoint& p : m_points) {
        minX = std::min(minX, p.x());
        maxX = std::max(maxX, p.x());
        minY = std::min(minY, p.y());
        maxY = std::max(maxY, p.y());
    }
    
    return QRect(QPoint(minX, minY), QPoint(maxX, maxY)).adjusted(-5, -5, 5, 5);
}

Shape::ShapeType Polygon::type() const {
    return Shape::Polygon;
}

QString Polygon::getInfo() const {
    QPointF c = center();
    QRect rect = boundingRect();
    return QString("多边形(%1边) - 中心: (%2, %3) 尺寸: %4 x %5").arg(m_points.size()).arg(c.x()).arg(c.y()).arg(rect.width()).arg(rect.height());
}

QPointF Polygon::center() const {
    if (m_points.isEmpty()) return QPointF(0, 0);
    
    qreal x = 0, y = 0;
    for (const QPoint& p : m_points) {
        x += p.x();
        y += p.y();
    }
    return QPointF(x / m_points.size(), y / m_points.size());
}

void Polygon::setPoints(const QVector<QPoint>& points) {
    m_points = points;
}

QVector<QPoint> Polygon::points() const {
    return m_points;
}