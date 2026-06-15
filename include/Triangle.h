#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Shape.h"

class Triangle : public Shape {
public:
    Triangle();
    Triangle(const QPoint& p1, const QPoint& p2, const QPoint& p3);

    void draw(QPainter* painter) const override;
    bool contains(const QPoint& point) const override;
    void translate(const QPoint& offset) override;
    void rotate(qreal angle, const QPoint& center) override;
    void scale(qreal factor, const QPoint& center) override;
    QRect boundingRect() const override;
    ShapeType type() const override;

    void setPoints(const QPoint& p1, const QPoint& p2, const QPoint& p3);
    QPoint p1() const;
    QPoint p2() const;
    QPoint p3() const;

private:
    QPoint m_p1;
    QPoint m_p2;
    QPoint m_p3;
};

#endif