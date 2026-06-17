#ifndef SHAPE_H
#define SHAPE_H

#include <QPainter>
#include <QPoint>
#include <QRect>
#include <QColor>

class Shape {
public:
    enum ShapeType {
        Triangle,
        Rectangle,
        Ellipse,
        Polygon,
        Curve
    };

    Shape();
    virtual ~Shape() = default;

    virtual void draw(QPainter* painter) const = 0;
    virtual bool contains(const QPoint& point) const = 0;
    virtual void translate(const QPoint& offset) = 0;
    virtual void rotate(qreal angle, const QPoint& center) = 0;
    virtual void scale(qreal factor, const QPoint& center) = 0;
    virtual QRect boundingRect() const = 0;
    virtual ShapeType type() const = 0;
    
    virtual QString getInfo() const = 0;
    virtual QPointF center() const = 0;

    void setPenColor(const QColor& color);
    void setBrushColor(const QColor& color);
    void setPenWidth(int width);
    void setSelected(bool selected);

    QColor penColor() const;
    QColor brushColor() const;
    int penWidth() const;
    bool isSelected() const;

protected:
    QColor m_penColor;
    QColor m_brushColor;
    int m_penWidth;
    bool m_selected;
};

#endif