#include "GraphicsView.h"
#include "ShapeFactory.h"
#include <QLinearGradient>

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
            // 检查是否接近起点，如果是则完成多边形
            if (m_polygonPoints.size() >= 3 && isNearPolygonStart(event->pos())) {
                Polygon* polygon = ShapeFactory::createPolygon(m_polygonPoints);
                polygon->setPenColor(m_drawColor);
                polygon->setBrushColor(m_fillColor);
                polygon->setPenWidth(m_penWidth);
                m_scene->addShape(polygon);
                m_polygonPoints.clear();
                m_isDrawing = false;
                update();
            } else {
                if (m_polygonPoints.isEmpty()) {
                    m_isDrawing = true;
                }
                m_polygonPoints.append(event->pos());
                update();
            }
        } else if (m_currentTool == DrawCurve) {
            m_polygonPoints.append(event->pos());
            m_isDrawing = true;
            update();
        } else {
            m_isDrawing = true;
        }
    } else if (event->button() == Qt::RightButton && m_currentTool == DrawPolygon && !m_polygonPoints.isEmpty()) {
        // 右键完成多边形
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
    m_currentMousePos = event->pos();
    
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
    } else if (m_currentTool == DrawPolygon || m_currentTool == DrawCurve) {
        // 多边形或曲线模式下，实时更新预览
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

bool GraphicsView::isNearPolygonStart(const QPoint& pos) const {
    if (m_polygonPoints.isEmpty()) return false;
    
    QPoint startPoint = m_polygonPoints.first();
    int dx = pos.x() - startPoint.x();
    int dy = pos.y() - startPoint.y();
    int distance = dx * dx + dy * dy;
    
    return distance <= POLYGON_CLOSE_THRESHOLD * POLYGON_CLOSE_THRESHOLD;
}

void GraphicsView::drawGrid(QPainter* painter) {
    // 绘制背景渐变
    QRectF backgroundRect(0, 0, width(), height());
    QLinearGradient gradient(backgroundRect.topLeft(), backgroundRect.bottomRight());
    gradient.setColorAt(0, QColor(250, 250, 255));
    gradient.setColorAt(1, QColor(240, 240, 245));
    painter->fillRect(backgroundRect, gradient);
    
    // 绘制网格
    const int gridSize = 20;
    painter->setPen(QPen(QColor(220, 220, 230), 1));
    
    for (int x = 0; x < width(); x += gridSize) {
        painter->drawLine(x, 0, x, height());
    }
    for (int y = 0; y < height(); y += gridSize) {
        painter->drawLine(0, y, width(), y);
    }
    
    // 绘制更粗的主网格线
    const int majorGridSize = 100;
    painter->setPen(QPen(QColor(200, 200, 210), 1.5));
    
    for (int x = 0; x < width(); x += majorGridSize) {
        painter->drawLine(x, 0, x, height());
    }
    for (int y = 0; y < height(); y += majorGridSize) {
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
    painter->setPen(QPen(m_drawColor, m_penWidth));
    painter->setBrush(m_fillColor);
    painter->setOpacity(0.6);
    
    switch (m_currentTool) {
    case DrawTriangle: {
        if (m_isDrawing) {
            QPoint p1 = m_startPoint;
            QPoint p2(m_endPoint.x(), m_startPoint.y());
            QPoint p3((m_startPoint.x() + m_endPoint.x()) / 2, m_endPoint.y());
            QPolygon polygon;
            polygon << p1 << p2 << p3;
            painter->drawPolygon(polygon);
        }
        break;
    }
    case DrawRectangle:
        if (m_isDrawing) {
            painter->drawRect(QRect(m_startPoint, m_endPoint));
        }
        break;
    case DrawEllipse:
        if (m_isDrawing) {
            painter->drawEllipse(QRect(m_startPoint, m_endPoint));
        }
        break;
    case DrawPolygon:
        if (!m_polygonPoints.isEmpty()) {
            // 绘制已确定的边
            painter->drawPolyline(m_polygonPoints.data(), m_polygonPoints.size());
            
            // 绘制从最后一个点到当前鼠标位置的跟随直线
            painter->setOpacity(0.5);
            painter->setPen(QPen(m_drawColor, m_penWidth, Qt::DashLine));
            painter->drawLine(m_polygonPoints.last(), m_currentMousePos);
            
            // 检查是否接近起点，如果是则显示提示圆圈
            if (m_polygonPoints.size() >= 3 && isNearPolygonStart(m_currentMousePos)) {
                painter->setOpacity(1.0);
                painter->setPen(QPen(Qt::green, 2));
                painter->setBrush(Qt::NoBrush);
                painter->drawEllipse(m_polygonPoints.first(), POLYGON_CLOSE_THRESHOLD, POLYGON_CLOSE_THRESHOLD);
                
                // 在圆圈内绘制一个小圆点作为视觉提示
                painter->setBrush(Qt::green);
                painter->drawEllipse(m_polygonPoints.first(), 5, 5);
            }
            
            // 绘制所有已确定的顶点
            painter->setOpacity(1.0);
            painter->setPen(QPen(Qt::blue, 1));
            painter->setBrush(Qt::blue);
            for (const QPoint& p : m_polygonPoints) {
                painter->drawEllipse(p, 4, 4);
            }
        }
        break;
    case DrawCurve:
        if (m_polygonPoints.size() >= 1) {
            // 绘制已确定的控制点连线
            painter->drawPolyline(m_polygonPoints.data(), m_polygonPoints.size());
            
            // 绘制从最后一个点到当前鼠标位置的跟随直线
            painter->setOpacity(0.5);
            painter->setPen(QPen(m_drawColor, m_penWidth, Qt::DashLine));
            painter->drawLine(m_polygonPoints.last(), m_currentMousePos);
            
            // 绘制所有控制点
            painter->setOpacity(1.0);
            painter->setPen(QPen(Qt::blue, 1));
            painter->setBrush(Qt::blue);
            for (const QPoint& p : m_polygonPoints) {
                painter->drawEllipse(p, 4, 4);
            }
        }
        break;
    default:
        break;
    }
    
    painter->setOpacity(1.0);
}