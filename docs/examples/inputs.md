# 输入控件示例与完整代码

[返回学习路线](README.md)

## QDoubleSpinBox

**是什么**：有上下界、步长和小数位数的浮点输入框。

**用途**：温度、增益、比例等需要精确输入的数值。

**最常用的方式**：setRange()、setDecimals()、setSingleStep()、valueChanged(double)。下面的实现展示创建控件、配置初始值，再用信号槽处理变化。

**本 demo**：输入目标温度，实时显示取到的数值。

**操作步骤**：点击箭头或输入小数，尝试上下限。

**注意事项**：显示为小数不代表十进制运算绝对精确；金额计算要另选数据表示。

全部示例在 GUI 线程操作控件；QObject 子对象由父对象释放。未出现显式资源释放代码时，仍应检查模型、场景、布局项和对话框的所有权。

### 头文件：`examples/inputs/doublespinboxexample.h`

```cpp
#ifndef DOUBLESPINBOXEXAMPLE_H
#define DOUBLESPINBOXEXAMPLE_H

#include <QWidget>

/** @brief QDoubleSpinBox 练习页：输入目标温度，实时显示取到的数值。 */
class DoubleSpinBoxExample : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief 初始化QDoubleSpinBox示例及信号槽
     * @param parent 父控件，可为空；页面和子对象遵循 Qt 父子所有权
     * @note 无返回值；在 QApplication 创建后的 GUI 线程调用，不执行硬件操作。
     */
    explicit DoubleSpinBoxExample(QWidget *parent = nullptr);
};

#endif
```

### 实现文件：`examples/inputs/doublespinboxexample.cpp`

```cpp
#include "doublespinboxexample.h"

#include <QDoubleSpinBox>
#include <QLabel>
#include <QVBoxLayout>
#include <QtGlobal>

DoubleSpinBoxExample::DoubleSpinBoxExample(QWidget *parent)
    : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(12, 12, 12, 12);
    layout->setAlignment(Qt::AlignTop);
    auto *description = new QLabel(tr("输入目标温度，实时显示取到的数值。"), this);
    description->setWordWrap(true);
    layout->addWidget(description);
    // 所有界面操作在 GUI 线程；子控件由 Qt 的父子对象机制自动释放。
    auto *input = new QDoubleSpinBox(this);
    input->setRange(-40.0, 125.0);
    input->setDecimals(1);
    input->setSingleStep(0.5);
    input->setSuffix(tr(" °C"));
    input->setValue(25.0);
    auto *status = new QLabel(tr("目标温度：25.0 °C"), this);
    layout->addWidget(input);
    layout->addWidget(status);
    /** @brief 回显温度；@param value 不含单位后缀的浮点值；无返回值；仅更新 GUI。 */
    connect(input, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this,
        [status](double value) { status->setText(tr("目标温度：%1 °C").arg(value, 0, 'f', 1)); });
}
```

## QPlainTextEdit

**是什么**：面向多行纯文本的编辑器，不承担富文本排版。

**用途**：日志窗口、脚本、配置文本；日志需要限制保留行数。

**最常用的方式**：appendPlainText()、setReadOnly()、setMaximumBlockCount()、toPlainText()。下面的实现展示创建控件、配置初始值，再用信号槽处理变化。

**本 demo**：追加模拟采样日志，可切换只读、清空并限制为 100 段。

**操作步骤**：输入一些文字，再切换只读；反复追加日志并观察尾部。

**注意事项**：这是独立参考页，不改动 demos/inputs/ 中正在编写的同类练习。限制 block 数会禁用撤销/重做，适合滚动日志。

全部示例在 GUI 线程操作控件；QObject 子对象由父对象释放。未出现显式资源释放代码时，仍应检查模型、场景、布局项和对话框的所有权。

### 头文件：`examples/inputs/plaintexteditexample.h`

