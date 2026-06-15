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

    GraphicsScene* m_scene;
    ToolType m_currentTool;
    QColor m_drawColor;
    QColor m_fillColor;
    int m_penWidth;

    QPoint m_startPoint;
    QPoint m_endPoint;
    QVector<QPoint> m_polygonPoints;
    bool m_isDrawing;
    bool m_isDragging;
};

#endif