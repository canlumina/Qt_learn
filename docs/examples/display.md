# 显示控件示例与完整代码

[返回学习路线](README.md)

## QLabel

**是什么**：显示文字或图片的标签。

**用途**：参数名称、状态提示、图片预览。

**最常用的方式**：setText()、setPixmap()、setWordWrap()、setTextInteractionFlags()。下面的实现展示创建控件、配置初始值，再用信号槽处理变化。

**本 demo**：同时展示可复制文字和程序生成的色块图片。

**操作步骤**：拖选文字并复制，点击按钮切换图片颜色。

全部示例在 GUI 线程操作控件；QObject 子对象由父对象释放。未出现显式资源释放代码时，仍应检查模型、场景、布局项和对话框的所有权。

### 头文件：`examples/display/labelexample.h`

```cpp
#ifndef LABELEXAMPLE_H
#define LABELEXAMPLE_H

#include <QWidget>

/** @brief QLabel 练习页：同时展示可复制文字和程序生成的色块图片。 */
class LabelExample : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief 初始化QLabel示例及信号槽
     * @param parent 父控件，可为空；页面和子对象遵循 Qt 父子所有权
     * @note 无返回值；在 QApplication 创建后的 GUI 线程调用，不执行硬件操作。
     */
    explicit LabelExample(QWidget *parent = nullptr);
};

#endif
```

### 实现文件：`examples/display/labelexample.cpp`

```cpp
#include "labelexample.h"

#include <QColor>
#include <QLabel>
#include <QPixmap>
#include <QPushButton>
#include <QVBoxLayout>

LabelExample::LabelExample(QWidget *parent)
    : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(12, 12, 12, 12);
    layout->setAlignment(Qt::AlignTop);
    auto *description = new QLabel(tr("同时展示可复制文字和程序生成的色块图片。"), this);
    description->setWordWrap(true);
    layout->addWidget(description);
    // 所有界面操作在 GUI 线程；子控件由 Qt 的父子对象机制自动释放。
    auto *text = new QLabel(tr("状态：设备空闲\n这段文字可以选择并复制。"), this);
    text->setTextFormat(Qt::PlainText);
    text->setWordWrap(true);
    text->setTextInteractionFlags(Qt::TextSelectableByMouse);
    auto *image = new QLabel(this);
    QPixmap pixmap(160, 80);
    pixmap.fill(QColor("#377bb5"));
    image->setPixmap(pixmap);
    image->setAlignment(Qt::AlignCenter);
    auto *change = new QPushButton(tr("切换色块"), this);
    change->setCheckable(true);
    layout->addWidget(text);
    layout->addWidget(image);
    layout->addWidget(change);
    /** @brief 更换图片；@param checked 是否选择第二种颜色；无返回值；图片按值由 Qt 管理。 */
    connect(change, &QPushButton::toggled, this, [image](bool checked) {
        QPixmap next(160, 80);
        next.fill(checked ? QColor("#c77a35") : QColor("#377bb5"));
        image->setPixmap(next);
    });
}
```

## QProgressBar

**是什么**：显示已完成的比例或不确定耗时任务的忙碌状态。

**用途**：升级、拷贝、加载、后台任务进度。

**最常用的方式**：setRange()、setValue()、setFormat()。下面的实现展示创建控件、配置初始值，再用信号槽处理变化。

**本 demo**：定时器模拟进度，可切换确定进度和忙碌模式，支持重新开始。

**操作步骤**：点击开始，切换忙碌模式，再切回百分比。

**注意事项**：真实工作放入工作线程，再通过信号把进度传回 GUI；本例没有 sleep 或真实任务。

全部示例在 GUI 线程操作控件；QObject 子对象由父对象释放。未出现显式资源释放代码时，仍应检查模型、场景、布局项和对话框的所有权。

### 头文件：`examples/display/progressbarexample.h`

```cpp
#ifndef PROGRESSBAREXAMPLE_H
#define PROGRESSBAREXAMPLE_H

#include <QWidget>

/** @brief QProgressBar 练习页：定时器模拟进度，可切换确定进度和忙碌模式，支持重新开始。 */
class ProgressBarExample : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief 初始化QProgressBar示例及信号槽
     * @param parent 父控件，可为空；页面和子对象遵循 Qt 父子所有权
     * @note 无返回值；在 QApplication 创建后的 GUI 线程调用，不执行硬件操作。
     */
    explicit ProgressBarExample(QWidget *parent = nullptr);

private:
    int completed = 0; // 已完成百分比，与忙碌模式的显示范围分开保存。
};

#endif
```