```cpp
#ifndef PLAINTEXTEDITEXAMPLE_H
#define PLAINTEXTEDITEXAMPLE_H

#include <QWidget>

/** @brief QPlainTextEdit 练习页：追加模拟采样日志，可切换只读、清空并限制为 100 段。 */
class PlainTextEditExample : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief 初始化QPlainTextEdit示例及信号槽
     * @param parent 父控件，可为空；页面和子对象遵循 Qt 父子所有权
     * @note 无返回值；在 QApplication 创建后的 GUI 线程调用，不执行硬件操作。
     */
    explicit PlainTextEditExample(QWidget *parent = nullptr);
};

#endif
```

### 实现文件：`examples/inputs/plaintexteditexample.cpp`

```cpp
#include "plaintexteditexample.h"

#include <QCheckBox>
#include <QDateTime>
#include <QHBoxLayout>
#include <QLabel>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QVBoxLayout>

PlainTextEditExample::PlainTextEditExample(QWidget *parent)
    : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(12, 12, 12, 12);
    layout->setAlignment(Qt::AlignTop);
    auto *description = new QLabel(tr("追加模拟采样日志，可切换只读、清空并限制为 100 段。"), this);
    description->setWordWrap(true);
    layout->addWidget(description);
    // 所有界面操作在 GUI 线程；子控件由 Qt 的父子对象机制自动释放。
    auto *editor = new QPlainTextEdit(this);
    editor->setPlaceholderText(tr("可输入纯文本，或追加模拟日志"));
    editor->setMaximumBlockCount(100);
    auto *readOnly = new QCheckBox(tr("只读模式"), this);
    auto *append = new QPushButton(tr("追加日志"), this);
    auto *clear = new QPushButton(tr("清空"), this);
    auto *row = new QHBoxLayout;
    row->addWidget(readOnly);
    row->addWidget(append);
    row->addWidget(clear);
    layout->addLayout(row);
    layout->addWidget(editor, 1);
    connect(readOnly, &QCheckBox::toggled, editor, &QPlainTextEdit::setReadOnly);
    connect(clear, &QPushButton::clicked, editor, &QPlainTextEdit::clear);
    /** @brief 追加当前时间的模拟日志；无参数、无返回值；不读取硬件或文件。 */
    connect(append, &QPushButton::clicked, this, [editor] {
        editor->appendPlainText(QDateTime::currentDateTime().toString("hh:mm:ss") + tr(" 采样正常"));
    });
}
```

## QSlider

**是什么**：在整数范围内连续拖动选择值。

**用途**：音量、亮度等允许近似选择的参数。

**最常用的方式**：setRange()、setValue()、valueChanged(int)。下面的实现展示创建控件、配置初始值，再用信号槽处理变化。

**本 demo**：滑块与数值框双向同步，显示模拟亮度百分比。

**操作步骤**：拖动滑块，再输入数值，观察另一个控件同步。

全部示例在 GUI 线程操作控件；QObject 子对象由父对象释放。未出现显式资源释放代码时，仍应检查模型、场景、布局项和对话框的所有权。

### 头文件：`examples/inputs/sliderexample.h`

```cpp
#ifndef SLIDEREXAMPLE_H
#define SLIDEREXAMPLE_H

#include <QWidget>

/** @brief QSlider 练习页：滑块与数值框双向同步，显示模拟亮度百分比。 */
class SliderExample : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief 初始化QSlider示例及信号槽
     * @param parent 父控件，可为空；页面和子对象遵循 Qt 父子所有权
     * @note 无返回值；在 QApplication 创建后的 GUI 线程调用，不执行硬件操作。
     */
    explicit SliderExample(QWidget *parent = nullptr);
};

#endif
```

### 实现文件：`examples/inputs/sliderexample.cpp`

