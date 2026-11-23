# 容器示例与完整代码

[返回学习路线](README.md)

## QWidget

**是什么**：最基础的可视容器，也是自定义页面的常用基类。

**用途**：组合标签、输入框和按钮为可复用页面。

**最常用的方式**：setLayout()、setEnabled()、setVisible()。下面的实现展示创建控件、配置初始值，再用信号槽处理变化。

**本 demo**：一个整体启用或禁用的参数区域。

**操作步骤**：取消启用勾选，观察区域中的子控件一起禁用。

**注意事项**：容器负责子对象生命周期；页面类通常继承 QWidget，而不是继承其中的某个输入控件。

全部示例在 GUI 线程操作控件；QObject 子对象由父对象释放。未出现显式资源释放代码时，仍应检查模型、场景、布局项和对话框的所有权。

### 头文件：`examples/containers/widgetexample.h`

```cpp
#ifndef WIDGETEXAMPLE_H
#define WIDGETEXAMPLE_H

#include <QWidget>

/** @brief QWidget 练习页：一个整体启用或禁用的参数区域。 */
class WidgetExample : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief 初始化QWidget示例及信号槽
     * @param parent 父控件，可为空；页面和子对象遵循 Qt 父子所有权
     * @note 无返回值；在 QApplication 创建后的 GUI 线程调用，不执行硬件操作。
     */
    explicit WidgetExample(QWidget *parent = nullptr);
};

#endif
```

### 实现文件：`examples/containers/widgetexample.cpp`

```cpp
#include "widgetexample.h"

#include <QCheckBox>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include <QVBoxLayout>
#include <QWidget>

WidgetExample::WidgetExample(QWidget *parent)
    : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(12, 12, 12, 12);
    layout->setAlignment(Qt::AlignTop);
    auto *description = new QLabel(tr("一个整体启用或禁用的参数区域。"), this);
    description->setWordWrap(true);
    layout->addWidget(description);
    // 所有界面操作在 GUI 线程；子控件由 Qt 的父子对象机制自动释放。
    auto *enabled = new QCheckBox(tr("启用参数区域"), this);
    enabled->setChecked(true);
    auto *panel = new QWidget(this);
    auto *panelLayout = new QFormLayout(panel);
    panelLayout->addRow(tr("名称："), new QLineEdit(panel));
    auto *value = new QSpinBox(panel);
    value->setRange(1, 100);
    panelLayout->addRow(tr("目标值："), value);
    layout->addWidget(enabled);
    layout->addWidget(panel);
    connect(enabled, &QCheckBox::toggled, panel, &QWidget::setEnabled);
}
```

## QGroupBox

**是什么**：带标题、可选勾选开关的分组容器。

**用途**：相关设置分组、隔离多组单选按钮。

**最常用的方式**：setTitle()、setCheckable()、toggled()。下面的实现展示创建控件、配置初始值，再用信号槽处理变化。

**本 demo**：两组独立的单选模式，其中高级配置可以整体关闭。

**操作步骤**：分别选择两组单选项，再关闭高级配置。

**注意事项**：组内单选依靠相同父对象互斥；不同组的父对象不同，因此互不干扰。

全部示例在 GUI 线程操作控件；QObject 子对象由父对象释放。未出现显式资源释放代码时，仍应检查模型、场景、布局项和对话框的所有权。

### 头文件：`examples/containers/groupboxexample.h`

```cpp
#ifndef GROUPBOXEXAMPLE_H
#define GROUPBOXEXAMPLE_H

#include <QWidget>

/** @brief QGroupBox 练习页：两组独立的单选模式，其中高级配置可以整体关闭。 */
class GroupBoxExample : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief 初始化QGroupBox示例及信号槽
     * @param parent 父控件，可为空；页面和子对象遵循 Qt 父子所有权
     * @note 无返回值；在 QApplication 创建后的 GUI 线程调用，不执行硬件操作。
     */
    explicit GroupBoxExample(QWidget *parent = nullptr);
};

#endif
```

### 实现文件：`examples/containers/groupboxexample.cpp`