### 实现文件：`examples/display/progressbarexample.cpp`

```cpp
#include "progressbarexample.h"

#include <QCheckBox>
#include <QLabel>
#include <QProgressBar>
#include <QPushButton>
#include <QTimer>
#include <QVBoxLayout>

ProgressBarExample::ProgressBarExample(QWidget *parent)
    : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(12, 12, 12, 12);
    layout->setAlignment(Qt::AlignTop);
    auto *description = new QLabel(tr("定时器模拟进度，可切换确定进度和忙碌模式，支持重新开始。"), this);
    description->setWordWrap(true);
    layout->addWidget(description);
    // 所有界面操作在 GUI 线程；子控件由 Qt 的父子对象机制自动释放。
    auto *progress = new QProgressBar(this);
    progress->setRange(0, 100);
    progress->setValue(0);
    auto *busy = new QCheckBox(tr("忙碌模式（不显示百分比）"), this);
    auto *start = new QPushButton(tr("开始 / 重新开始"), this);
    auto *timer = new QTimer(this);
    timer->setInterval(80);
    layout->addWidget(progress);
    layout->addWidget(busy);
    layout->addWidget(start);
    /** @brief 模拟一小步进度；无参数、无返回值；不阻塞 GUI，计数达到上限停止。 */
    connect(timer, &QTimer::timeout, this, [this, progress, busy, timer] {
        completed += 2;
        if (!busy->isChecked())
            progress->setValue(completed);
        if (completed >= 100) {
            timer->stop();
            busy->setChecked(false);
            progress->setValue(100);
        }
    });
    /** @brief 重新开始；无参数、无返回值；定时器由页面管理，销毁页面自动停止。 */
    connect(start, &QPushButton::clicked, this, [this, progress, busy, timer] {
        completed = 0;
        if (!busy->isChecked())
            progress->setValue(0);
        timer->start();
    });
    /** @brief 切换进度范围；@param enabled true 表示忙碌模式；无返回值；恢复时回显实际计数。 */
    connect(busy, &QCheckBox::toggled, this, [this, progress](bool enabled) {
        progress->setRange(0, enabled ? 0 : 100);
        if (!enabled)
            progress->setValue(completed);
    });
}
```

## QTextBrowser

**是什么**：用于只读富文本浏览，支持链接和历史导航。

**用途**：帮助页、使用说明、更新记录。

**最常用的方式**：setHtml()、setSource()、anchorClicked()、setOpenExternalLinks()。下面的实现展示创建控件、配置初始值，再用信号槽处理变化。

**本 demo**：内置帮助内容与锚点导航，不启动外部浏览器。

**操作步骤**：点击“跳到注意事项”，观察页面内跳转和链接提示。

**注意事项**：复杂网页需要 Qt WebEngine 等其他模块；本例仅依赖 Widgets。

全部示例在 GUI 线程操作控件；QObject 子对象由父对象释放。未出现显式资源释放代码时，仍应检查模型、场景、布局项和对话框的所有权。

### 头文件：`examples/display/textbrowserexample.h`

```cpp
#ifndef TEXTBROWSEREXAMPLE_H
#define TEXTBROWSEREXAMPLE_H

#include <QWidget>

/** @brief QTextBrowser 练习页：内置帮助内容与锚点导航，不启动外部浏览器。 */
class TextBrowserExample : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief 初始化QTextBrowser示例及信号槽
     * @param parent 父控件，可为空；页面和子对象遵循 Qt 父子所有权
     * @note 无返回值；在 QApplication 创建后的 GUI 线程调用，不执行硬件操作。
     */
    explicit TextBrowserExample(QWidget *parent = nullptr);
};

#endif
```

### 实现文件：`examples/display/textbrowserexample.cpp`