```cpp
#include "sliderexample.h"

#include <QLabel>
#include <QSlider>
#include <QSpinBox>
#include <QVBoxLayout>
#include <QtGlobal>

SliderExample::SliderExample(QWidget *parent)
    : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(12, 12, 12, 12);
    layout->setAlignment(Qt::AlignTop);
    auto *description = new QLabel(tr("滑块与数值框双向同步，显示模拟亮度百分比。"), this);
    description->setWordWrap(true);
    layout->addWidget(description);
    // 所有界面操作在 GUI 线程；子控件由 Qt 的父子对象机制自动释放。
    auto *slider = new QSlider(Qt::Horizontal, this);
    auto *spin = new QSpinBox(this);
    slider->setRange(0, 100);
    spin->setRange(0, 100);
    spin->setSuffix(tr(" %"));
    slider->setValue(50);
    spin->setValue(50);
    layout->addWidget(new QLabel(tr("模拟亮度（不会修改设备亮度）"), this));
    layout->addWidget(slider);
    layout->addWidget(spin);
    // 值未变化时 setValue 不会继续发信号，因此这种双向连接不会无限递归。
    connect(slider, &QSlider::valueChanged, spin, &QSpinBox::setValue);
    connect(spin, QOverload<int>::of(&QSpinBox::valueChanged), slider, &QSlider::setValue);
}
```

## QDateEdit

**是什么**：按年、月、日分段编辑日期。

**用途**：预约日期、起止日期、生产日期。

**最常用的方式**：setDate()、setDisplayFormat()、setCalendarPopup()、dateChanged()。下面的实现展示创建控件、配置初始值，再用信号槽处理变化。

**本 demo**：带日历弹窗的日期输入，选择后显示 ISO 日期。

**操作步骤**：点击日期各段或日历按钮，选择不同日期。

全部示例在 GUI 线程操作控件；QObject 子对象由父对象释放。未出现显式资源释放代码时，仍应检查模型、场景、布局项和对话框的所有权。

### 头文件：`examples/inputs/dateeditexample.h`

```cpp
#ifndef DATEEDITEXAMPLE_H
#define DATEEDITEXAMPLE_H

#include <QWidget>

/** @brief QDateEdit 练习页：带日历弹窗的日期输入，选择后显示 ISO 日期。 */
class DateEditExample : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief 初始化QDateEdit示例及信号槽
     * @param parent 父控件，可为空；页面和子对象遵循 Qt 父子所有权
     * @note 无返回值；在 QApplication 创建后的 GUI 线程调用，不执行硬件操作。
     */
    explicit DateEditExample(QWidget *parent = nullptr);
};

#endif
```

### 实现文件：`examples/inputs/dateeditexample.cpp`

```cpp
#include "dateeditexample.h"

#include <QDate>
#include <QDateEdit>
#include <QLabel>
#include <QVBoxLayout>

DateEditExample::DateEditExample(QWidget *parent)
    : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(12, 12, 12, 12);
    layout->setAlignment(Qt::AlignTop);
    auto *description = new QLabel(tr("带日历弹窗的日期输入，选择后显示 ISO 日期。"), this);
    description->setWordWrap(true);
    layout->addWidget(description);
    // 所有界面操作在 GUI 线程；子控件由 Qt 的父子对象机制自动释放。
    auto *input = new QDateEdit(QDate::currentDate(), this);
    input->setDisplayFormat("yyyy-MM-dd");
    input->setDateRange(QDate(2000, 1, 1), QDate(2100, 12, 31));
    input->setCalendarPopup(true);
    auto *status = new QLabel(input->date().toString(Qt::ISODate), this);
    layout->addWidget(input);
    layout->addWidget(status);
    /** @brief 显示选定日期；@param date 有效日期；无返回值；不修改系统时间。 */
    connect(input, &QDateEdit::dateChanged, this,
        [status](const QDate &date) { status->setText(date.toString(Qt::ISODate)); });
}
```

## QTimeEdit

**是什么**：按时、分、秒分段编辑时间。

**用途**：每天定时执行的时间点、时间参数。

**最常用的方式**：setTime()、setDisplayFormat()、timeChanged()。下面的实现展示创建控件、配置初始值，再用信号槽处理变化。

**本 demo**：编辑模拟定时任务的执行时间。

