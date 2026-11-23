# 布局示例与完整代码

[返回学习路线](README.md)

## QVBoxLayout

**是什么**：将子控件从上到下排列的布局。

**用途**：纵向表单、页面整体结构。

**最常用的方式**：addWidget()、addLayout()、addStretch()、setContentsMargins()。下面的实现展示创建控件、配置初始值，再用信号槽处理变化。

**本 demo**：标题、可伸缩编辑区、底部操作按钮纵向排列。

**操作步骤**：缩放窗口，观察编辑区扩展而按钮仍在底部。

全部示例在 GUI 线程操作控件；QObject 子对象由父对象释放。未出现显式资源释放代码时，仍应检查模型、场景、布局项和对话框的所有权。

### 头文件：`examples/layouts/vboxlayoutexample.h`

```cpp
#ifndef VBOXLAYOUTEXAMPLE_H
#define VBOXLAYOUTEXAMPLE_H

#include <QWidget>

/** @brief QVBoxLayout 练习页：标题、可伸缩编辑区、底部操作按钮纵向排列。 */
class VBoxLayoutExample : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief 初始化QVBoxLayout示例及信号槽
     * @param parent 父控件，可为空；页面和子对象遵循 Qt 父子所有权
     * @note 无返回值；在 QApplication 创建后的 GUI 线程调用，不执行硬件操作。
     */
    explicit VBoxLayoutExample(QWidget *parent = nullptr);
};

#endif
```

### 实现文件：`examples/layouts/vboxlayoutexample.cpp`

```cpp
#include "vboxlayoutexample.h"

#include <QLabel>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QVBoxLayout>

VBoxLayoutExample::VBoxLayoutExample(QWidget *parent)
    : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(12, 12, 12, 12);
    layout->setAlignment(Qt::AlignTop);
    auto *description = new QLabel(tr("标题、可伸缩编辑区、底部操作按钮纵向排列。"), this);
    description->setWordWrap(true);
    layout->addWidget(description);
    // 所有界面操作在 GUI 线程；子控件由 Qt 的父子对象机制自动释放。
    // 页面顶层 layout 本身就是 QVBoxLayout；stretch=1 的编辑区优先分配额外高度。
    auto *editor = new QPlainTextEdit(this);
    editor->setPlainText(tr("这里是可以伸缩的主要内容区域。"));
    layout->addWidget(new QLabel(tr("顶部说明"), this));
    layout->addWidget(editor, 1);
    layout->addWidget(new QPushButton(tr("底部按钮（仅演示布局）"), this));
}
```

## QHBoxLayout

**是什么**：将子控件从左到右排列的布局。

**用途**：一排按钮、标签加输入框。

**最常用的方式**：addWidget()、addStretch()、setSpacing()。下面的实现展示创建控件、配置初始值，再用信号槽处理变化。

**本 demo**：标签、可伸缩输入框、提交按钮位于同一行。

**操作步骤**：调整窗口宽度；输入框占据剩余空间，按钮尺寸保持合理。

全部示例在 GUI 线程操作控件；QObject 子对象由父对象释放。未出现显式资源释放代码时，仍应检查模型、场景、布局项和对话框的所有权。

### 头文件：`examples/layouts/hboxlayoutexample.h`

```cpp
#ifndef HBOXLAYOUTEXAMPLE_H
#define HBOXLAYOUTEXAMPLE_H

#include <QWidget>

/** @brief QHBoxLayout 练习页：标签、可伸缩输入框、提交按钮位于同一行。 */
class HBoxLayoutExample : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief 初始化QHBoxLayout示例及信号槽
     * @param parent 父控件，可为空；页面和子对象遵循 Qt 父子所有权
     * @note 无返回值；在 QApplication 创建后的 GUI 线程调用，不执行硬件操作。
     */
    explicit HBoxLayoutExample(QWidget *parent = nullptr);
};

#endif
```

### 实现文件：`examples/layouts/hboxlayoutexample.cpp`

