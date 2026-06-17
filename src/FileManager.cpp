#include "FileManager.h"
#include "Rectangle.h"
#include "Ellipse.h"
#include "Triangle.h"
#include "Polygon.h"
#include "Curve.h"
#include <QFile>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QMessageBox>
#include <QRegularExpression>
#include <QTextStream>

FileManager::FileManager(QObject* parent)
    : QObject(parent)
{
}

bool FileManager::saveScene(const GraphicsScene* scene, const QString& filePath) {
    if (!scene) return false;
    
    // 根据文件扩展名选择保存格式
    if (filePath.endsWith(".txt", Qt::CaseInsensitive)) {
        return saveToText(scene, filePath);
    } else {
        return saveToSvg(scene, filePath);
    }
}

bool FileManager::loadScene(GraphicsScene* scene, const QString& filePath) {
    if (!scene) return false;
    
    // 根据文件扩展名选择加载格式
    if (filePath.endsWith(".txt", Qt::CaseInsensitive)) {
        return loadFromText(scene, filePath);
    } else {
        return loadFromSvg(scene, filePath);
    }
}

bool FileManager::saveToSvg(const GraphicsScene* scene, const QString& filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return false;
    }
    
    QXmlStreamWriter writer(&file);
    writer.setAutoFormatting(true);
    writer.writeStartDocument();
    
    writer.writeStartElement("svg");
    writer.writeAttribute("xmlns", "http://www.w3.org/2000/svg");
    writer.writeAttribute("width", "800");
    writer.writeAttribute("height", "600");
    writer.writeAttribute("viewBox", "0 0 800 600");
    
    for (Shape* shape : scene->shapes()) {
        writer.writeStartElement("g");
        
        QString fillColor = shape->brushColor().name();
        QString strokeColor = shape->penColor().name();
        int strokeWidth = shape->penWidth();
        
        writer.writeAttribute("fill", fillColor);
        writer.writeAttribute("stroke", strokeColor);
        writer.writeAttribute("stroke-width", QString::number(strokeWidth));
        
        switch (shape->type()) {
        case Shape::Rectangle: {
            Rectangle* rect = static_cast<Rectangle*>(shape);
            QRect r = rect->rect();
            writer.writeStartElement("rect");
            writer.writeAttribute("x", QString::number(r.x()));
            writer.writeAttribute("y", QString::number(r.y()));
            writer.writeAttribute("width", QString::number(r.width()));
            writer.writeAttribute("height", QString::number(r.height()));
            writer.writeEndElement();
            break;
        }
        case Shape::Ellipse: {
            Ellipse* ellipse = static_cast<Ellipse*>(shape);
            QRect r = ellipse->rect();
            writer.writeStartElement("ellipse");
            writer.writeAttribute("cx", QString::number(r.center().x()));
            writer.writeAttribute("cy", QString::number(r.center().y()));
            writer.writeAttribute("rx", QString::number(r.width() / 2));
            writer.writeAttribute("ry", QString::number(r.height() / 2));
            writer.writeEndElement();
            break;
        }
        case Shape::Triangle: {
            Triangle* tri = static_cast<Triangle*>(shape);
            QString points = QString("%1,%2 %3,%4 %5,%6")
                .arg(tri->p1().x()).arg(tri->p1().y())
                .arg(tri->p2().x()).arg(tri->p2().y())
                .arg(tri->p3().x()).arg(tri->p3().y());
            writer.writeStartElement("polygon");
            writer.writeAttribute("points", points);
            writer.writeEndElement();
            break;
        }
        case Shape::Polygon: {
            Polygon* poly = static_cast<Polygon*>(shape);
            QString points;
            for (const QPoint& p : poly->points()) {
                if (!points.isEmpty()) points += " ";
                points += QString("%1,%2").arg(p.x()).arg(p.y());
            }
            writer.writeStartElement("polygon");
            writer.writeAttribute("points", points);
            writer.writeEndElement();
            break;
        }
        case Shape::Curve: {
            Curve* curve = static_cast<Curve*>(shape);
            QString d = "M";
            for (int i = 0; i < curve->controlPoints().size(); ++i) {
                const QPoint& p = curve->controlPoints()[i];
                if (i == 0) {
                    d += QString(" %1 %2").arg(p.x()).arg(p.y());
                } else if (i % 3 == 0) {
                    d += QString(" C");
                    d += QString(" %1 %2").arg(p.x()).arg(p.y());
                } else {
                    d += QString(" %1 %2").arg(p.x()).arg(p.y());
                }
            }
            writer.writeStartElement("path");
            writer.writeAttribute("d", d);
            writer.writeAttribute("fill", "none");
            writer.writeEndElement();
            break;
        }
        }
        
        writer.writeEndElement();
    }
    
    writer.writeEndElement();
    writer.writeEndDocument();
    
    file.close();
    return true;
}

