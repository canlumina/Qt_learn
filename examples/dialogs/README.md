# 对话框参考示例

本目录包含 7 个示例，每个类各有一对 `.h/.cpp`，由 `widget_examples` 统一运行。

[用途、常用方式、操作步骤与完整代码](../../docs/examples/dialogs.md) · [返回示例目录](../README.md)

| 控件 | 头文件 | 实现文件 | 示例功能 |
| --- | --- | --- | --- |
| QMessageBox | [messageboxexample.h](messageboxexample.h) | [messageboxexample.cpp](messageboxexample.cpp) | 安全的模拟确认，默认选择否，不执行真实删除。 |
| QFileDialog | [filedialogexample.h](filedialogexample.h) | [filedialogexample.cpp](filedialogexample.cpp) | 选择现有文件、目录或拟保存路径，仅回显路径。 |
| QDialog | [dialogexample.h](dialogexample.h) | [dialogexample.cpp](dialogexample.cpp) | 自定义通道名称对话框，确认后回显，取消保留原值。 |
| QInputDialog | [inputdialogexample.h](inputdialogexample.h) | [inputdialogexample.cpp](inputdialogexample.cpp) | 输入通道名称或采样次数，正确区分确认与取消。 |
| QColorDialog | [colordialogexample.h](colordialogexample.h) | [colordialogexample.cpp](colordialogexample.cpp) | 选择颜色并应用到预览标签，取消保留原色。 |
| QFontDialog | [fontdialogexample.h](fontdialogexample.h) | [fontdialogexample.cpp](fontdialogexample.cpp) | 选择字体并应用到中英文预览。 |
| QProgressDialog | [progressdialogexample.h](progressdialogexample.h) | [progressdialogexample.cpp](progressdialogexample.cpp) | 定时器驱动的模拟任务，可取消并重新开始。 |
