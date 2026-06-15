#define _USE_MATH_DEFINES
#include "Curve.h"
#include <cmath>
#include <algorithm>

Curve::Curve() {
}

Curve::Curve(const QVector<QPoint>& controlPoints)
    : m_controlPoints(controlPoints)
{
}

void Curve::draw(QPainter* painter) const {
    if (m_controlPoints.size() < 2) return;
    
    painter->save();
    
    QPen pen(m_penColor, m_penWidth);
    if (m_selected) {
        pen.setStyle(Qt::DashLine);
    }
    painter->setPen(pen);
    
    if (m_controlPoints.size() == 2) {
        painter->drawLine(m_controlPoints[0], m_controlPoints[1]);
    } else {
        QPainterPath path;
        path.moveTo(m_controlPoints[0]);
        
        for (int i = 0; i < m_controlPoints.size() - 1; i += 3) {
            if (i + 3 <= m_controlPoints.size()) {
                path.cubicTo(
                    m_controlPoints[i + 1],
                    m_controlPoints[i + 2],
                    m_controlPoints[std::min(i + 3, m_controlPoints.size() - 1)]
                );
            } else if (i + 2 <= m_controlPoints.size()) {
                path.lineTo(m_controlPoints[i + 1]);
            }
        }
        
        painter->drawPath(path);
    }
    
    if (m_selected) {
        painter->setPen(QPen(Qt::blue, 1));
        painter->setBrush(Qt::blue);
        for (const QPoint& p : m_controlPoints) {
            painter->drawEllipse(p, 4, 4);
        }
    }
    
    painter->restore();
}

bool Curve::contains(const QPoint& point) const {
    if (m_controlPoints.size() < 2) return false;
    
    int tolerance = 8;
    
    if (m_controlPoints.size() == 2) {
        QPoint p1 = m_controlPoints[0];
        QPoint p2 = m_controlPoints[1];
        
        int dx = p2.x() - p1.x();
        int dy = p2.y() - p1.y();
        int len2 = dx * dx + dy * dy;
        
        if (len2 == 0) {
            int dist2 = (point.x() - p1.x()) * (point.x() - p1.x()) + 
                        (point.y() - p1.y()) * (point.y() - p1.y());
            return dist2 < tolerance * tolerance;
        }
        
        qreal t = qMax(0.0, qMin(1.0, ((point.x() - p1.x()) * dx + (point.y() - p1.y()) * dy) / (qreal)len2));
        QPoint projection(p1.x() + t * dx, p1.y() + t * dy);
        
        int dist2 = (point.x() - projection.x()) * (point.x() - projection.x()) + 
                    (point.y() - projection.y()) * (point.y() - projection.y());
        return dist2 < tolerance * tolerance;
    }
    
    QPainterPath path;
    path.moveTo(m_controlPoints[0]);
    
    for (int i = 0; i < m_controlPoints.size() - 1; i += 3) {
        if (i + 3 <= m_controlPoints.size()) {
            path.cubicTo(
                m_controlPoints[i + 1],
                m_controlPoints[i + 2],
                m_controlPoints[std::min(i + 3, m_controlPoints.size() - 1)]
            );
        } else if (i + 2 <= m_controlPoints.size()) {
            path.lineTo(m_controlPoints[i + 1]);
        }
    }
    
    return path.contains(point);
}

void Curve::translate(const QPoint& offset) {
    for (int i = 0; i < m_controlPoints.size(); ++i) {
        m_controlPoints[i] += offset;
    }
}

void Curve::rotate(qreal angle, const QPoint& center) {
    if (angle == 0) return;
    
    qreal rad = angle * M_PI / 180.0;
    qreal cosA = cos(rad);
    qreal sinA = sin(rad);
    
    for (int i = 0; i < m_controlPoints.size(); ++i) {
        int dx = m_controlPoints[i].x() - center.x();
        int dy = m_controlPoints[i].y() - center.y();
        m_controlPoints[i].setX(center.x() + dx * cosA - dy * sinA);
        m_controlPoints[i].setY(center.y() + dx * sinA + dy * cosA);
    }
}

void Curve::scale(qreal factor, const QPoint& center) {
    for (int i = 0; i < m_controlPoints.size(); ++i) {
        int dx = m_controlPoints[i].x() - center.x();
        int dy = m_controlPoints[i].y() - center.y();
        m_controlPoints[i].setX(center.x() + dx * factor);
        m_controlPoints[i].setY(center.y() + dy * factor);
    }
}

QRect Curve::boundingRect() const {
    if (m_controlPoints.isEmpty()) return QRect();
    
    int minX = m_controlPoints[0].x();
    int maxX = m_controlPoints[0].x();
    int minY = m_controlPoints[0].y();
    int maxY = m_controlPoints[0].y();
    
    for (const QPoint& p : m_controlPoints) {
        minX = std::min(minX, p.x());
        maxX = std::max(maxX, p.x());
        minY = std::min(minY, p.y());
        maxY = std::max(maxY, p.y());
    }
    
    return QRect(QPoint(minX, minY), QPoint(maxX, maxY)).adjusted(-5, -5, 5, 5);
}

Shape::ShapeType Curve::type() const {
    return Shape::Curve;
}

void Curve::setControlPoints(const QVector<QPoint>& points) {
    m_controlPoints = points;
}

QVector<QPoint> Curve::controlPoints() const {
    return m_controlPoints;
}