```cpp
#include "groupboxexample.h"

#include <QGroupBox>
#include <QLabel>
#include <QRadioButton>
#include <QVBoxLayout>

GroupBoxExample::GroupBoxExample(QWidget *parent)
    : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(12, 12, 12, 12);
    layout->setAlignment(Qt::AlignTop);
    auto *description = new QLabel(tr("两组独立的单选模式，其中高级配置可以整体关闭。"), this);
    description->setWordWrap(true);
    layout->addWidget(description);
    // 所有界面操作在 GUI 线程；子控件由 Qt 的父子对象机制自动释放。
    auto *basic = new QGroupBox(tr("采样方式"), this);
    auto *basicLayout = new QVBoxLayout(basic);
    auto *fast = new QRadioButton(tr("快速"), basic);
    auto *accurate = new QRadioButton(tr("精细"), basic);
    fast->setChecked(true);
    basicLayout->addWidget(fast);
    basicLayout->addWidget(accurate);
    auto *advanced = new QGroupBox(tr("高级配置"), this);
    advanced->setCheckable(true);
    advanced->setChecked(true);
    auto *advancedLayout = new QVBoxLayout(advanced);
    auto *autoMode = new QRadioButton(tr("自动"), advanced);
    auto *manual = new QRadioButton(tr("手动"), advanced);
    autoMode->setChecked(true);
    advancedLayout->addWidget(autoMode);
    advancedLayout->addWidget(manual);
    layout->addWidget(basic);
    layout->addWidget(advanced);
}
```

## QTabWidget

**是什么**：自带标签栏的多页面容器。

**用途**：设置窗口、多个独立功能页。

**最常用的方式**：addTab()、currentChanged()、setTabEnabled()。下面的实现展示创建控件、配置初始值，再用信号槽处理变化。

**本 demo**：连接配置与采样配置两个选项卡。

**操作步骤**：切换标签，观察当前索引提示。

全部示例在 GUI 线程操作控件；QObject 子对象由父对象释放。未出现显式资源释放代码时，仍应检查模型、场景、布局项和对话框的所有权。

### 头文件：`examples/containers/tabwidgetexample.h`

```cpp
#ifndef TABWIDGETEXAMPLE_H
#define TABWIDGETEXAMPLE_H

#include <QWidget>

/** @brief QTabWidget 练习页：连接配置与采样配置两个选项卡。 */
class TabWidgetExample : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief 初始化QTabWidget示例及信号槽
     * @param parent 父控件，可为空；页面和子对象遵循 Qt 父子所有权
     * @note 无返回值；在 QApplication 创建后的 GUI 线程调用，不执行硬件操作。
     */
    explicit TabWidgetExample(QWidget *parent = nullptr);
};

#endif
```

### 实现文件：`examples/containers/tabwidgetexample.cpp`

```cpp
#include "tabwidgetexample.h"

#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QWidget>

TabWidgetExample::TabWidgetExample(QWidget *parent)
    : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(12, 12, 12, 12);
    layout->setAlignment(Qt::AlignTop);
    auto *description = new QLabel(tr("连接配置与采样配置两个选项卡。"), this);
    description->setWordWrap(true);
    layout->addWidget(description);
    // 所有界面操作在 GUI 线程；子控件由 Qt 的父子对象机制自动释放。
    auto *tabs = new QTabWidget(this);
    auto *connection = new QWidget(tabs);
    auto *connectionLayout = new QFormLayout(connection);
    connectionLayout->addRow(tr("设备名称："), new QLineEdit(connection));
    auto *sampling = new QWidget(tabs);
    auto *samplingLayout = new QFormLayout(sampling);
    samplingLayout->addRow(tr("采样次数："), new QSpinBox(sampling));
    tabs->addTab(connection, tr("连接"));
    tabs->addTab(sampling, tr("采样"));
    auto *status = new QLabel(tr("当前页：连接"), this);
    layout->addWidget(tabs, 1);
    layout->addWidget(status);
    /** @brief 回显标签页；@param index 当前页序号；无返回值；忽略没有当前页的情况。 */
    connect(tabs, &QTabWidget::currentChanged, this, [tabs, status](int index) {
        if (index >= 0)
            status->setText(tr("当前页：%1").arg(tabs->tabText(index)));
    });
}
```