**操作步骤**：选择时、分、秒并用键盘或箭头调整。

**注意事项**：QTime 不包含日期或时区；涉及跨天或时区转换时使用 QDateTime。

全部示例在 GUI 线程操作控件；QObject 子对象由父对象释放。未出现显式资源释放代码时，仍应检查模型、场景、布局项和对话框的所有权。

### 头文件：`examples/inputs/timeeditexample.h`

```cpp
#ifndef TIMEEDITEXAMPLE_H
#define TIMEEDITEXAMPLE_H

#include <QWidget>

/** @brief QTimeEdit 练习页：编辑模拟定时任务的执行时间。 */
class TimeEditExample : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief 初始化QTimeEdit示例及信号槽
     * @param parent 父控件，可为空；页面和子对象遵循 Qt 父子所有权
     * @note 无返回值；在 QApplication 创建后的 GUI 线程调用，不执行硬件操作。
     */
    explicit TimeEditExample(QWidget *parent = nullptr);
};

#endif
```

### 实现文件：`examples/inputs/timeeditexample.cpp`

```cpp
#include "timeeditexample.h"

#include <QLabel>
#include <QTime>
#include <QTimeEdit>
#include <QVBoxLayout>

TimeEditExample::TimeEditExample(QWidget *parent)
    : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(12, 12, 12, 12);
    layout->setAlignment(Qt::AlignTop);
    auto *description = new QLabel(tr("编辑模拟定时任务的执行时间。"), this);
    description->setWordWrap(true);
    layout->addWidget(description);
    // 所有界面操作在 GUI 线程；子控件由 Qt 的父子对象机制自动释放。
    auto *input = new QTimeEdit(QTime(8, 30, 0), this);
    input->setDisplayFormat("HH:mm:ss");
    auto *status = new QLabel(tr("执行时间：08:30:00"), this);
    layout->addWidget(input);
    layout->addWidget(status);
    /** @brief 回显时刻；@param time 一天中的时间；无返回值；不实际创建系统定时任务。 */
    connect(input, &QTimeEdit::timeChanged, this,
        [status](const QTime &time) { status->setText(tr("执行时间：%1").arg(time.toString("HH:mm:ss"))); });
}
```

## QDateTimeEdit

**是什么**：同时编辑日期和时间。

**用途**：预约、查询区间、带日期的定时参数。

**最常用的方式**：setDateTime()、dateTime()、dateTimeChanged()。下面的实现展示创建控件、配置初始值，再用信号槽处理变化。

**本 demo**：设置模拟预约时间，回显本地日期时间。

**操作步骤**：切换日期、时间各段并观察回显。

**注意事项**：实际业务需明确时区及夏令时策略；本例只练习本地时间编辑。

全部示例在 GUI 线程操作控件；QObject 子对象由父对象释放。未出现显式资源释放代码时，仍应检查模型、场景、布局项和对话框的所有权。

### 头文件：`examples/inputs/datetimeeditexample.h`

```cpp
#ifndef DATETIMEEDITEXAMPLE_H
#define DATETIMEEDITEXAMPLE_H

#include <QWidget>

/** @brief QDateTimeEdit 练习页：设置模拟预约时间，回显本地日期时间。 */
class DateTimeEditExample : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief 初始化QDateTimeEdit示例及信号槽
     * @param parent 父控件，可为空；页面和子对象遵循 Qt 父子所有权
     * @note 无返回值；在 QApplication 创建后的 GUI 线程调用，不执行硬件操作。
     */
    explicit DateTimeEditExample(QWidget *parent = nullptr);
};

#endif
```

### 实现文件：`examples/inputs/datetimeeditexample.cpp`

