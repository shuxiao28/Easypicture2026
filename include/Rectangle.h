#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Shape.h"

class Rectangle : public Shape {
public:
    Rectangle();
    Rectangle(const QRect& rect);
    Rectangle(const QPoint& topLeft, const QPoint& bottomRight);

    void draw(QPainter* painter) const override;
    bool contains(const QPoint& point) const override;
    void translate(const QPoint& offset) override;
    void rotate(qreal angle, const QPoint& center) override;
    void scale(qreal factor, const QPoint& center) override;
    QRect boundingRect() const override;
    ShapeType type() const override;
    QString getInfo() const override;
    QPointF center() const override;

    void setRect(const QRect& rect);
    QRect rect() const;

private:
    QRect m_rect;
};

#endif