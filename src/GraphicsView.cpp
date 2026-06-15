#include "GraphicsView.h"
#include "ShapeFactory.h"

GraphicsView::GraphicsView(QWidget* parent)
    : QWidget(parent),
      m_scene(nullptr),
      m_currentTool(SelectTool),
      m_drawColor(Qt::black),
      m_fillColor(Qt::white),
      m_penWidth(2),
      m_isDrawing(false),
      m_isDragging(false)
{
    setMouseTracking(true);
    setBackgroundRole(QPalette::Base);
}

GraphicsView::~GraphicsView() {
}

void GraphicsView::setScene(GraphicsScene* scene) {
    m_scene = scene;
    connect(m_scene, &GraphicsScene::sceneCleared, this, [this]() { this->update(); });
    connect(m_scene, &GraphicsScene::shapeAdded, this, [this](Shape*) { this->update(); });
    connect(m_scene, &GraphicsScene::shapeRemoved, this, [this](Shape*) { this->update(); });
    connect(m_scene, &GraphicsScene::selectionChanged, this, [this]() { this->update(); });
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
    painter.setRenderHint(QPainter::Antialiasing);
    
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
                m_isDragging = true;
                update();
            } else {
                m_scene->deselectAll();
                update();
            }
        } else if (m_currentTool == DrawPolygon) {
            if (m_polygonPoints.isEmpty()) {
                m_isDrawing = true;
            }
            m_polygonPoints.append(event->pos());
            update();
        } else if (m_currentTool == DrawCurve) {
            m_polygonPoints.append(event->pos());
            m_isDrawing = true;
            update();
        } else {
            m_isDrawing = true;
        }
    } else if (event->button() == Qt::RightButton && m_currentTool == DrawPolygon && !m_polygonPoints.isEmpty()) {
        if (m_polygonPoints.size() >= 3 && m_scene) {
            Polygon* polygon = ShapeFactory::createPolygon(m_polygonPoints);
            polygon->setPenColor(m_drawColor);
            polygon->setBrushColor(m_fillColor);
            polygon->setPenWidth(m_penWidth);
            m_scene->addShape(polygon);
        }
        m_polygonPoints.clear();
        m_isDrawing = false;
        update();
    } else if (event->button() == Qt::RightButton && m_currentTool == DrawCurve && m_polygonPoints.size() >= 2) {
        if (m_scene) {
            Curve* curve = ShapeFactory::createCurve(m_polygonPoints);
            curve->setPenColor(m_drawColor);
            curve->setPenWidth(m_penWidth);
            m_scene->addShape(curve);
        }
        m_polygonPoints.clear();
        m_isDrawing = false;
        update();
    }
}

void GraphicsView::mouseMoveEvent(QMouseEvent* event) {
    if (m_isDragging && m_currentTool == SelectTool) {
        QPoint offset = event->pos() - m_endPoint;
        if (!offset.isNull() && m_scene) {
            m_scene->translateSelected(offset);
        }
        m_endPoint = event->pos();
        update();
    } else if (m_isDrawing && m_currentTool != DrawPolygon && m_currentTool != DrawCurve) {
        m_endPoint = event->pos();
        update();
    }
}

void GraphicsView::mouseReleaseEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        if (m_isDragging) {
            m_isDragging = false;
        } else if (m_isDrawing && m_currentTool != DrawPolygon && m_currentTool != DrawCurve) {
            m_isDrawing = false;
            
            if (m_scene && m_startPoint != m_endPoint) {
                QRect rect(QPoint(std::min(m_startPoint.x(), m_endPoint.x()),
                                 std::min(m_startPoint.y(), m_endPoint.y())),
                           QPoint(std::max(m_startPoint.x(), m_endPoint.x()),
                                  std::max(m_startPoint.y(), m_endPoint.y())));
                
                Shape* shape = nullptr;
                switch (m_currentTool) {
                case DrawRectangle:
                    shape = ShapeFactory::createRectangle(rect);
                    break;
                case DrawEllipse:
                    shape = ShapeFactory::createEllipse(rect);
                    break;
                case DrawTriangle: {
                    QPoint p1 = m_startPoint;
                    QPoint p2(m_endPoint.x(), m_startPoint.y());
                    QPoint p3((m_startPoint.x() + m_endPoint.x()) / 2, m_endPoint.y());
                    shape = ShapeFactory::createTriangle(p1, p2, p3);
                    break;
                }
                default:
                    break;
                }
                
                if (shape) {
                    shape->setPenColor(m_drawColor);
                    shape->setBrushColor(m_fillColor);
                    shape->setPenWidth(m_penWidth);
                    m_scene->addShape(shape);
                }
            }
            update();
        }
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
    painter->setOpacity(0.6);
    
    switch (m_currentTool) {
    case DrawTriangle: {
        QPoint p1 = m_startPoint;
        QPoint p2(m_endPoint.x(), m_startPoint.y());
        QPoint p3((m_startPoint.x() + m_endPoint.x()) / 2, m_endPoint.y());
        QPolygon polygon;
        polygon << p1 << p2 << p3;
        painter->drawPolygon(polygon);
        break;
    }
    case DrawRectangle:
        painter->drawRect(QRect(m_startPoint, m_endPoint));
        break;
    case DrawEllipse:
        painter->drawEllipse(QRect(m_startPoint, m_endPoint));
        break;
    case DrawPolygon:
        if (m_polygonPoints.size() > 1) {
            painter->drawPolyline(m_polygonPoints.data(), m_polygonPoints.size());
            if (m_polygonPoints.size() >= 2) {
                painter->drawLine(m_polygonPoints.last(), m_polygonPoints.first());
            }
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
    
    painter->setOpacity(1.0);
}