```cpp
#include "hboxlayoutexample.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>

HBoxLayoutExample::HBoxLayoutExample(QWidget *parent)
    : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(12, 12, 12, 12);
    layout->setAlignment(Qt::AlignTop);
    auto *description = new QLabel(tr("标签、可伸缩输入框、提交按钮位于同一行。"), this);
    description->setWordWrap(true);
    layout->addWidget(description);
    // 所有界面操作在 GUI 线程；子控件由 Qt 的父子对象机制自动释放。
    auto *row = new QHBoxLayout;
    auto *input = new QLineEdit(this);
    auto *apply = new QPushButton(tr("应用"), this);
    auto *status = new QLabel(tr("等待输入"), this);
    status->setTextFormat(Qt::PlainText);
    status->setWordWrap(true);
    row->addWidget(new QLabel(tr("设备名称："), this));
    row->addWidget(input, 1);
    row->addWidget(apply);
    layout->addLayout(row);
    layout->addWidget(status);
    /** @brief 显示输入；无参数、无返回值；只更新纯文本标签，不连接真实设备。 */
    connect(apply, &QPushButton::clicked, this, [input, status] { status->setText(input->text()); });
}
```

## QGridLayout

**是什么**：按行列网格放置控件，支持跨行跨列。

**用途**：仪表面板、计算器、复杂表单。

**最常用的方式**：addWidget(widget,row,column,rowSpan,columnSpan) 、setColumnStretch()。下面的实现展示创建控件、配置初始值，再用信号槽处理变化。

**本 demo**：三行模拟通道输入与一个跨三列的说明。

**操作步骤**：输入各通道值，缩放窗口观察列宽。

全部示例在 GUI 线程操作控件；QObject 子对象由父对象释放。未出现显式资源释放代码时，仍应检查模型、场景、布局项和对话框的所有权。

### 头文件：`examples/layouts/gridlayoutexample.h`

```cpp
#ifndef GRIDLAYOUTEXAMPLE_H
#define GRIDLAYOUTEXAMPLE_H

#include <QWidget>

/** @brief QGridLayout 练习页：三行模拟通道输入与一个跨三列的说明。 */
class GridLayoutExample : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief 初始化QGridLayout示例及信号槽
     * @param parent 父控件，可为空；页面和子对象遵循 Qt 父子所有权
     * @note 无返回值；在 QApplication 创建后的 GUI 线程调用，不执行硬件操作。
     */
    explicit GridLayoutExample(QWidget *parent = nullptr);
};

#endif
```

### 实现文件：`examples/layouts/gridlayoutexample.cpp`

```cpp
#include "gridlayoutexample.h"

#include <QCheckBox>
#include <QGridLayout>
#include <QLabel>
#include <QSpinBox>
#include <QVBoxLayout>

GridLayoutExample::GridLayoutExample(QWidget *parent)
    : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(12, 12, 12, 12);
    layout->setAlignment(Qt::AlignTop);
    auto *description = new QLabel(tr("三行模拟通道输入与一个跨三列的说明。"), this);
    description->setWordWrap(true);
    layout->addWidget(description);
    // 所有界面操作在 GUI 线程；子控件由 Qt 的父子对象机制自动释放。
    auto *grid = new QGridLayout;
    grid->addWidget(new QLabel(tr("通道"), this), 0, 0);
    grid->addWidget(new QLabel(tr("目标值"), this), 0, 1);
    grid->addWidget(new QLabel(tr("启用"), this), 0, 2);
    for (int row = 1; row <= 3; ++row) {
        grid->addWidget(new QLabel(tr("通道 %1").arg(row), this), row, 0);
        auto *value = new QSpinBox(this);
        value->setRange(0, 1000);
        grid->addWidget(value, row, 1);
        grid->addWidget(new QCheckBox(this), row, 2);
    }
    grid->setColumnStretch(1, 1);
    grid->addWidget(new QLabel(tr("本说明跨越三列，不访问硬件。"), this), 4, 0, 1, 3);
    layout->addLayout(grid);
}
```

