# QGraphicsView：图形选择、拖动与视图缩放

日期：2026-11-28

## 本次练习

在 `demos/display/graphicsview.h / .cpp` 实现 `GraphicsView` 页面，通过 `learn` 主窗口的 `QGraphicsView` 项打开。页面继承 QWidget，使用 QVBoxLayout 放置说明、缩放按钮和图形视图，视图的伸缩因子为 1。

QGraphicsView 用于显示和交互操作二维图形，适合流程图、图形编辑器或设备示意图。最常见的组合是：QGraphicsScene 管理图形项，QGraphicsView 显示场景，QGraphicsItem 表示可绘制、可交互的图形。本练习创建矩形和椭圆，支持鼠标选择与拖动，按钮控制放大、缩小和缩放复位。

## 关键实现

```cpp
auto *scene = new QGraphicsScene(this);
scene->setSceneRect(0, 0, 420, 240);
auto *rectangle = scene->addRect(30, 40, 120, 70,
                               QPen(Qt::darkBlue), QBrush(QColor("#8bdce0")));
auto *ellipse = scene->addEllipse(180, 40, 120, 70,
                                QPen(Qt::darkRed), QBrush(QColor("#f0c0c0")));
rectangle->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
ellipse->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);

auto *view = new QGraphicsView(scene, this);
view->setRenderHint(QPainter::Antialiasing);
```

以上为代码节选，完整布局、按钮及信号连接见 `demos/display/graphicsview.cpp`。

- `setSceneRect(0, 0, 420, 240)` 指定场景区域，用于视图显示和滚动范围计算；本例没有限制图形只能在该矩形内移动。
- `addRect()`、`addEllipse()` 创建图形项并交给场景管理；QPen 设置轮廓，QBrush 设置填充颜色。
- `ItemIsSelectable` 允许选择图形，`ItemIsMovable` 允许鼠标拖动，配合使用即可练习交互。
- `scale(1.2, 1.2)` 等比例放大视图，`scale(1.0 / 1.2, 1.0 / 1.2)` 缩小；改变的是视图变换，图形本身的几何和场景位置不随缩放修改。
- 当前通过 `transform().m11()` 判断缩放：小于 4.0 才允许继续放大，大于 0.3 才允许继续缩小。判断发生在操作前，因此最终比例可能略超 4.0 或略低于 0.3，并非严格钳制到这两个端点。
- “复位”连接 `resetTransform()`，恢复原始缩放比例；不撤销图形的拖动位置，也不表示自动适配全部图形到窗口。
- 页面及场景、视图、按钮由 Qt 父子对象机制管理，场景负责释放图形项；本例无需自定义析构函数。界面操作须在 GUI 线程进行。

## 文件和学习进度

- 新增 `demos/display/graphicsview.h / .cpp`，补充构造函数、放大和缩小回调的中文注释，说明缩放阈值与复位的实际含义。
- 根 `CMakeLists.txt` 将源码加入 `learn`；`mainwindow.cpp` 包含头文件并注册页面。
- 更新显示分类 README、根 README 文档索引和控件速查的分类汇总，保留已有 `✅ QGraphicsView` 并注明已完成个人练习。
- 显示类可继续学习 QTextBrowser；图形视图后续可尝试图形分组和场景坐标转换。

## 验证

沿用现有 Qt 5.15.2、系统 C++ 编译器和 Ninja 配置，提交前检查 `learn` 目标：

```bash
cmake --build build/qt5 --target learn --parallel 4
```

上述命令执行成功，`learn` 目标编译、链接通过；差异空白、文档相对链接及敏感字段检查通过。

真实桌面的鼠标拖动、选择高亮、抗锯齿外观和缩放后的滚动效果，以及 Qt 6 和开发板表现需单独验证。建议分别拖动两个图形，连续点击放大、缩小，再点击复位，确认图形恢复原始显示比例且保留移动后的场景位置。
