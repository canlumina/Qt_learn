# 布局练习

本目录存放自己根据 `examples/layouts/` 编写的布局 demo，每个页面各占一对 `.h/.cpp`，统一由 `learn` 主窗口加载。

已有练习：

- `vboxlayout.h / .cpp`：QVBoxLayout，从上到下放置说明、编辑区和按钮；通过 `addWidget(editor, 1)` 为编辑区分配额外高度，按钮仅演示排列。见 [开发记录](../../docs/2026-11-25-13-QVBoxLayout纵向布局.md)。
- `hboxlayout.h / .cpp`：QHBoxLayout，横向排列说明、设备名称输入行和状态标签；输入框分配额外宽度，点击“应用”回显输入。见 [开发记录](../../docs/2026-11-25-14-QHBoxLayout横向布局.md)。

新增练习时：

1. 创建继承 QWidget 的页面，为构造函数和其他函数补充中文说明。
2. 在根目录 `CMakeLists.txt` 的布局练习区域列出 `.h/.cpp`。
3. 在 `mainwindow.cpp` 中包含头文件并调用 `addDemo()` 注册页面。
4. 维护开发记录、根目录 README 和 `docs/Qt基本控件速查.md`，已有 ✅ 不重复标记。

QVBoxLayout、QHBoxLayout 已完成独立练习，建议接着实现 QGridLayout、QFormLayout，再组合嵌套布局与弹簧。参考教程见 [布局示例与完整代码](../../docs/examples/layouts.md)。