## QStackedWidget

**是什么**：不自带导航按钮的堆叠页面容器。

**用途**：列表导航、分步页面、同一区域切换视图。

**最常用的方式**：addWidget()、setCurrentIndex()、currentChanged()。下面的实现展示创建控件、配置初始值，再用信号槽处理变化。

**本 demo**：导航列表切换概览与参数页面。

**操作步骤**：点击左侧两项，观察右侧页面。

全部示例在 GUI 线程操作控件；QObject 子对象由父对象释放。未出现显式资源释放代码时，仍应检查模型、场景、布局项和对话框的所有权。

### 头文件：`examples/containers/stackedwidgetexample.h`

```cpp
#ifndef STACKEDWIDGETEXAMPLE_H
#define STACKEDWIDGETEXAMPLE_H

#include <QWidget>

/** @brief QStackedWidget 练习页：导航列表切换概览与参数页面。 */
class StackedWidgetExample : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief 初始化QStackedWidget示例及信号槽
     * @param parent 父控件，可为空；页面和子对象遵循 Qt 父子所有权
     * @note 无返回值；在 QApplication 创建后的 GUI 线程调用，不执行硬件操作。
     */
    explicit StackedWidgetExample(QWidget *parent = nullptr);
};

#endif
```

### 实现文件：`examples/containers/stackedwidgetexample.cpp`

```cpp
#include "stackedwidgetexample.h"

#include <QFormLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QWidget>

StackedWidgetExample::StackedWidgetExample(QWidget *parent)
    : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(12, 12, 12, 12);
    layout->setAlignment(Qt::AlignTop);
    auto *description = new QLabel(tr("导航列表切换概览与参数页面。"), this);
    description->setWordWrap(true);
    layout->addWidget(description);
    // 所有界面操作在 GUI 线程；子控件由 Qt 的父子对象机制自动释放。
    auto *row = new QHBoxLayout;
    auto *navigation = new QListWidget(this);
    navigation->addItems({ tr("概览"), tr("参数") });
    navigation->setMaximumWidth(140);
    auto *stack = new QStackedWidget(this);
    stack->addWidget(new QLabel(tr("概览页面：设备处于演示模式"), stack));
    auto *parameters = new QWidget(stack);
    auto *form = new QFormLayout(parameters);
    form->addRow(tr("名称："), new QLineEdit(parameters));
    stack->addWidget(parameters);
    row->addWidget(navigation);
    row->addWidget(stack, 1);
    layout->addLayout(row, 1);
    connect(navigation, &QListWidget::currentRowChanged, stack, &QStackedWidget::setCurrentIndex);
    navigation->setCurrentRow(0);
}
```

## QScrollArea

**是什么**：为一个内容控件提供滚动条。

**用途**：长设置表单、超出屏幕的参数区。

**最常用的方式**：setWidget()、setWidgetResizable()、ensureWidgetVisible()。下面的实现展示创建控件、配置初始值，再用信号槽处理变化。

**本 demo**：一个包含 30 个参数输入框的长表单。

**操作步骤**：缩小窗口并向下滚动；底部参数仍可访问。

全部示例在 GUI 线程操作控件；QObject 子对象由父对象释放。未出现显式资源释放代码时，仍应检查模型、场景、布局项和对话框的所有权。

### 头文件：`examples/containers/scrollareaexample.h`

```cpp
#ifndef SCROLLAREAEXAMPLE_H
#define SCROLLAREAEXAMPLE_H

#include <QWidget>

/** @brief QScrollArea 练习页：一个包含 30 个参数输入框的长表单。 */
class ScrollAreaExample : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief 初始化QScrollArea示例及信号槽
     * @param parent 父控件，可为空；页面和子对象遵循 Qt 父子所有权
     * @note 无返回值；在 QApplication 创建后的 GUI 线程调用，不执行硬件操作。
     */
    explicit ScrollAreaExample(QWidget *parent = nullptr);
};

#endif
```

### 实现文件：`examples/containers/scrollareaexample.cpp`

