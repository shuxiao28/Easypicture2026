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
    painter->save();
    
    QPen pen(m_penColor, m_penWidth);
    if (m_selected) {
        pen.setStyle(Qt::DashLine);
    }
    painter->setPen(pen);
    painter->setBrush(m_brushColor);
    
    painter->drawRect(m_rect);
    
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

bool Rectangle::contains(const QPoint& point) const {
    return m_rect.contains(point);
}

void Rectangle::translate(const QPoint& offset) {
    m_rect.translate(offset);
}

void Rectangle::rotate(qreal angle, const QPoint& center) {
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

void Rectangle::scale(qreal factor, const QPoint& center) {
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

QRect Rectangle::boundingRect() const {
    return m_rect.adjusted(-5, -5, 5, 5);
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