# QFormLayout：参数表单与换行策略

记录日期：2026-11-27。源码与主窗口注册已于 2026-11-26 提交并推送，提交为 `ebecc49`；本次补充开发记录、学习进度和中文函数注释，保留已有提交历史。

## 本次练习

在 `demos/layouts/formlayout.h / .cpp` 实现 `FormLayout` 页面，通过主窗口的 `QFormLayout` 项打开。页面继承 QWidget，顶层 QVBoxLayout 放置说明标签与 QFormLayout。

表单包含设备名称、采样周期和备注。设备名称、备注使用 QLineEdit，采样周期使用 QSpinBox，范围为 10～1000，显示 `ms` 后缀。当前仅练习参数输入和布局，没有保存配置、输入联动或硬件访问。

## 关键实现

```cpp
auto *form = new QFormLayout;
form->setRowWrapPolicy(QFormLayout::WrapAllRows);
form->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);

auto *name = new QLineEdit(this);
auto *period = new QSpinBox(this);
period->setRange(10, 1000);
period->setSuffix(" ms");
auto *note = new QLineEdit(this);
form->addRow(tr("设备名称"), name);
form->addRow(tr("采样周期"), period);
form->addRow(tr("备注"), note);
layout->addLayout(form);
```

以上为代码节选，完整实现见 `demos/layouts/formlayout.cpp`。

- `addRow()` 将标签和输入控件组成一个逻辑表单项。
- 当前 `WrapAllRows` 始终将输入控件放在标签下一行，并非仅在窗口变窄时换行。若要宽度不足时才换行，可比较 `WrapLongRows`；`DontWrapRows` 保持标签与输入在同一行。
- `AllNonFixedFieldsGrow` 允许非固定宽度的输入控件使用额外宽度；具体大小仍受最小、最大尺寸等约束。
- 页面边距为 12，整体顶部对齐。Qt 父子所有权负责布局及控件的释放，本例没有独立申请的外部资源。

## 文件和学习进度

- 已有提交包含 `.h/.cpp`、CMake 源码清单和主窗口注册，本次不重复提交或改写历史。
- 为构造函数补充中文功能、参数和 GUI 线程说明，修正换行策略注释并清理相关行末空白；页面行为保持原样。
- 同步布局分类 README、根 README 文档索引和控件速查，保留已有 `✅ QFormLayout`，注明已完成个人练习。
- 下一项布局练习推进到 QSpacerItem，之后可组合嵌套布局并比较换行策略。

## 验证

沿用当前 Qt 5.15.2、系统 C++ 编译器及 Ninja 配置：

```bash
cmake --build build/qt5 --target learn --parallel 4
```

上述命令执行成功，`learn` 目标编译、链接通过；差异空白、文档相对链接及敏感字段检查通过。

尚未逐项手动验证真实桌面的输入、窗口缩放及字体显示，也未验证 Qt 6 或开发板。建议运行后分别替换三种换行策略，观察标签与输入控件的排列，并调整窗口宽度比较差异。