```cpp
#include "textbrowserexample.h"

#include <QLabel>
#include <QTextBrowser>
#include <QUrl>
#include <QVBoxLayout>

TextBrowserExample::TextBrowserExample(QWidget *parent)
    : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(12, 12, 12, 12);
    layout->setAlignment(Qt::AlignTop);
    auto *description = new QLabel(tr("内置帮助内容与锚点导航，不启动外部浏览器。"), this);
    description->setWordWrap(true);
    layout->addWidget(description);
    // 所有界面操作在 GUI 线程；子控件由 Qt 的父子对象机制自动释放。
    auto *browser = new QTextBrowser(this);
    auto *status = new QLabel(tr("尚未点击链接"), this);
    status->setTextFormat(Qt::PlainText);
    browser->setOpenExternalLinks(false);
    browser->setOpenLinks(false);
    browser->setHtml(tr("<h2>帮助页</h2><p><a href='#notes'>跳到注意事项</a></p>"
                        "<p>QTextBrowser 用于只读文档，不是完整网页浏览器。</p>"
                        "<p>这里可以显示标题、列表和文本链接。</p>"
                        "<h3 id='notes'>注意事项</h3><p>只处理本页锚点，不访问网络。</p>"));
    layout->addWidget(browser, 1);
    layout->addWidget(status);
    /** @brief 处理本页锚点；@param url 用户点击的链接；无返回值；其他协议不执行。 */
    connect(browser, &QTextBrowser::anchorClicked, this, [browser, status](const QUrl &url) {
        status->setText(tr("点击链接：%1").arg(url.toString()));
        if (url.scheme().isEmpty() && url.path().isEmpty())
            browser->scrollToAnchor(url.fragment());
    });
}
```

## QLCDNumber

**是什么**：模拟液晶数字显示的只读控件。

**用途**：计数器、仪表读数、数字时钟。

**最常用的方式**：display()、setDigitCount()、setSegmentStyle()。下面的实现展示创建控件、配置初始值，再用信号槽处理变化。

**本 demo**：数值框调整模拟电压，LCD 回显带一位小数的读数。

**操作步骤**：调整输入值，观察数码管显示。

全部示例在 GUI 线程操作控件；QObject 子对象由父对象释放。未出现显式资源释放代码时，仍应检查模型、场景、布局项和对话框的所有权。

### 头文件：`examples/display/lcdnumberexample.h`

```cpp
#ifndef LCDNUMBEREXAMPLE_H
#define LCDNUMBEREXAMPLE_H

#include <QWidget>

/** @brief QLCDNumber 练习页：数值框调整模拟电压，LCD 回显带一位小数的读数。 */
class LCDNumberExample : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief 初始化QLCDNumber示例及信号槽
     * @param parent 父控件，可为空；页面和子对象遵循 Qt 父子所有权
     * @note 无返回值；在 QApplication 创建后的 GUI 线程调用，不执行硬件操作。
     */
    explicit LCDNumberExample(QWidget *parent = nullptr);
};

#endif
```

### 实现文件：`examples/display/lcdnumberexample.cpp`

```cpp
#include "lcdnumberexample.h"

#include <QDoubleSpinBox>
#include <QLCDNumber>
#include <QLabel>
#include <QString>
#include <QVBoxLayout>
#include <QtGlobal>

LCDNumberExample::LCDNumberExample(QWidget *parent)
    : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(12, 12, 12, 12);
    layout->setAlignment(Qt::AlignTop);
    auto *description = new QLabel(tr("数值框调整模拟电压，LCD 回显带一位小数的读数。"), this);
    description->setWordWrap(true);
    layout->addWidget(description);
    // 所有界面操作在 GUI 线程；子控件由 Qt 的父子对象机制自动释放。
    auto *lcd = new QLCDNumber(6, this);
    lcd->setSegmentStyle(QLCDNumber::Flat);
    auto *value = new QDoubleSpinBox(this);
    value->setRange(0.0, 99.9);
    value->setDecimals(1);
    value->setSuffix(tr(" V"));
    value->setValue(12.0);
    lcd->display(QString::number(value->value(), 'f', 1));
    layout->addWidget(lcd);
    layout->addWidget(value);
    /** @brief 回显电压；@param voltage 当前模拟读数；无返回值；显示长度由 digitCount 限定。 */
    connect(value, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this,
        [lcd](double voltage) { lcd->display(QString::number(voltage, 'f', 1)); });
}
```

## QCalendarWidget

**是什么**：可直接浏览和选择日期的月历。

**用途**：日程、日期选择、预约界面。

**最常用的方式**：selectedDate()、selectionChanged()、setDateTextFormat()。下面的实现展示创建控件、配置初始值，再用信号槽处理变化。

**本 demo**：日历选择与日期回显，同时突出标记今天。

**操作步骤**：点击日期、切换月份，观察标签。