```cpp
#include "scrollareaexample.h"

#include <QFormLayout>
#include <QLabel>
#include <QScrollArea>
#include <QSpinBox>
#include <QVBoxLayout>
#include <QWidget>

ScrollAreaExample::ScrollAreaExample(QWidget *parent)
    : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(12, 12, 12, 12);
    layout->setAlignment(Qt::AlignTop);
    auto *description = new QLabel(tr("一个包含 30 个参数输入框的长表单。"), this);
    description->setWordWrap(true);
    layout->addWidget(description);
    // 所有界面操作在 GUI 线程；子控件由 Qt 的父子对象机制自动释放。
    auto *area = new QScrollArea(this);
    area->setWidgetResizable(true);
    auto *content = new QWidget;
    auto *form = new QFormLayout(content);
    for (int index = 1; index <= 30; ++index) {
        auto *input = new QSpinBox(content);
        input->setRange(0, 1000);
        form->addRow(tr("参数 %1：").arg(index), input);
    }
    // content 只能有一个布局；setWidget 后内容控件由滚动区接管。
    area->setWidget(content);
    layout->addWidget(area, 1);
}
```

## QSplitter

**是什么**：可由用户拖动分界线的多区域容器。

**用途**：目录与预览、源码与日志、可调分栏。

**最常用的方式**：addWidget()、setSizes()、setStretchFactor()、saveState()。下面的实现展示创建控件、配置初始值，再用信号槽处理变化。

**本 demo**：左侧目录，右侧说明，分栏可拖动。

**操作步骤**：拖动中间分界线，改变两侧宽度。

全部示例在 GUI 线程操作控件；QObject 子对象由父对象释放。未出现显式资源释放代码时，仍应检查模型、场景、布局项和对话框的所有权。

### 头文件：`examples/containers/splitterexample.h`

```cpp
#ifndef SPLITTEREXAMPLE_H
#define SPLITTEREXAMPLE_H

#include <QWidget>

/** @brief QSplitter 练习页：左侧目录，右侧说明，分栏可拖动。 */
class SplitterExample : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief 初始化QSplitter示例及信号槽
     * @param parent 父控件，可为空；页面和子对象遵循 Qt 父子所有权
     * @note 无返回值；在 QApplication 创建后的 GUI 线程调用，不执行硬件操作。
     */
    explicit SplitterExample(QWidget *parent = nullptr);
};

#endif
```

### 实现文件：`examples/containers/splitterexample.cpp`

```cpp
#include "splitterexample.h"

#include <QLabel>
#include <QListWidget>
#include <QPlainTextEdit>
#include <QSplitter>
#include <QVBoxLayout>

SplitterExample::SplitterExample(QWidget *parent)
    : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(12, 12, 12, 12);
    layout->setAlignment(Qt::AlignTop);
    auto *description = new QLabel(tr("左侧目录，右侧说明，分栏可拖动。"), this);
    description->setWordWrap(true);
    layout->addWidget(description);
    // 所有界面操作在 GUI 线程；子控件由 Qt 的父子对象机制自动释放。
    auto *splitter = new QSplitter(Qt::Horizontal, this);
    auto *list = new QListWidget(splitter);
    list->addItems({ tr("通道一"), tr("通道二"), tr("通道三") });
    auto *details = new QPlainTextEdit(splitter);
    details->setPlainText(tr("拖动中间分割线来调整比例。"));
    splitter->addWidget(list);
    splitter->addWidget(details);
    splitter->setChildrenCollapsible(false);
    splitter->setStretchFactor(1, 1);
    splitter->setSizes({ 140, 360 });
    layout->addWidget(splitter, 1);
}
```

## QToolBox

**是什么**：通过标题栏切换页面的抽屉式容器。

**用途**：按分组收纳工具、分类设置。

**最常用的方式**：addItem()、setCurrentIndex()、currentChanged()。下面的实现展示创建控件、配置初始值，再用信号槽处理变化。

**本 demo**：常规、显示、维护三个工具页。

**操作步骤**：点击不同标题，展开对应内容。

**注意事项**：QToolBox 通常一次显示一个页，不等同于可同时展开多组的树控件。

全部示例在 GUI 线程操作控件；QObject 子对象由父对象释放。未出现显式资源释放代码时，仍应检查模型、场景、布局项和对话框的所有权。