bool FileManager::loadFromSvg(GraphicsScene* scene, const QString& filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return false;
    }
    
    QXmlStreamReader reader(&file);
    scene->clear();
    
    while (!reader.atEnd()) {
        QXmlStreamReader::TokenType token = reader.readNext();
        
        if (token == QXmlStreamReader::StartElement) {
            if (reader.name() == "rect") {
                QXmlStreamAttributes attrs = reader.attributes();
                int x = attrs.value("x").toInt();
                int y = attrs.value("y").toInt();
                int w = attrs.value("width").toInt();
                int h = attrs.value("height").toInt();
                
                Rectangle* rect = new Rectangle(QRect(x, y, w, h));
                scene->addShape(rect);
            } else if (reader.name() == "ellipse") {
                QXmlStreamAttributes attrs = reader.attributes();
                int cx = attrs.value("cx").toInt();
                int cy = attrs.value("cy").toInt();
                int rx = attrs.value("rx").toInt();
                int ry = attrs.value("ry").toInt();
                
                Ellipse* ellipse = new Ellipse(QRect(cx - rx, cy - ry, rx * 2, ry * 2));
                scene->addShape(ellipse);
            } else if (reader.name() == "polygon") {
                QXmlStreamAttributes attrs = reader.attributes();
                QString pointsStr = attrs.value("points").toString();
                QStringList pointsList = pointsStr.split(" ");
                QVector<QPoint> points;
                
                for (const QString& p : pointsList) {
                    QStringList coords = p.split(",");
                    if (coords.size() == 2) {
                        points.append(QPoint(coords[0].toInt(), coords[1].toInt()));
                    }
                }
                
                if (points.size() >= 3) {
                    Polygon* poly = new Polygon(points);
                    scene->addShape(poly);
                }
            } else if (reader.name() == "path") {
                QXmlStreamAttributes attrs = reader.attributes();
                QString d = attrs.value("d").toString();
                
                QStringList tokens = d.split(" ", QString::SkipEmptyParts);
                QVector<QPoint> points;
                
                for (int i = 0; i < tokens.size(); ) {
                    if (tokens[i] == "M") {
                        i++;
                        continue;
                    }
                    if (tokens[i] == "C") {
                        i++;
                        continue;
                    }
                    if (i + 1 < tokens.size()) {
                        points.append(QPoint(tokens[i].toInt(), tokens[i+1].toInt()));
                        i += 2;
                    } else {
                        break;
                    }
                }
                
                if (points.size() >= 2) {
                    Curve* curve = new Curve(points);
                    scene->addShape(curve);
                }
            }
        }
    }
    
    file.close();
    return true;
}

// 文本格式保存 - 格式示例：矩形，（0，0），100，50
bool FileManager::saveToText(const GraphicsScene* scene, const QString& filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return false;
    }
    
    QTextStream out(&file);
    out.setCodec("UTF-8");
    
    out << "# EasyPicture 2026 图形数据文件\n";
    out << "# 格式说明：图形类型，参数...\n";
    out << "# 矩形：矩形，（中心x，中心y），宽，高\n";
    out << "# 椭圆：椭圆，（中心x，中心y），宽，高\n";
    out << "# 三角形：三角形，（点1x，点1y），（点2x，点2y），（点3x，点3y）\n";
    out << "# 多边形：多边形，（点1x，点1y），（点2x，点2y），...，（点nx，点ny）\n";
    out << "# 曲线：曲线，（点1x，点1y），（点2x，点2y），...，（点nx，点ny）\n";
    out << "\n";
    
    for (Shape* shape : scene->shapes()) {
        QString line;
        switch (shape->type()) {
        case Shape::Rectangle: {
            Rectangle* rect = static_cast<Rectangle*>(shape);
            QRect r = rect->rect();
            QPointF c = r.center();
            line = QString("矩形，（%1，%2），%3，%4")
                .arg(c.x()).arg(c.y()).arg(r.width()).arg(r.height());
            break;
        }
        case Shape::Ellipse: {
            Ellipse* ellipse = static_cast<Ellipse*>(shape);
            QRect r = ellipse->rect();
            QPointF c = r.center();
            line = QString("椭圆，（%1，%2），%3，%4")
                .arg(c.x()).arg(c.y()).arg(r.width()).arg(r.height());
            break;
        }
        case Shape::Triangle: {
            Triangle* tri = static_cast<Triangle*>(shape);
            line = QString("三角形，（%1，%2），（%3，%4），（%5，%6）")
                .arg(tri->p1().x()).arg(tri->p1().y())
                .arg(tri->p2().x()).arg(tri->p2().y())
                .arg(tri->p3().x()).arg(tri->p3().y());
            break;
        }
        case Shape::Polygon: {
            Polygon* poly = static_cast<Polygon*>(shape);
            QStringList pointStrs;
            for (const QPoint& p : poly->points()) {
                pointStrs << QString("（%1，%2）").arg(p.x()).arg(p.y());
            }
            line = "多边形，" + pointStrs.join("，");
            break;
        }
        case Shape::Curve: {
            Curve* curve = static_cast<Curve*>(shape);
            QStringList pointStrs;
            for (const QPoint& p : curve->controlPoints()) {
                pointStrs << QString("（%1，%2）").arg(p.x()).arg(p.y());
            }
            line = "曲线，" + pointStrs.join("，");
            break;
        }
        }
        
        // 添加颜色和线宽信息
        line += QString("，线条：%1，填充：%2，线宽：%3")
            .arg(shape->penColor().name())
            .arg(shape->brushColor().name())
            .arg(shape->penWidth());
        
        out << line << "\n";
    }
    
    file.close();
    return true;
}

