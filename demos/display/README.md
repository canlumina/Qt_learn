# 显示控件练习

本目录存放自己根据 `examples/display/` 编写的显示控件 demo，每个页面各占一对 `.h/.cpp`，统一由 `learn` 主窗口加载。

已有练习：

- `lable.h / .cpp`：QLabel，显示可选择并复制的纯文本、自动换行的说明文字和 160×80 色块图片；点击“改变颜色”按钮在蓝色与橙色之间切换。见 [开发记录](../../docs/2026-11-27-17-QLabel文字与图片显示.md)。

新增练习时：

1. 创建继承 QWidget 的页面，为构造函数及其他函数补充中文注释。
2. 在根目录 `CMakeLists.txt` 的显示控件区域列出 `.h/.cpp`。
3. 在 `mainwindow.cpp` 中包含头文件并调用 `addDemo()` 注册页面。
4. 维护开发记录、根目录 README 和 `docs/Qt基本控件速查.md`，已有 ✅ 不重复标记。

QLabel 已完成独立练习，建议接着实现 QProgressBar，练习进度范围和数值更新。参考教程见 [显示控件示例与完整代码](../../docs/examples/display.md)。
