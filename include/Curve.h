#ifndef CURVE_H
#define CURVE_H

#include "Shape.h"
#include <QVector>

class Curve : public Shape {
public:
    Curve();
    Curve(const QVector<QPoint>& controlPoints);

    void draw(QPainter* painter) const override;
    bool contains(const QPoint& point) const override;
    void translate(const QPoint& offset) override;
    void rotate(qreal angle, const QPoint& center) override;
    void scale(qreal factor, const QPoint& center) override;
    QRect boundingRect() const override;
    ShapeType type() const override;

    void setControlPoints(const QVector<QPoint>& points);
    QVector<QPoint> controlPoints() const;

private:
    QVector<QPoint> m_controlPoints;
};

#endif