# 容器控件练习

本目录存放自己根据 `examples/containers/` 编写的容器控件 demo，每个页面各占一对 `.h/.cpp`，统一由 `learn` 主窗口加载。

已有练习：

- `widget.h / .cpp`：QWidget，使用复选框整体启用或禁用包含名称、0～100 目标值的参数区域，禁用期间保留输入内容。见 [开发记录](../../docs/2026-11-28-21-QWidget参数区域启用与禁用.md)。

新增练习时：

1. 创建继承 QWidget 的页面，为构造函数和其他函数补充中文注释。
2. 在根目录 `CMakeLists.txt` 的容器控件区域列出 `.h/.cpp`。
3. 在 `mainwindow.cpp` 中包含头文件并调用 `addDemo()` 注册页面。
4. 维护开发记录、根目录 README 和 `docs/Qt基本控件速查.md`，已有 ✅ 不重复标记。

QWidget 已完成独立练习；QFrame 的边框容器练习位于 `demos/display/`。下一项建议实现 QGroupBox，比较带标题分组和可勾选分组的使用方式，再学习 QTabWidget 和 QStackedWidget。参考教程见 [容器示例与完整代码](../../docs/examples/containers.md)。
