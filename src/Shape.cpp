#include "Shape.h"

Shape::Shape()
    : m_penColor(Qt::black),
      m_brushColor(Qt::white),
      m_penWidth(2),
      m_selected(false)
{
}

void Shape::setPenColor(const QColor& color) {
    m_penColor = color;
}

void Shape::setBrushColor(const QColor& color) {
    m_brushColor = color;
}

void Shape::setPenWidth(int width) {
    m_penWidth = width;
}

void Shape::setSelected(bool selected) {
    m_selected = selected;
}

QColor Shape::penColor() const {
    return m_penColor;
}

QColor Shape::brushColor() const {
    return m_brushColor;
}

int Shape::penWidth() const {
    return m_penWidth;
}

bool Shape::isSelected() const {
    return m_selected;
}