### 头文件：`examples/containers/toolboxexample.h`

```cpp
#ifndef TOOLBOXEXAMPLE_H
#define TOOLBOXEXAMPLE_H

#include <QWidget>

/** @brief QToolBox 练习页：常规、显示、维护三个工具页。 */
class ToolBoxExample : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief 初始化QToolBox示例及信号槽
     * @param parent 父控件，可为空；页面和子对象遵循 Qt 父子所有权
     * @note 无返回值；在 QApplication 创建后的 GUI 线程调用，不执行硬件操作。
     */
    explicit ToolBoxExample(QWidget *parent = nullptr);
};

#endif
```

### 实现文件：`examples/containers/toolboxexample.cpp`

```cpp
#include "toolboxexample.h"

#include <QCheckBox>
#include <QLabel>
#include <QToolBox>
#include <QVBoxLayout>
#include <QWidget>

ToolBoxExample::ToolBoxExample(QWidget *parent)
    : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(12, 12, 12, 12);
    layout->setAlignment(Qt::AlignTop);
    auto *description = new QLabel(tr("常规、显示、维护三个工具页。"), this);
    description->setWordWrap(true);
    layout->addWidget(description);
    // 所有界面操作在 GUI 线程；子控件由 Qt 的父子对象机制自动释放。
    auto *box = new QToolBox(this);
    auto *general = new QWidget(box);
    auto *generalLayout = new QVBoxLayout(general);
    generalLayout->addWidget(new QCheckBox(tr("启用自动采样"), general));
    auto *display = new QWidget(box);
    auto *displayLayout = new QVBoxLayout(display);
    displayLayout->addWidget(new QCheckBox(tr("显示网格"), display));
    auto *maintenance = new QWidget(box);
    auto *maintenanceLayout = new QVBoxLayout(maintenance);
    maintenanceLayout->addWidget(new QLabel(tr("维护说明：本例没有擦除或烧录操作。"), maintenance));
    box->addItem(general, tr("常规"));
    box->addItem(display, tr("显示"));
    box->addItem(maintenance, tr("维护"));
    layout->addWidget(box, 1);
}
```

## QDockWidget

**是什么**：可停靠、浮动及关闭的工具面板。

**用途**：IDE 的目录栏、属性栏、日志面板。

**最常用的方式**：setWidget()、QMainWindow::addDockWidget()、toggleViewAction()。下面的实现展示创建控件、配置初始值，再用信号槽处理变化。

**本 demo**：嵌入一个主窗口，提供可拖动日志面板和恢复显示按钮。

**操作步骤**：拖动面板标题使其浮动或停靠，关闭后用按钮重新显示。

**注意事项**：推荐由 QMainWindow 管理停靠区域；浮动是窗口系统相关行为，目标板需单独确认。

全部示例在 GUI 线程操作控件；QObject 子对象由父对象释放。未出现显式资源释放代码时，仍应检查模型、场景、布局项和对话框的所有权。

### 头文件：`examples/containers/dockwidgetexample.h`

```cpp
#ifndef DOCKWIDGETEXAMPLE_H
#define DOCKWIDGETEXAMPLE_H

#include <QWidget>

/** @brief QDockWidget 练习页：嵌入一个主窗口，提供可拖动日志面板和恢复显示按钮。 */
class DockWidgetExample : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief 初始化QDockWidget示例及信号槽
     * @param parent 父控件，可为空；页面和子对象遵循 Qt 父子所有权
     * @note 无返回值；在 QApplication 创建后的 GUI 线程调用，不执行硬件操作。
     */
    explicit DockWidgetExample(QWidget *parent = nullptr);
};

#endif
```

### 实现文件：`examples/containers/dockwidgetexample.cpp`