## QFormLayout

**是什么**：以标签和输入控件两列组织表单。

**用途**：设置、参数输入、个人信息页。

**最常用的方式**：addRow()、setFieldGrowthPolicy()、setRowWrapPolicy()。下面的实现展示创建控件、配置初始值，再用信号槽处理变化。

**本 demo**：设备名称、采样周期、备注组成一个可伸缩表单。

**操作步骤**：输入不同参数，缩窄窗口观察表单换行。

全部示例在 GUI 线程操作控件；QObject 子对象由父对象释放。未出现显式资源释放代码时，仍应检查模型、场景、布局项和对话框的所有权。

### 头文件：`examples/layouts/formlayoutexample.h`

```cpp
#ifndef FORMLAYOUTEXAMPLE_H
#define FORMLAYOUTEXAMPLE_H

#include <QWidget>

/** @brief QFormLayout 练习页：设备名称、采样周期、备注组成一个可伸缩表单。 */
class FormLayoutExample : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief 初始化QFormLayout示例及信号槽
     * @param parent 父控件，可为空；页面和子对象遵循 Qt 父子所有权
     * @note 无返回值；在 QApplication 创建后的 GUI 线程调用，不执行硬件操作。
     */
    explicit FormLayoutExample(QWidget *parent = nullptr);
};

#endif
```

### 实现文件：`examples/layouts/formlayoutexample.cpp`

```cpp
#include "formlayoutexample.h"

#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include <QVBoxLayout>

FormLayoutExample::FormLayoutExample(QWidget *parent)
    : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(12, 12, 12, 12);
    layout->setAlignment(Qt::AlignTop);
    auto *description = new QLabel(tr("设备名称、采样周期、备注组成一个可伸缩表单。"), this);
    description->setWordWrap(true);
    layout->addWidget(description);
    // 所有界面操作在 GUI 线程；子控件由 Qt 的父子对象机制自动释放。
    auto *form = new QFormLayout;
    form->setRowWrapPolicy(QFormLayout::WrapLongRows);
    form->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
    auto *name = new QLineEdit(this);
    auto *period = new QSpinBox(this);
    period->setRange(10, 10000);
    period->setSuffix(tr(" ms"));
    auto *note = new QLineEdit(this);
    form->addRow(tr("设备名称："), name);
    form->addRow(tr("采样周期："), period);
    form->addRow(tr("备注："), note);
    layout->addLayout(form);
}
```

## QStackedLayout

**是什么**：让多个页面共用位置，默认一次显示一个。

**用途**：在现有 QWidget 容器中切换多页内容。

**最常用的方式**：addWidget()、setCurrentIndex()、setStackingMode()。下面的实现展示创建控件、配置初始值，再用信号槽处理变化。

**本 demo**：下拉框切换两个布局页面。

**操作步骤**：切换下拉框，观察一个显示页被另一个替代。

**注意事项**：布局不是 QWidget，不能当作页面传给 addWidget；先给 QWidget 设置布局。

全部示例在 GUI 线程操作控件；QObject 子对象由父对象释放。未出现显式资源释放代码时，仍应检查模型、场景、布局项和对话框的所有权。

### 头文件：`examples/layouts/stackedlayoutexample.h`

```cpp
#ifndef STACKEDLAYOUTEXAMPLE_H
#define STACKEDLAYOUTEXAMPLE_H

#include <QWidget>

/** @brief QStackedLayout 练习页：下拉框切换两个布局页面。 */
class StackedLayoutExample : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief 初始化QStackedLayout示例及信号槽
     * @param parent 父控件，可为空；页面和子对象遵循 Qt 父子所有权
     * @note 无返回值；在 QApplication 创建后的 GUI 线程调用，不执行硬件操作。
     */
    explicit StackedLayoutExample(QWidget *parent = nullptr);
};

#endif
```

### 实现文件：`examples/layouts/stackedlayoutexample.cpp`

