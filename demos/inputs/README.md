# 输入控件示例

本目录用于存放输入窗口部件的示例，例如 QLineEdit、QTextEdit、QSpinBox 和 QComboBox。

已有示例：

- `combobox.h / .cpp`：QComboBox，切换选项时用 `qDebug()` 输出当前选项。
- `lineedit.h / .cpp`：QLineEdit，点击“确认”后在标签上显示输入的文本并清空输入框。
- `spinbox.h / .cpp`：QSpinBox，数值变化时设置主窗口的不透明度；Wayland 桌面和 linuxfb 下没有可见效果，原因见开发日志。
- `textedit.h / .cpp`：QTextEdit，多行文本输入，通过按钮全选或清除内容。

新增示例时：

1. 在本目录创建独立的 `.h/.cpp`，页面通常继承 QWidget；为新增函数提供中文注释。
2. 在根目录 `CMakeLists.txt` 的 `add_executable(learn ...)` 输入控件区域添加两个文件的路径。
3. 在 `mainwindow.cpp` 中包含 `demos/inputs/xxx.h`，并调用 `addDemo("控件名称", new 示例类(this))` 注册页面。
4. 在 `docs/` 中记录开发日志，并更新根目录 README 的文档索引。

请使用与按钮示例不同的类名和文件名，便于 Qt AUTOMOC/AUTOUIC 生成文件和定位源码。