```cpp
#include "dockwidgetexample.h"

#include <QDockWidget>
#include <QLabel>
#include <QMainWindow>
#include <QPlainTextEdit>
#include <QToolButton>
#include <QVBoxLayout>

DockWidgetExample::DockWidgetExample(QWidget *parent)
    : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(12, 12, 12, 12);
    layout->setAlignment(Qt::AlignTop);
    auto *description = new QLabel(tr("嵌入一个主窗口，提供可拖动日志面板和恢复显示按钮。"), this);
    description->setWordWrap(true);
    layout->addWidget(description);
    // 所有界面操作在 GUI 线程；子控件由 Qt 的父子对象机制自动释放。
    auto *window = new QMainWindow(this);
    window->setWindowFlags(Qt::Widget);
    window->setCentralWidget(new QLabel(tr("中央编辑区域"), window));
    auto *dock = new QDockWidget(tr("日志面板"), window);
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea | Qt::BottomDockWidgetArea);
    auto *log = new QPlainTextEdit(dock);
    log->setReadOnly(true);
    log->setPlainText(tr("拖动标题栏可改变停靠位置。"));
    dock->setWidget(log);
    window->addDockWidget(Qt::BottomDockWidgetArea, dock);
    auto *show = new QToolButton(this);
    show->setDefaultAction(dock->toggleViewAction());
    layout->addWidget(show);
    layout->addWidget(window, 1);
}
```

## QMdiArea

**是什么**：在一个工作区中管理多个子窗口。

**用途**：多文档编辑、传统桌面工具。

**最常用的方式**：addSubWindow()、tileSubWindows()、cascadeSubWindows()。下面的实现展示创建控件、配置初始值，再用信号槽处理变化。

**本 demo**：新建多个临时文档窗口，提供平铺与层叠。

**操作步骤**：新建几页，分别点击平铺、层叠，也可关闭子窗口。

全部示例在 GUI 线程操作控件；QObject 子对象由父对象释放。未出现显式资源释放代码时，仍应检查模型、场景、布局项和对话框的所有权。

### 头文件：`examples/containers/mdiareaexample.h`

```cpp
#ifndef MDIAREAEXAMPLE_H
#define MDIAREAEXAMPLE_H

#include <QWidget>

/** @brief QMdiArea 练习页：新建多个临时文档窗口，提供平铺与层叠。 */
class MdiAreaExample : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief 初始化QMdiArea示例及信号槽
     * @param parent 父控件，可为空；页面和子对象遵循 Qt 父子所有权
     * @note 无返回值；在 QApplication 创建后的 GUI 线程调用，不执行硬件操作。
     */
    explicit MdiAreaExample(QWidget *parent = nullptr);
};

#endif
```

### 实现文件：`examples/containers/mdiareaexample.cpp`

```cpp
#include "mdiareaexample.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QMdiArea>
#include <QMdiSubWindow>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QVBoxLayout>

MdiAreaExample::MdiAreaExample(QWidget *parent)
    : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(12, 12, 12, 12);
    layout->setAlignment(Qt::AlignTop);
    auto *description = new QLabel(tr("新建多个临时文档窗口，提供平铺与层叠。"), this);
    description->setWordWrap(true);
    layout->addWidget(description);
    // 所有界面操作在 GUI 线程；子控件由 Qt 的父子对象机制自动释放。
    auto *area = new QMdiArea(this);
    auto *row = new QHBoxLayout;
    auto *create = new QPushButton(tr("新建文档"), this);
    auto *tile = new QPushButton(tr("平铺"), this);
    auto *cascade = new QPushButton(tr("层叠"), this);
    row->addWidget(create);
    row->addWidget(tile);
    row->addWidget(cascade);
    layout->addLayout(row);
    layout->addWidget(area, 1);
    /** @brief 创建临时子窗口；无参数、无返回值；关闭时删除窗口和文档，不访问磁盘。 */
    connect(create, &QPushButton::clicked, this, [area] {
        auto *editor = new QPlainTextEdit;
        editor->setPlainText(tr("临时文档，关闭后内容不保留。"));
        auto *subWindow = area->addSubWindow(editor);
        subWindow->setAttribute(Qt::WA_DeleteOnClose);
        subWindow->setWindowTitle(tr("临时文档"));
        subWindow->resize(260, 180);
        subWindow->show();
    });
    connect(tile, &QPushButton::clicked, area, &QMdiArea::tileSubWindows);
    connect(cascade, &QPushButton::clicked, area, &QMdiArea::cascadeSubWindows);
    create->click();
}
```