```cpp
#include "datetimeeditexample.h"

#include <QDateTime>
#include <QDateTimeEdit>
#include <QLabel>
#include <QVBoxLayout>

DateTimeEditExample::DateTimeEditExample(QWidget *parent)
    : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(12, 12, 12, 12);
    layout->setAlignment(Qt::AlignTop);
    auto *description = new QLabel(tr("设置模拟预约时间，回显本地日期时间。"), this);
    description->setWordWrap(true);
    layout->addWidget(description);
    // 所有界面操作在 GUI 线程；子控件由 Qt 的父子对象机制自动释放。
    auto *input = new QDateTimeEdit(QDateTime::currentDateTime(), this);
    input->setDisplayFormat("yyyy-MM-dd HH:mm:ss");
    input->setCalendarPopup(true);
    auto *status = new QLabel(input->dateTime().toString(Qt::ISODate), this);
    layout->addWidget(input);
    layout->addWidget(status);
    /** @brief 回显日期时间；@param value 控件当前时间值；无返回值；不修改系统时钟。 */
    connect(input, &QDateTimeEdit::dateTimeChanged, this,
        [status](const QDateTime &value) { status->setText(value.toString(Qt::ISODate)); });
}
```

## QDial

**是什么**：旋钮形的整数输入控件。

**用途**：仪表面板、模拟旋转调参。

**最常用的方式**：setRange()、setNotchesVisible()、valueChanged()。下面的实现展示创建控件、配置初始值，再用信号槽处理变化。

**本 demo**：用旋钮调整模拟输出百分比。

**操作步骤**：拖动旋钮或使用方向键，观察数值变化。

全部示例在 GUI 线程操作控件；QObject 子对象由父对象释放。未出现显式资源释放代码时，仍应检查模型、场景、布局项和对话框的所有权。

### 头文件：`examples/inputs/dialexample.h`

```cpp
#ifndef DIALEXAMPLE_H
#define DIALEXAMPLE_H

#include <QWidget>

/** @brief QDial 练习页：用旋钮调整模拟输出百分比。 */
class DialExample : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief 初始化QDial示例及信号槽
     * @param parent 父控件，可为空；页面和子对象遵循 Qt 父子所有权
     * @note 无返回值；在 QApplication 创建后的 GUI 线程调用，不执行硬件操作。
     */
    explicit DialExample(QWidget *parent = nullptr);
};

#endif
```

### 实现文件：`examples/inputs/dialexample.cpp`

```cpp
#include "dialexample.h"

#include <QDial>
#include <QLabel>
#include <QVBoxLayout>

DialExample::DialExample(QWidget *parent)
    : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(12, 12, 12, 12);
    layout->setAlignment(Qt::AlignTop);
    auto *description = new QLabel(tr("用旋钮调整模拟输出百分比。"), this);
    description->setWordWrap(true);
    layout->addWidget(description);
    // 所有界面操作在 GUI 线程；子控件由 Qt 的父子对象机制自动释放。
    auto *dial = new QDial(this);
    dial->setRange(0, 100);
    dial->setNotchesVisible(true);
    dial->setWrapping(false);
    dial->setValue(30);
    auto *status = new QLabel(tr("模拟输出：30 %"), this);
    layout->addWidget(dial, 1);
    layout->addWidget(status);
    /** @brief 显示旋钮数值；@param value 0～100 的值；无返回值；不控制真实外设。 */
    connect(dial, &QDial::valueChanged, this,
        [status](int value) { status->setText(tr("模拟输出：%1 %").arg(value)); });
}
```

## QScrollBar

**是什么**：通过滑块和步进按钮选择整数位置。

**用途**：自定义浏览位置；普通内容滚动通常交给 QScrollArea。

**最常用的方式**：setRange()、setPageStep()、valueChanged()。下面的实现展示创建控件、配置初始值，再用信号槽处理变化。

**本 demo**：模拟在 0～900 的数据偏移中移动。

**操作步骤**：拖动滚动条，点击两侧箭头或槽道。

全部示例在 GUI 线程操作控件；QObject 子对象由父对象释放。未出现显式资源释放代码时，仍应检查模型、场景、布局项和对话框的所有权。

### 头文件：`examples/inputs/scrollbarexample.h`