// 文本格式加载
bool FileManager::loadFromText(GraphicsScene* scene, const QString& filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return false;
    }
    
    QTextStream in(&file);
    in.setCodec("UTF-8");
    
    scene->clear();
    
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        
        // 跳过注释和空行
        if (line.isEmpty() || line.startsWith("#")) {
            continue;
        }
        
        Shape* shape = parseTextLine(line);
        if (shape) {
            scene->addShape(shape);
        }
    }
    
    file.close();
    return true;
}

// 解析文本行中的图形数据
Shape* FileManager::parseTextLine(const QString& line) {
    // 使用正则表达式提取坐标
    QRegularExpression coordRegex("（(-?\\d+)，(-?\\d+)）");
    QRegularExpressionMatchIterator coordMatches = coordRegex.globalMatch(line);
    
    QVector<QPoint> points;
    while (coordMatches.hasNext()) {
        QRegularExpressionMatch match = coordMatches.next();
        int x = match.captured(1).toInt();
        int y = match.captured(2).toInt();
        points.append(QPoint(x, y));
    }
    
    // 提取数值参数（宽、高等）
    QRegularExpression numRegex("，(-?\\d+)");
    QRegularExpressionMatchIterator numMatches = numRegex.globalMatch(line);
    
    QVector<int> numbers;
    while (numMatches.hasNext()) {
        QRegularExpressionMatch match = numMatches.next();
        numbers.append(match.captured(1).toInt());
    }
    
    // 提取颜色和线宽
    QRegularExpression colorRegex("线条：(#\\w+)，填充：(#\\w+)，线宽：(\\d+)");
    QRegularExpressionMatch colorMatch = colorRegex.match(line);
    
    QColor penColor = Qt::black;
    QColor brushColor = Qt::white;
    int penWidth = 2;
    
    if (colorMatch.hasMatch()) {
        penColor = QColor(colorMatch.captured(1));
        brushColor = QColor(colorMatch.captured(2));
        penWidth = colorMatch.captured(3).toInt();
    }
    
    Shape* shape = nullptr;
    
    if (line.startsWith("矩形")) {
        if (points.size() >= 1 && numbers.size() >= 2) {
            QPoint center = points[0];
            int width = numbers[0];
            int height = numbers[1];
            QRect rect(center.x() - width/2, center.y() - height/2, width, height);
            shape = new Rectangle(rect);
        }
    } else if (line.startsWith("椭圆")) {
        if (points.size() >= 1 && numbers.size() >= 2) {
            QPoint center = points[0];
            int width = numbers[0];
            int height = numbers[1];
            QRect rect(center.x() - width/2, center.y() - height/2, width, height);
            shape = new Ellipse(rect);
        }
    } else if (line.startsWith("三角形")) {
        if (points.size() >= 3) {
            shape = new Triangle(points[0], points[1], points[2]);
        }
    } else if (line.startsWith("多边形")) {
        if (points.size() >= 3) {
            shape = new Polygon(points);
        }
    } else if (line.startsWith("曲线")) {
        if (points.size() >= 2) {
            shape = new Curve(points);
        }
    }
    
    if (shape) {
        shape->setPenColor(penColor);
        shape->setBrushColor(brushColor);
        shape->setPenWidth(penWidth);
    }
    
    return shape;
}