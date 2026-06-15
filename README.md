# EasyPicture 2026

一个基于Qt的简易矢量图形生成系统。

## 功能特性

- 支持绘制多种基本图形：三角形、矩形、椭圆、多边形、曲线
- 图形属性设置：线条颜色、填充颜色、线条宽度
- 图形选择和编辑功能
- 文件保存和加载（SVG格式）

## 项目结构

```
Easypicture2026/
├── include/          # 头文件目录
│   ├── Shape.h       # 图形抽象基类
│   ├── Triangle.h    # 三角形类
│   ├── Rectangle.h   # 矩形类
│   ├── Ellipse.h     # 椭圆类
│   ├── Polygon.h     # 多边形类
│   ├── Curve.h       # 曲线类
│   ├── GraphicsScene.h    # 场景管理器
│   ├── GraphicsView.h     # 视图组件
│   ├── MainWindow.h       # 主窗口
│   ├── FileManager.h      # 文件管理
│   └── ShapeFactory.h     # 图形工厂
├── src/              # 源文件目录
│   ├── main.cpp      # 程序入口
│   ├── Shape.cpp
│   ├── Triangle.cpp
│   ├── Rectangle.cpp
│   ├── Ellipse.cpp
│   ├── Polygon.cpp
│   ├── Curve.cpp
│   ├── GraphicsScene.cpp
│   ├── GraphicsView.cpp
│   ├── MainWindow.cpp
│   ├── FileManager.cpp
│   └── ShapeFactory.cpp
├── ui/               # UI设计文件
├── resources/        # 资源文件
│   └── resources.qrc
└── Easypicture2026.pro   # Qt项目文件
```

## 编译运行

使用Qt Creator打开项目文件 `Easypicture2026.pro`，然后编译运行。

## 开发环境

- Qt 5.15 或更高版本
- C++11 或更高版本