全部示例在 GUI 线程操作控件；QObject 子对象由父对象释放。未出现显式资源释放代码时，仍应检查模型、场景、布局项和对话框的所有权。

### 头文件：`examples/display/calendarwidgetexample.h`

```cpp
#ifndef CALENDARWIDGETEXAMPLE_H
#define CALENDARWIDGETEXAMPLE_H

#include <QWidget>

/** @brief QCalendarWidget 练习页：日历选择与日期回显，同时突出标记今天。 */
class CalendarWidgetExample : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief 初始化QCalendarWidget示例及信号槽
     * @param parent 父控件，可为空；页面和子对象遵循 Qt 父子所有权
     * @note 无返回值；在 QApplication 创建后的 GUI 线程调用，不执行硬件操作。
     */
    explicit CalendarWidgetExample(QWidget *parent = nullptr);
};

#endif
```

### 实现文件：`examples/display/calendarwidgetexample.cpp`

```cpp
#include "calendarwidgetexample.h"

#include <QCalendarWidget>
#include <QColor>
#include <QDate>
#include <QFont>
#include <QLabel>
#include <QTextCharFormat>
#include <QVBoxLayout>

CalendarWidgetExample::CalendarWidgetExample(QWidget *parent)
    : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(12, 12, 12, 12);
    layout->setAlignment(Qt::AlignTop);
    auto *description = new QLabel(tr("日历选择与日期回显，同时突出标记今天。"), this);
    description->setWordWrap(true);
    layout->addWidget(description);
    // 所有界面操作在 GUI 线程；子控件由 Qt 的父子对象机制自动释放。
    auto *calendar = new QCalendarWidget(this);
    calendar->setGridVisible(true);
    QTextCharFormat todayFormat;
    todayFormat.setForeground(QColor("#b54832"));
    todayFormat.setFontWeight(QFont::Bold);
    calendar->setDateTextFormat(QDate::currentDate(), todayFormat);
    auto *status = new QLabel(calendar->selectedDate().toString(Qt::ISODate), this);
    layout->addWidget(calendar, 1);
    layout->addWidget(status);
    /** @brief 回显选择；无参数、无返回值；通过 selectedDate 获取当前日期。 */
    connect(calendar, &QCalendarWidget::selectionChanged, this,
        [calendar, status] { status->setText(calendar->selectedDate().toString(Qt::ISODate)); });
}
```

## QGraphicsView

**是什么**：显示 QGraphicsScene 的图形视图，支持缩放、选择和拖动。

**用途**：流程图、图元编辑、可缩放画布。

**最常用的方式**：setScene()、scale()、fitInView()、QGraphicsItem::setFlags()。下面的实现展示创建控件、配置初始值，再用信号槽处理变化。

**本 demo**：可拖动的矩形与椭圆，提供放大、缩小和复位。

**操作步骤**：拖动图形；点击放大缩小，按复位还原缩放。

**注意事项**：视图不会拥有外部传入的 scene，因此给 scene 设置页面父对象；scene 负责销毁图元。

全部示例在 GUI 线程操作控件；QObject 子对象由父对象释放。未出现显式资源释放代码时，仍应检查模型、场景、布局项和对话框的所有权。

### 头文件：`examples/display/graphicsviewexample.h`

```cpp
#ifndef GRAPHICSVIEWEXAMPLE_H
#define GRAPHICSVIEWEXAMPLE_H

#include <QWidget>

/** @brief QGraphicsView 练习页：可拖动的矩形与椭圆，提供放大、缩小和复位。 */
class GraphicsViewExample : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief 初始化QGraphicsView示例及信号槽
     * @param parent 父控件，可为空；页面和子对象遵循 Qt 父子所有权
     * @note 无返回值；在 QApplication 创建后的 GUI 线程调用，不执行硬件操作。
     */
    explicit GraphicsViewExample(QWidget *parent = nullptr);
};

#endif
```

### 实现文件：`examples/display/graphicsviewexample.cpp`