```cpp
#ifndef SCROLLBAREXAMPLE_H
#define SCROLLBAREXAMPLE_H

#include <QWidget>

/** @brief QScrollBar 练习页：模拟在 0～900 的数据偏移中移动。 */
class ScrollBarExample : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief 初始化QScrollBar示例及信号槽
     * @param parent 父控件，可为空；页面和子对象遵循 Qt 父子所有权
     * @note 无返回值；在 QApplication 创建后的 GUI 线程调用，不执行硬件操作。
     */
    explicit ScrollBarExample(QWidget *parent = nullptr);
};

#endif
```

### 实现文件：`examples/inputs/scrollbarexample.cpp`

```cpp
#include "scrollbarexample.h"

#include <QLabel>
#include <QScrollBar>
#include <QVBoxLayout>

ScrollBarExample::ScrollBarExample(QWidget *parent)
    : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(12, 12, 12, 12);
    layout->setAlignment(Qt::AlignTop);
    auto *description = new QLabel(tr("模拟在 0～900 的数据偏移中移动。"), this);
    description->setWordWrap(true);
    layout->addWidget(description);
    // 所有界面操作在 GUI 线程；子控件由 Qt 的父子对象机制自动释放。
    auto *bar = new QScrollBar(Qt::Horizontal, this);
    bar->setRange(0, 900);
    bar->setSingleStep(10);
    bar->setPageStep(100);
    auto *status = new QLabel(tr("数据起始偏移：0"), this);
    layout->addWidget(bar);
    layout->addWidget(status);
    /** @brief 显示偏移；@param value 当前起始位置；无返回值；只演示位置选择。 */
    connect(bar, &QScrollBar::valueChanged, this,
        [status](int value) { status->setText(tr("数据起始偏移：%1").arg(value)); });
}
```

## QFontComboBox

**是什么**：列出系统可用字体的下拉框。

**用途**：编辑器字体选择、显示设置。

**最常用的方式**：currentFont()、currentFontChanged()、setFontFilters()。下面的实现展示创建控件、配置初始值，再用信号槽处理变化。

**本 demo**：为预览文字切换字体，保留固定字号。

**操作步骤**：选不同字体，观察中英文预览；可用字体取决于系统安装。

全部示例在 GUI 线程操作控件；QObject 子对象由父对象释放。未出现显式资源释放代码时，仍应检查模型、场景、布局项和对话框的所有权。

### 头文件：`examples/inputs/fontcomboboxexample.h`

```cpp
#ifndef FONTCOMBOBOXEXAMPLE_H
#define FONTCOMBOBOXEXAMPLE_H

#include <QWidget>

/** @brief QFontComboBox 练习页：为预览文字切换字体，保留固定字号。 */
class FontComboBoxExample : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief 初始化QFontComboBox示例及信号槽
     * @param parent 父控件，可为空；页面和子对象遵循 Qt 父子所有权
     * @note 无返回值；在 QApplication 创建后的 GUI 线程调用，不执行硬件操作。
     */
    explicit FontComboBoxExample(QWidget *parent = nullptr);
};

#endif
```

### 实现文件：`examples/inputs/fontcomboboxexample.cpp`

```cpp
#include "fontcomboboxexample.h"

#include <QFont>
#include <QFontComboBox>
#include <QLabel>
#include <QVBoxLayout>

FontComboBoxExample::FontComboBoxExample(QWidget *parent)
    : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(12, 12, 12, 12);
    layout->setAlignment(Qt::AlignTop);
    auto *description = new QLabel(tr("为预览文字切换字体，保留固定字号。"), this);
    description->setWordWrap(true);
    layout->addWidget(description);
    // 所有界面操作在 GUI 线程；子控件由 Qt 的父子对象机制自动释放。
    auto *fonts = new QFontComboBox(this);
    auto *preview = new QLabel(tr("字体预览 Qt Widgets 123 中文"), this);
    preview->setWordWrap(true);
    QFont initial = fonts->currentFont();
    initial.setPointSize(18);
    preview->setFont(initial);
    layout->addWidget(fonts);
    layout->addWidget(preview);
    /** @brief 更新预览字体；@param font 选定字体；无返回值；字体不含汉字时由系统回退。 */
    connect(fonts, &QFontComboBox::currentFontChanged, this, [preview](const QFont &font) {
        QFont displayFont = font;
        displayFont.setPointSize(18);
        preview->setFont(displayFont);
    });
}
```

