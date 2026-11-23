# 输入控件参考示例

本目录包含 10 个示例，每个类各有一对 `.h/.cpp`，由 `widget_examples` 统一运行。

[用途、常用方式、操作步骤与完整代码](../../docs/examples/inputs.md) · [返回示例目录](../README.md)

| 控件 | 头文件 | 实现文件 | 示例功能 |
| --- | --- | --- | --- |
| QDoubleSpinBox | [doublespinboxexample.h](doublespinboxexample.h) | [doublespinboxexample.cpp](doublespinboxexample.cpp) | 输入目标温度，实时显示取到的数值。 |
| QPlainTextEdit | [plaintexteditexample.h](plaintexteditexample.h) | [plaintexteditexample.cpp](plaintexteditexample.cpp) | 追加模拟采样日志，可切换只读、清空并限制为 100 段。 |
| QSlider | [sliderexample.h](sliderexample.h) | [sliderexample.cpp](sliderexample.cpp) | 滑块与数值框双向同步，显示模拟亮度百分比。 |
| QDateEdit | [dateeditexample.h](dateeditexample.h) | [dateeditexample.cpp](dateeditexample.cpp) | 带日历弹窗的日期输入，选择后显示 ISO 日期。 |
| QTimeEdit | [timeeditexample.h](timeeditexample.h) | [timeeditexample.cpp](timeeditexample.cpp) | 编辑模拟定时任务的执行时间。 |
| QDateTimeEdit | [datetimeeditexample.h](datetimeeditexample.h) | [datetimeeditexample.cpp](datetimeeditexample.cpp) | 设置模拟预约时间，回显本地日期时间。 |
| QDial | [dialexample.h](dialexample.h) | [dialexample.cpp](dialexample.cpp) | 用旋钮调整模拟输出百分比。 |
| QScrollBar | [scrollbarexample.h](scrollbarexample.h) | [scrollbarexample.cpp](scrollbarexample.cpp) | 模拟在 0～900 的数据偏移中移动。 |
| QFontComboBox | [fontcomboboxexample.h](fontcomboboxexample.h) | [fontcomboboxexample.cpp](fontcomboboxexample.cpp) | 为预览文字切换字体，保留固定字号。 |
| QKeySequenceEdit | [keysequenceeditexample.h](keysequenceeditexample.h) | [keysequenceeditexample.cpp](keysequenceeditexample.cpp) | 录入快捷键，焦点离开录入框后按该快捷键更新计数。 |
