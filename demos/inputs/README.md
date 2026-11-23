# 输入控件示例

本目录用于存放输入窗口部件的示例，例如 QLineEdit、QTextEdit、QSpinBox 和 QComboBox。

已有示例：

- `combobox.h / .cpp`：QComboBox，切换选项时用 `qDebug()` 输出当前选项。
- `lineedit.h / .cpp`：QLineEdit，点击“确认”后在标签上显示输入的文本并清空输入框。
- `spinbox.h / .cpp`：QSpinBox，数值变化时设置主窗口的不透明度；Wayland 桌面和 linuxfb 下没有可见效果，原因见开发日志。
- `textedit.h / .cpp`：QTextEdit，富文本格式、段落对齐、剪贴板操作、撤销重做、循环查找和实时字符统计；清空全文可撤销。
- `plaintextedit.h / .cpp`：QPlainTextEdit，读取可执行文件同目录的 UTF-8 `text.txt`，用单选按钮切换只读状态；打开失败会提示完整路径和原因，编辑内容不自动保存。见 [开发记录](../../docs/2026-11-24-12-QPlainTextEdit读取文本.md)。

新增示例时：

1. 在本目录创建独立的 `.h/.cpp`，页面通常继承 QWidget；为新增函数提供中文注释。
2. 在根目录 `CMakeLists.txt` 的 `add_executable(learn ...)` 输入控件区域添加两个文件的路径。
3. 在 `mainwindow.cpp` 中包含 `demos/inputs/xxx.h`，并调用 `addDemo("控件名称", new 示例类(this))` 注册页面。
4. 在 `docs/` 中记录开发日志，并更新根目录 README 的文档索引。
5. 完成示例后更新 `docs/Qt基本控件速查.md`，在对应控件名称前添加 `✅`，同步维护文末学习进度。

请使用与按钮示例不同的类名和文件名，便于 Qt AUTOMOC/AUTOUIC 生成文件和定位源码。
