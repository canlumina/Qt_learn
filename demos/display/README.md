# 显示控件练习

本目录存放自己根据 `examples/display/` 编写的显示控件 demo，每个页面各占一对 `.h/.cpp`，统一由 `learn` 主窗口加载。

已有练习：

- `lable.h / .cpp`：QLabel，显示可选择并复制的纯文本、自动换行的说明文字和 160×80 色块图片；点击“改变颜色”按钮在蓝色与橙色之间切换。见 [开发记录](../../docs/2026-11-27-17-QLabel文字与图片显示.md)。
- `progressbar.h / .cpp`：QProgressBar，QTimer 每 80 ms 模拟增加 2 个百分点，支持忙碌模式与重新开始；退出忙碌模式恢复实际进度，完成后停止定时器并显示 100%。见 [开发记录](../../docs/2026-11-28-18-QProgressBar进度与忙碌模式.md)。
- `graphicsview.h / .cpp`：QGraphicsView，场景中显示可选择、可拖动的矩形与椭圆，按钮控制放大、缩小和缩放复位；复位保留图形移动后的位置。见 [开发记录](../../docs/2026-11-28-19-QGraphicsView图形拖动与缩放.md)。

新增练习时：

1. 创建继承 QWidget 的页面，为构造函数及其他函数补充中文注释。
2. 在根目录 `CMakeLists.txt` 的显示控件区域列出 `.h/.cpp`。
3. 在 `mainwindow.cpp` 中包含头文件并调用 `addDemo()` 注册页面。
4. 维护开发记录、根目录 README 和 `docs/Qt基本控件速查.md`，已有 ✅ 不重复标记。

QLabel、QProgressBar、QGraphicsView 已完成独立练习，建议接着实现 QTextBrowser，练习只读富文本和链接交互。参考教程见 [显示控件示例与完整代码](../../docs/examples/display.md)。