## QKeySequenceEdit

**是什么**：记录用户按下的快捷键组合。

**用途**：偏好设置中的自定义快捷键。

**最常用的方式**：keySequence()、keySequenceChanged()、QShortcut::setKey()。下面的实现展示创建控件、配置初始值，再用信号槽处理变化。

**本 demo**：录入快捷键，焦点离开录入框后按该快捷键更新计数。

**操作步骤**：在录入框输入组合键，等待录入结束，点击测试区后按组合键。

**注意事项**：快捷键可能与窗口或系统绑定冲突，正式设置界面应检查冲突。

全部示例在 GUI 线程操作控件；QObject 子对象由父对象释放。未出现显式资源释放代码时，仍应检查模型、场景、布局项和对话框的所有权。

### 头文件：`examples/inputs/keysequenceeditexample.h`

```cpp
#ifndef KEYSEQUENCEEDITEXAMPLE_H
#define KEYSEQUENCEEDITEXAMPLE_H

#include <QWidget>

/** @brief QKeySequenceEdit 练习页：录入快捷键，焦点离开录入框后按该快捷键更新计数。 */
class KeySequenceEditExample : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief 初始化QKeySequenceEdit示例及信号槽
     * @param parent 父控件，可为空；页面和子对象遵循 Qt 父子所有权
     * @note 无返回值；在 QApplication 创建后的 GUI 线程调用，不执行硬件操作。
     */
    explicit KeySequenceEditExample(QWidget *parent = nullptr);

private:
    int triggerCount = 0; // 页面内的快捷键触发次数。
};

#endif
```

### 实现文件：`examples/inputs/keysequenceeditexample.cpp`

```cpp
#include "keysequenceeditexample.h"

#include <QKeySequence>
#include <QKeySequenceEdit>
#include <QLabel>
#include <QPushButton>
#include <QShortcut>
#include <QVBoxLayout>

KeySequenceEditExample::KeySequenceEditExample(QWidget *parent)
    : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(12, 12, 12, 12);
    layout->setAlignment(Qt::AlignTop);
    auto *description = new QLabel(tr("录入快捷键，焦点离开录入框后按该快捷键更新计数。"), this);
    description->setWordWrap(true);
    layout->addWidget(description);
    // 所有界面操作在 GUI 线程；子控件由 Qt 的父子对象机制自动释放。
    auto *input = new QKeySequenceEdit(QKeySequence(Qt::CTRL | Qt::Key_J), this);
    auto *test = new QPushButton(tr("点这里，再按快捷键测试"), this);
    auto *status = new QLabel(tr("触发次数：0"), this);
    auto *shortcut = new QShortcut(input->keySequence(), this);
    shortcut->setContext(Qt::WidgetWithChildrenShortcut);
    shortcut->setAutoRepeat(false);
    layout->addWidget(input);
    layout->addWidget(test);
    layout->addWidget(status);
    /** @brief 更新绑定；@param key 用户录入的序列；无返回值；空序列会禁用快捷键。 */
    connect(input, &QKeySequenceEdit::keySequenceChanged, this, [shortcut](const QKeySequence &key) {
        shortcut->setKey(key);
        shortcut->setEnabled(!key.isEmpty());
    });
    /** @brief 累加触发次数；无参数、无返回值；仅在该示例获得焦点时响应。 */
    connect(shortcut, &QShortcut::activated, this,
        [this, status] { status->setText(tr("触发次数：%1").arg(++triggerCount)); });
}
```
