#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QWidget>
#include <QPainter>
#include <QPoint>
#include <QMouseEvent>
#include "GraphicsScene.h"

class GraphicsView : public QWidget {
    Q_OBJECT

public:
    enum ToolType {
        SelectTool,
        DrawTriangle,
        DrawRectangle,
        DrawEllipse,
        DrawPolygon,
        DrawCurve
    };

    GraphicsView(QWidget* parent = nullptr);
    ~GraphicsView() override;

    void setScene(GraphicsScene* scene);
    void setCurrentTool(ToolType tool);
    void setDrawColor(const QColor& color);
    void setFillColor(const QColor& color);
    void setPenWidth(int width);

protected:
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

private:
    void drawGrid(QPainter* painter);
    void drawShapes(QPainter* painter);
    void drawPreview(QPainter* painter);
    
    // 检查鼠标是否接近多边形起点
    bool isNearPolygonStart(const QPoint& pos) const;

    GraphicsScene* m_scene;
    ToolType m_currentTool;
    QColor m_drawColor;
    QColor m_fillColor;
    int m_penWidth;

    QPoint m_startPoint;
    QPoint m_endPoint;
    QPoint m_currentMousePos;  // 当前鼠标位置
    QVector<QPoint> m_polygonPoints;
    bool m_isDrawing;
    bool m_isDragging;
    
    // 多边形起点接近阈值
    static const int POLYGON_CLOSE_THRESHOLD = 15;
};

#endif