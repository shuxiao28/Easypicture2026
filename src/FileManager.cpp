#include "FileManager.h"
#include <QFile>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QMessageBox>

FileManager::FileManager(QObject* parent)
    : QObject(parent)
{
}

bool FileManager::saveScene(const GraphicsScene* scene, const QString& filePath) {
    if (!scene) return false;
    
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

bool FileManager::loadScene(GraphicsScene* scene, const QString& filePath) {
    if (!scene) return false;
    
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
                
                QStringList tokens = d.split(" ", Qt::SkipEmptyParts);
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