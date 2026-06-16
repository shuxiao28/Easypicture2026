# EasyPicture 2026

一个基于 Qt 的简易矢量图形生成系统。

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
│   └── mainwindow.ui
├── resources/        # 资源文件
│   └── resources.qrc
└── Easypicture2026.pro   # Qt项目文件
```

## 环境要求

| 组件 | 版本要求 |
|------|----------|
| Qt | 5.12.x 或更高版本 |
| C++标准 | C++11 或更高 |
| 编译器 | MinGW 7.3+ / MSVC 2017+ / GCC 5+ |

## 编译步骤

### 使用 Qt Creator（推荐）

1. 打开 Qt Creator
2. 文件 → 打开文件或项目
3. 选择 `Easypicture2026.pro`
4. 在 "Configure Project" 界面：
   - 选择正确的构建套件（Kit）
   - 确保已安装 Qt SVG 模块
5. 点击 "Configure"
6. 点击构建按钮（绿色三角形）

### 使用命令行

```bash
# 进入项目目录
cd Easypicture2026

# 使用 qmake 生成 Makefile
qmake Easypicture2026.pro

# 编译项目
make
# 或者使用 MinGW
mingw32-make

# 运行程序
./release/Easypicture2026.exe
```

## 常见问题

### 问题 1：Qt SVG module not found

**原因**：缺少 Qt SVG 模块

**解决方案**：
1. 打开 Qt Maintenance Tool
2. 选择已安装的 Qt 版本
3. 勾选 "Qt SVG" 组件
4. 点击 "更新"

### 问题 2：Compiler not found

**原因**：工具链未配置

**解决方案**：
1. 打开 Qt Creator → 工具 → 选项 → Kits
2. 添加或选择正确的编译器（MinGW/MSVC）
3. 确保 Qt 版本与编译器匹配

### 问题 3：项目配置警告

**原因**：`.pro.user` 文件包含本地配置

**解决方案**：
1. 删除项目目录中的 `.pro.user` 文件
2. 重新打开项目
3. 重新配置构建套件

### 问题 4：头文件找不到

**原因**：包含路径配置问题

**解决方案**：
1. 确保 `INCLUDEPATH += $$PWD/include` 在 `.pro` 文件中
2. 检查头文件路径是否正确

## 开发说明

### 添加新图形类型

1. 在 `include/` 目录创建新头文件（如 `Circle.h`）
2. 在 `src/` 目录创建源文件（如 `Circle.cpp`）
3. 继承 `Shape` 基类并实现纯虚函数
4. 在 `ShapeFactory.cpp` 中添加创建逻辑
5. 在 `Easypicture2026.pro` 中添加文件

### 修改界面

1. 使用 Qt Designer 打开 `ui/mainwindow.ui`
2. 设计界面布局
3. Qt Creator 会自动生成 `ui_mainwindow.h`

## 许可证

MIT License

## 贡献

欢迎提交 Issue 和 Pull Request！