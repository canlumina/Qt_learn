# 主窗口参考示例

本目录包含 6 个示例，每个类各有一对 `.h/.cpp`，由 `widget_examples` 统一运行。

[用途、常用方式、操作步骤与完整代码](../../docs/examples/windows.md) · [返回示例目录](../README.md)

| 控件 | 头文件 | 实现文件 | 示例功能 |
| --- | --- | --- | --- |
| QMainWindow | [mainwindowexample.h](mainwindowexample.h) | [mainwindowexample.cpp](mainwindowexample.cpp) | 嵌入一个具备菜单、工具栏和状态栏的小主窗口。 |
| QMenuBar | [menubarexample.h](menubarexample.h) | [menubarexample.cpp](menubarexample.cpp) | 操作和帮助两个菜单，触发后回显。 |
| QMenu | [menuexample.h](menuexample.h) | [menuexample.cpp](menuexample.cpp) | 文本区右键菜单，包含全选、清空和换行开关。 |
| QAction | [actionexample.h](actionexample.h) | [actionexample.cpp](actionexample.cpp) | 一个“显示网格”动作同时放进工具栏和菜单，状态自动同步。 |
| QToolBar | [toolbarexample.h](toolbarexample.h) | [toolbarexample.cpp](toolbarexample.cpp) | 带刷新动作和模式下拉框的工具栏。 |
| QStatusBar | [statusbarexample.h](statusbarexample.h) | [statusbarexample.cpp](statusbarexample.cpp) | 左边显示会超时消失的消息，右边保留演示模式状态。 |
