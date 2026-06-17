#ifndef POLYGON_H
#define POLYGON_H

#include "Shape.h"
#include <QVector>

class Polygon : public Shape {
public:
    Polygon();
    Polygon(const QVector<QPoint>& points);

    void draw(QPainter* painter) const override;
    bool contains(const QPoint& point) const override;
    void translate(const QPoint& offset) override;
    void rotate(qreal angle, const QPoint& center) override;
    void scale(qreal factor, const QPoint& center) override;
    QRect boundingRect() const override;
    ShapeType type() const override;
    QString getInfo() const override;
    QPointF center() const override;

    void setPoints(const QVector<QPoint>& points);
    QVector<QPoint> points() const;

private:
    QVector<QPoint> m_points;
};

#endif