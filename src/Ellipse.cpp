#include "Ellipse.h"

Ellipse::Ellipse() {
}

Ellipse::Ellipse(const QRect& rect)
    : m_rect(rect)
{
}

void Ellipse::draw(QPainter* painter) const {
    painter->save();
    
    QPen pen(m_penColor, m_penWidth);
    if (m_selected) {
        pen.setStyle(Qt::DashLine);
    }
    painter->setPen(pen);
    painter->setBrush(m_brushColor);
    
    painter->drawEllipse(m_rect);
    
    if (m_selected) {
        painter->setPen(QPen(Qt::blue, 1));
        painter->setBrush(Qt::blue);
        painter->drawEllipse(m_rect.topLeft(), 4, 4);
        painter->drawEllipse(m_rect.topRight(), 4, 4);
        painter->drawEllipse(m_rect.bottomLeft(), 4, 4);
        painter->drawEllipse(m_rect.bottomRight(), 4, 4);
    }
    
    painter->restore();
}

bool Ellipse::contains(const QPoint& point) const {
    QRect r = m_rect;
    if (r.width() <= 0 || r.height() <= 0) return false;
    
    qreal rx = r.width() / 2.0;
    qreal ry = r.height() / 2.0;
    qreal cx = r.left() + rx;
    qreal cy = r.top() + ry;
    
    qreal dx = point.x() - cx;
    qreal dy = point.y() - cy;
    
    return (dx * dx) / (rx * rx) + (dy * dy) / (ry * ry) <= 1.0;
}

void Ellipse::translate(const QPoint& offset) {
    m_rect.translate(offset);
}

void Ellipse::rotate(qreal angle, const QPoint& center) {
    if (angle == 0) return;
    
    qreal rad = angle * M_PI / 180.0;
    qreal cosA = cos(rad);
    qreal sinA = sin(rad);
    
    QRect newRect;
    QPoint points[4] = {
        m_rect.topLeft(),
        m_rect.topRight(),
        m_rect.bottomLeft(),
        m_rect.bottomRight()
    };
    
    for (int i = 0; i < 4; ++i) {
        int dx = points[i].x() - center.x();
        int dy = points[i].y() - center.y();
        points[i].setX(center.x() + dx * cosA - dy * sinA);
        points[i].setY(center.y() + dx * sinA + dy * cosA);
    }
    
    int minX = std::min({points[0].x(), points[1].x(), points[2].x(), points[3].x()});
    int maxX = std::max({points[0].x(), points[1].x(), points[2].x(), points[3].x()});
    int minY = std::min({points[0].y(), points[1].y(), points[2].y(), points[3].y()});
    int maxY = std::max({points[0].y(), points[1].y(), points[2].y(), points[3].y()});
    
    m_rect = QRect(QPoint(minX, minY), QPoint(maxX, maxY));
}

void Ellipse::scale(qreal factor, const QPoint& center) {
    QPoint tl = m_rect.topLeft();
    QPoint br = m_rect.bottomRight();
    
    int dx1 = tl.x() - center.x();
    int dy1 = tl.y() - center.y();
    int dx2 = br.x() - center.x();
    int dy2 = br.y() - center.y();
    
    tl.setX(center.x() + dx1 * factor);
    tl.setY(center.y() + dy1 * factor);
    br.setX(center.x() + dx2 * factor);
    br.setY(center.y() + dy2 * factor);
    
    m_rect = QRect(tl, br);
}

QRect Ellipse::boundingRect() const {
    return m_rect.adjusted(-5, -5, 5, 5);
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