```cpp
#include "graphicsviewexample.h"

#include <QBrush>
#include <QColor>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QHBoxLayout>
#include <QLabel>
#include <QPainter>
#include <QPen>
#include <QPushButton>
#include <QVBoxLayout>

GraphicsViewExample::GraphicsViewExample(QWidget *parent)
    : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(12, 12, 12, 12);
    layout->setAlignment(Qt::AlignTop);
    auto *description = new QLabel(tr("可拖动的矩形与椭圆，提供放大、缩小和复位。"), this);
    description->setWordWrap(true);
    layout->addWidget(description);
    // 所有界面操作在 GUI 线程；子控件由 Qt 的父子对象机制自动释放。
    auto *scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, 420, 240);
    auto *rectangle = scene->addRect(30, 40, 120, 70, QPen(Qt::darkBlue), QBrush(QColor("#8dbce0")));
    auto *ellipse = scene->addEllipse(220, 90, 100, 80, QPen(Qt::darkGreen), QBrush(QColor("#9fd4a8")));
    rectangle->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
    ellipse->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
    auto *view = new QGraphicsView(scene, this);
    view->setRenderHint(QPainter::Antialiasing);
    auto *zoomIn = new QPushButton(tr("放大"), this);
    auto *zoomOut = new QPushButton(tr("缩小"), this);
    auto *reset = new QPushButton(tr("复位缩放"), this);
    auto *buttons = new QHBoxLayout;
    buttons->addWidget(zoomIn);
    buttons->addWidget(zoomOut);
    buttons->addWidget(reset);
    layout->addLayout(buttons);
    layout->addWidget(view, 1);
    /** @brief 有界放大画布；无参数、无返回值；限制缩放倍数，避免无限放大。 */
    connect(zoomIn, &QPushButton::clicked, this, [view] {
        if (view->transform().m11() < 4.0)
            view->scale(1.2, 1.2);
    });
    /** @brief 有界缩小画布；无参数、无返回值；保留最低可见比例。 */
    connect(zoomOut, &QPushButton::clicked, this, [view] {
        if (view->transform().m11() > 0.3)
            view->scale(1.0 / 1.2, 1.0 / 1.2);
    });
    connect(reset, &QPushButton::clicked, view, &QGraphicsView::resetTransform);
}
```

## QFrame

**是什么**：提供边框或水平、垂直分隔线的基础容器。

**用途**：区域边框、设置项分隔、视觉分组。

**最常用的方式**：setFrameShape()、setFrameShadow()、setLineWidth()。下面的实现展示创建控件、配置初始值，再用信号槽处理变化。

**本 demo**：上方带边框的说明区域，下方使用水平分隔线。

**操作步骤**：观察边框和分隔线；缩放窗口检查分隔线自动延伸。

**注意事项**：速查表里的 Line 与容器 QFrame 是同一个类，本页同时覆盖两种用法。

全部示例在 GUI 线程操作控件；QObject 子对象由父对象释放。未出现显式资源释放代码时，仍应检查模型、场景、布局项和对话框的所有权。

### 头文件：`examples/display/frameexample.h`

```cpp
#ifndef FRAMEEXAMPLE_H
#define FRAMEEXAMPLE_H

#include <QWidget>

/** @brief QFrame 练习页：上方带边框的说明区域，下方使用水平分隔线。 */
class FrameExample : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief 初始化QFrame示例及信号槽
     * @param parent 父控件，可为空；页面和子对象遵循 Qt 父子所有权
     * @note 无返回值；在 QApplication 创建后的 GUI 线程调用，不执行硬件操作。
     */
    explicit FrameExample(QWidget *parent = nullptr);
};

#endif
```

### 实现文件：`examples/display/frameexample.cpp`

```cpp
#include "frameexample.h"

#include <QFrame>
#include <QLabel>
#include <QVBoxLayout>

FrameExample::FrameExample(QWidget *parent)
    : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(12, 12, 12, 12);
    layout->setAlignment(Qt::AlignTop);
    auto *description = new QLabel(tr("上方带边框的说明区域，下方使用水平分隔线。"), this);
    description->setWordWrap(true);
    layout->addWidget(description);
    // 所有界面操作在 GUI 线程；子控件由 Qt 的父子对象机制自动释放。
    auto *panel = new QFrame(this);
    panel->setFrameShape(QFrame::StyledPanel);
    panel->setFrameShadow(QFrame::Sunken);
    auto *panelLayout = new QVBoxLayout(panel);
    panelLayout->addWidget(new QLabel(tr("这是带边框的内容容器"), panel));
    auto *line = new QFrame(this);
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);
    layout->addWidget(panel);
    layout->addWidget(line);
    layout->addWidget(new QLabel(tr("这是分隔线下方的说明"), this));
}
```
