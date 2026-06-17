#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QObject>
#include <QString>
#include "GraphicsScene.h"

class FileManager : public QObject {
    Q_OBJECT

public:
    FileManager(QObject* parent = nullptr);

    bool saveScene(const GraphicsScene* scene, const QString& filePath);
    bool loadScene(GraphicsScene* scene, const QString& filePath);
    
    // 文本格式保存和加载
    bool saveToText(const GraphicsScene* scene, const QString& filePath);
    bool loadFromText(GraphicsScene* scene, const QString& filePath);

private:
    bool saveToSvg(const GraphicsScene* scene, const QString& filePath);
    bool loadFromSvg(GraphicsScene* scene, const QString& filePath);
    
    // 解析文本行中的图形数据
    Shape* parseTextLine(const QString& line);
};

#endif