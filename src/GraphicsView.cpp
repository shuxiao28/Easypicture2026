#include "GraphicsView.h"

GraphicsView::GraphicsView(QWidget* parent)
    : QWidget(parent),
      m_scene(nullptr),
      m_currentTool(SelectTool),
      m_drawColor(Qt::black),
      m_fillColor(Qt::white),
      m_penWidth(2),
      m_isDrawing(false)
{
    setMouseTracking(true);
}

GraphicsView::~GraphicsView() {
}

void GraphicsView::setScene(GraphicsScene* scene) {
    m_scene = scene;
    update();
}

void GraphicsView::setCurrentTool(ToolType tool) {
    m_currentTool = tool;
    if (tool != DrawPolygon && tool != DrawCurve) {
        m_polygonPoints.clear();
    }
}

void GraphicsView::setDrawColor(const QColor& color) {
    m_drawColor = color;
}

void GraphicsView::setFillColor(const QColor& color) {
    m_fillColor = color;
}

void GraphicsView::setPenWidth(int width) {
    m_penWidth = width;
}

void GraphicsView::paintEvent(QPaintEvent* event) {
    Q_UNUSED(event);
    QPainter painter(this);
    drawGrid(&painter);
    drawShapes(&painter);
    drawPreview(&painter);
}

void GraphicsView::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        m_startPoint = event->pos();
        m_endPoint = event->pos();
        
        if (m_currentTool == SelectTool && m_scene) {
            Shape* shape = m_scene->shapeAt(event->pos());
            if (shape) {
                m_scene->selectShape(shape);
            } else {
                m_scene->deselectAll();
            }
            update();
        } else if (m_currentTool == DrawPolygon) {
            m_polygonPoints.append(event->pos());
            m_isDrawing = true;
            update();
        } else if (m_currentTool == DrawCurve) {
            m_polygonPoints.append(event->pos());
            m_isDrawing = true;
            update();
        } else {
            m_isDrawing = true;
        }
    }
}

void GraphicsView::mouseMoveEvent(QMouseEvent* event) {
    if (m_isDrawing) {
        m_endPoint = event->pos();
        update();
    }
}

void GraphicsView::mouseReleaseEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton && m_isDrawing) {
        m_isDrawing = false;
        
        if (m_scene) {
            // TODO: 创建并添加图形到场景
        }
        
        update();
    }
}

void GraphicsView::drawGrid(QPainter* painter) {
    const int gridSize = 20;
    painter->setPen(QColor(200, 200, 200));
    
    for (int x = 0; x < width(); x += gridSize) {
        painter->drawLine(x, 0, x, height());
    }
    for (int y = 0; y < height(); y += gridSize) {
        painter->drawLine(0, y, width(), y);
    }
}

void GraphicsView::drawShapes(QPainter* painter) {
    if (!m_scene) return;
    
    for (Shape* shape : m_scene->shapes()) {
        shape->draw(painter);
    }
}

void GraphicsView::drawPreview(QPainter* painter) {
    if (!m_isDrawing) return;
    
    painter->setPen(QPen(m_drawColor, m_penWidth));
    painter->setBrush(m_fillColor);
    
    switch (m_currentTool) {
    case DrawTriangle:
        // TODO: 绘制三角形预览
        break;
    case DrawRectangle:
        painter->drawRect(QRect(m_startPoint, m_endPoint));
        break;
    case DrawEllipse:
        painter->drawEllipse(QRect(m_startPoint, m_endPoint));
        break;
    case DrawPolygon:
        if (m_polygonPoints.size() > 1) {
            painter->drawPolyline(m_polygonPoints.data(), m_polygonPoints.size());
        }
        break;
    case DrawCurve:
        if (m_polygonPoints.size() >= 2) {
            painter->drawPolyline(m_polygonPoints.data(), m_polygonPoints.size());
        }
        break;
    default:
        break;
    }
}