```cpp
#include "stackedlayoutexample.h"

#include <QComboBox>
#include <QLabel>
#include <QStackedLayout>
#include <QVBoxLayout>
#include <QWidget>
#include <QtGlobal>

StackedLayoutExample::StackedLayoutExample(QWidget *parent)
    : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(12, 12, 12, 12);
    layout->setAlignment(Qt::AlignTop);
    auto *description = new QLabel(tr("下拉框切换两个布局页面。"), this);
    description->setWordWrap(true);
    layout->addWidget(description);
    // 所有界面操作在 GUI 线程；子控件由 Qt 的父子对象机制自动释放。
    auto *select = new QComboBox(this);
    select->addItems({ tr("概览"), tr("设置") });
    auto *host = new QWidget(this);
    auto *stack = new QStackedLayout(host);
    auto *overview = new QLabel(tr("概览：系统处于演示模式"), host);
    overview->setAlignment(Qt::AlignCenter);
    auto *settings = new QLabel(tr("设置：这里可以放参数输入控件"), host);
    settings->setAlignment(Qt::AlignCenter);
    stack->addWidget(overview);
    stack->addWidget(settings);
    layout->addWidget(select);
    layout->addWidget(host, 1);
    connect(
        select, QOverload<int>::of(&QComboBox::currentIndexChanged), stack, &QStackedLayout::setCurrentIndex);
}
```

## QSpacerItem

**是什么**：占位的布局项，用于留白或伸缩。

**用途**：把按钮推向右侧或底部、控制区块间空隙。

**最常用的方式**：QSpacerItem()、addItem()、addStretch()、QSizePolicy::Expanding。下面的实现展示创建控件、配置初始值，再用信号槽处理变化。

**本 demo**：固定宽度占位和水平伸缩占位同时演示。

**操作步骤**：拉宽窗口，观察取消和应用按钮保持在右边。

全部示例在 GUI 线程操作控件；QObject 子对象由父对象释放。未出现显式资源释放代码时，仍应检查模型、场景、布局项和对话框的所有权。

### 头文件：`examples/layouts/spaceritemexample.h`

```cpp
#ifndef SPACERITEMEXAMPLE_H
#define SPACERITEMEXAMPLE_H

#include <QWidget>

/** @brief QSpacerItem 练习页：固定宽度占位和水平伸缩占位同时演示。 */
class SpacerItemExample : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief 初始化QSpacerItem示例及信号槽
     * @param parent 父控件，可为空；页面和子对象遵循 Qt 父子所有权
     * @note 无返回值；在 QApplication 创建后的 GUI 线程调用，不执行硬件操作。
     */
    explicit SpacerItemExample(QWidget *parent = nullptr);
};

#endif
```

### 实现文件：`examples/layouts/spaceritemexample.cpp`

```cpp
#include "spaceritemexample.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QSizePolicy>
#include <QSpacerItem>
#include <QVBoxLayout>

SpacerItemExample::SpacerItemExample(QWidget *parent)
    : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(12, 12, 12, 12);
    layout->setAlignment(Qt::AlignTop);
    auto *description = new QLabel(tr("固定宽度占位和水平伸缩占位同时演示。"), this);
    description->setWordWrap(true);
    layout->addWidget(description);
    // 所有界面操作在 GUI 线程；子控件由 Qt 的父子对象机制自动释放。
    auto *row = new QHBoxLayout;
    row->addWidget(new QLabel(tr("左侧说明"), this));
    // addItem 后由布局拥有占位项，不需要单独 delete。
    row->addItem(new QSpacerItem(24, 0, QSizePolicy::Fixed, QSizePolicy::Minimum));
    row->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));
    row->addWidget(new QPushButton(tr("取消（布局示意）"), this));
    row->addWidget(new QPushButton(tr("应用（布局示意）"), this));
    layout->addLayout(row);
    layout->addStretch(1);
    layout->addWidget(new QLabel(tr("上方还有一个竖向弹簧，这段文字保持在底部。"), this));
}
```
