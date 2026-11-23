# 主窗口示例与完整代码

[返回学习路线](README.md)

## QMainWindow

**是什么**：提供中央区、菜单栏、工具栏、停靠区和状态栏的窗口框架。

**用途**：功能完整的桌面或嵌入式主界面。

**最常用的方式**：setCentralWidget()、menuBar()、addToolBar()、statusBar()。下面的实现展示创建控件、配置初始值，再用信号槽处理变化。

**本 demo**：嵌入一个具备菜单、工具栏和状态栏的小主窗口。

**操作步骤**：从菜单或工具栏触发同一个刷新动作。

**注意事项**：QMainWindow 有专用布局，不要直接 setLayout；业务布局应设置在 centralWidget 上。

全部示例在 GUI 线程操作控件；QObject 子对象由父对象释放。未出现显式资源释放代码时，仍应检查模型、场景、布局项和对话框的所有权。

### 头文件：`examples/windows/mainwindowexample.h`

```cpp
#ifndef MAINWINDOWEXAMPLE_H
#define MAINWINDOWEXAMPLE_H

#include <QWidget>

/** @brief QMainWindow 练习页：嵌入一个具备菜单、工具栏和状态栏的小主窗口。 */
class MainWindowExample : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief 初始化QMainWindow示例及信号槽
     * @param parent 父控件，可为空；页面和子对象遵循 Qt 父子所有权
     * @note 无返回值；在 QApplication 创建后的 GUI 线程调用，不执行硬件操作。
     */
    explicit MainWindowExample(QWidget *parent = nullptr);
};

#endif
```

### 实现文件：`examples/windows/mainwindowexample.cpp`

```cpp
#include "mainwindowexample.h"

#include <QAction>
#include <QLabel>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>
#include <QStyle>
#include <QTime>
#include <QToolBar>
#include <QVBoxLayout>

MainWindowExample::MainWindowExample(QWidget *parent)
    : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(12, 12, 12, 12);
    layout->setAlignment(Qt::AlignTop);
    auto *description = new QLabel(tr("嵌入一个具备菜单、工具栏和状态栏的小主窗口。"), this);
    description->setWordWrap(true);
    layout->addWidget(description);
    // 所有界面操作在 GUI 线程；子控件由 Qt 的父子对象机制自动释放。
    auto *window = new QMainWindow(this);
    window->setWindowFlags(Qt::Widget);
    auto *central = new QLabel(tr("这是主窗口的中央区域"), window);
    central->setAlignment(Qt::AlignCenter);
    window->setCentralWidget(central);
    auto *menu = window->menuBar()->addMenu(tr("操作"));
    window->menuBar()->setNativeMenuBar(false);
    auto *refresh = new QAction(style()->standardIcon(QStyle::SP_BrowserReload), tr("刷新"), window);
    menu->addAction(refresh);
    window->addToolBar(tr("常用"))->addAction(refresh);
    window->statusBar()->showMessage(tr("就绪"));
    layout->addWidget(window, 1);
    /** @brief 更新中央内容和状态；无参数、无返回值；仅操作本例内嵌窗口。 */
    connect(refresh, &QAction::triggered, this, [window, central] {
        central->setText(tr("刷新于 %1").arg(QTime::currentTime().toString("HH:mm:ss")));
        window->statusBar()->showMessage(tr("刷新完成"), 2000);
    });
}
```

## QMenuBar

**是什么**：展示菜单分类的菜单栏。

**用途**：把多个功能按文件、编辑、帮助等分组。

**最常用的方式**：addMenu()、QMenu::addAction()、QAction::triggered()。下面的实现展示创建控件、配置初始值，再用信号槽处理变化。

**本 demo**：操作和帮助两个菜单，触发后回显。

**操作步骤**：打开两个菜单并选择动作。

全部示例在 GUI 线程操作控件；QObject 子对象由父对象释放。未出现显式资源释放代码时，仍应检查模型、场景、布局项和对话框的所有权。

### 头文件：`examples/windows/menubarexample.h`

```cpp
#ifndef MENUBAREXAMPLE_H
#define MENUBAREXAMPLE_H

#include <QWidget>

/** @brief QMenuBar 练习页：操作和帮助两个菜单，触发后回显。 */
class MenuBarExample : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief 初始化QMenuBar示例及信号槽
     * @param parent 父控件，可为空；页面和子对象遵循 Qt 父子所有权
     * @note 无返回值；在 QApplication 创建后的 GUI 线程调用，不执行硬件操作。
     */
    explicit MenuBarExample(QWidget *parent = nullptr);
};

#endif
```

### 实现文件：`examples/windows/menubarexample.cpp`

```cpp
#include "menubarexample.h"

#include <QAction>
#include <QLabel>
#include <QMenuBar>
#include <QVBoxLayout>

MenuBarExample::MenuBarExample(QWidget *parent)
    : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(12, 12, 12, 12);
    layout->setAlignment(Qt::AlignTop);
    auto *description = new QLabel(tr("操作和帮助两个菜单，触发后回显。"), this);
    description->setWordWrap(true);
    layout->addWidget(description);
    // 所有界面操作在 GUI 线程；子控件由 Qt 的父子对象机制自动释放。
    auto *bar = new QMenuBar(this);
    bar->setNativeMenuBar(false);
    auto *operation = bar->addMenu(tr("操作"));
    auto *reset = operation->addAction(tr("重置演示状态"));
    auto *help = bar->addMenu(tr("帮助"));
    auto *about = help->addAction(tr("关于本页"));
    auto *status = new QLabel(tr("菜单动作将显示在这里"), this);
    layout->setMenuBar(bar);
    layout->addWidget(status);
    /** @brief 演示操作菜单；无参数、无返回值；不修改工程设置。 */
    connect(reset, &QAction::triggered, this, [status] { status->setText(tr("演示状态已重置")); });
    /** @brief 演示帮助菜单；无参数、无返回值；只显示说明。 */
    connect(
        about, &QAction::triggered, this, [status] { status->setText(tr("QMenuBar 用于组织菜单分类。")); });
}
```

## QMenu

**是什么**：弹出操作列表，支持子菜单、勾选和分隔线。

**用途**：右键菜单、按钮下拉菜单、主菜单中的子菜单。

**最常用的方式**：addAction()、addMenu()、popup()、setContextMenuPolicy()。下面的实现展示创建控件、配置初始值，再用信号槽处理变化。

**本 demo**：文本区右键菜单，包含全选、清空和换行开关。

**操作步骤**：在文本区右键或点击“显示菜单”，切换换行或执行全选。

全部示例在 GUI 线程操作控件；QObject 子对象由父对象释放。未出现显式资源释放代码时，仍应检查模型、场景、布局项和对话框的所有权。

### 头文件：`examples/windows/menuexample.h`

```cpp
#ifndef MENUEXAMPLE_H
#define MENUEXAMPLE_H

#include <QWidget>

/** @brief QMenu 练习页：文本区右键菜单，包含全选、清空和换行开关。 */
class MenuExample : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief 初始化QMenu示例及信号槽
     * @param parent 父控件，可为空；页面和子对象遵循 Qt 父子所有权
     * @note 无返回值；在 QApplication 创建后的 GUI 线程调用，不执行硬件操作。
     */
    explicit MenuExample(QWidget *parent = nullptr);
};

#endif
```

### 实现文件：`examples/windows/menuexample.cpp`

```cpp
#include "menuexample.h"

#include <QAction>
#include <QLabel>
#include <QMenu>
#include <QPlainTextEdit>
#include <QPoint>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

MenuExample::MenuExample(QWidget *parent)
    : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(12, 12, 12, 12);
    layout->setAlignment(Qt::AlignTop);
    auto *description = new QLabel(tr("文本区右键菜单，包含全选、清空和换行开关。"), this);
    description->setWordWrap(true);
    layout->addWidget(description);
    // 所有界面操作在 GUI 线程；子控件由 Qt 的父子对象机制自动释放。
    auto *editor = new QPlainTextEdit(this);
    editor->setPlainText(tr("这是右键菜单示例。输入一行长文本以观察换行开关。"));
    auto *menu = new QMenu(editor);
    auto *select = menu->addAction(tr("全选"));
    auto *clear = menu->addAction(tr("清空临时文本"));
    menu->addSeparator();
    auto *wrap = menu->addAction(tr("自动换行"));
    wrap->setCheckable(true);
    wrap->setChecked(true);
    auto *show = new QPushButton(tr("显示菜单"), this);
    editor->setContextMenuPolicy(Qt::CustomContextMenu);
    layout->addWidget(show);
    layout->addWidget(editor, 1);
    connect(select, &QAction::triggered, editor, &QPlainTextEdit::selectAll);
    connect(clear, &QAction::triggered, editor, &QPlainTextEdit::clear);
    /** @brief 显示右键菜单；@param position 视口局部坐标；无返回值；popup 非阻塞。 */
    connect(editor, &QWidget::customContextMenuRequested, this,
        [editor, menu](const QPoint &position) { menu->popup(editor->viewport()->mapToGlobal(position)); });
    /** @brief 提供触屏可用的菜单入口；无参数、无返回值；位置从按钮映射到全局。 */
    connect(show, &QPushButton::clicked, this,
        [show, menu] { menu->popup(show->mapToGlobal(QPoint(0, show->height()))); });
    /** @brief 设置换行模式；@param enabled 是否自动换行；无返回值；不修改文本。 */
    connect(wrap, &QAction::toggled, this, [editor](bool enabled) {
        editor->setLineWrapMode(enabled ? QPlainTextEdit::WidgetWidth : QPlainTextEdit::NoWrap);
    });
}
```

## QAction

**是什么**：可复用的界面命令，集中管理启用、勾选及触发逻辑。

**用途**：让菜单、工具栏和快捷键共享同一功能。

**最常用的方式**：setCheckable()、setEnabled()、triggered()、toggled()。下面的实现展示创建控件、配置初始值，再用信号槽处理变化。

**本 demo**：一个“显示网格”动作同时放进工具栏和菜单，状态自动同步。

**操作步骤**：从任一入口切换网格，观察另一入口的勾选状态。

**注意事项**：动作不等同于按钮；把动作添加到菜单和工具栏不会复制动作本身。

全部示例在 GUI 线程操作控件；QObject 子对象由父对象释放。未出现显式资源释放代码时，仍应检查模型、场景、布局项和对话框的所有权。

### 头文件：`examples/windows/actionexample.h`

```cpp
#ifndef ACTIONEXAMPLE_H
#define ACTIONEXAMPLE_H

#include <QWidget>

/** @brief QAction 练习页：一个“显示网格”动作同时放进工具栏和菜单，状态自动同步。 */
class ActionExample : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief 初始化QAction示例及信号槽
     * @param parent 父控件，可为空；页面和子对象遵循 Qt 父子所有权
     * @note 无返回值；在 QApplication 创建后的 GUI 线程调用，不执行硬件操作。
     */
    explicit ActionExample(QWidget *parent = nullptr);
};

#endif
```

### 实现文件：`examples/windows/actionexample.cpp`

```cpp
#include "actionexample.h"

#include <QAction>
#include <QLabel>
#include <QMenu>
#include <QToolBar>
#include <QToolButton>
#include <QVBoxLayout>

ActionExample::ActionExample(QWidget *parent)
    : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(12, 12, 12, 12);
    layout->setAlignment(Qt::AlignTop);
    auto *description = new QLabel(tr("一个“显示网格”动作同时放进工具栏和菜单，状态自动同步。"), this);
    description->setWordWrap(true);
    layout->addWidget(description);
    // 所有界面操作在 GUI 线程；子控件由 Qt 的父子对象机制自动释放。
    auto *grid = new QAction(tr("显示网格"), this);
    grid->setCheckable(true);
    auto *bar = new QToolBar(this);
    bar->addAction(grid);
    auto *menu = new QMenu(this);
    menu->addAction(grid);
    auto *button = new QToolButton(this);
    button->setText(tr("更多操作"));
    button->setMenu(menu);
    button->setPopupMode(QToolButton::InstantPopup);
    auto *status = new QLabel(tr("网格：关闭"), this);
    layout->addWidget(bar);
    layout->addWidget(button);
    layout->addWidget(status);
    /** @brief 回显共享动作状态；@param checked 是否勾选；无返回值；只需连接一次业务逻辑。 */
    connect(grid, &QAction::toggled, this,
        [status](bool checked) { status->setText(checked ? tr("网格：开启") : tr("网格：关闭")); });
}
```

## QToolBar

**是什么**：以按钮形式展示常用动作的工具栏。

**用途**：高频操作、编辑工具、导航。

**最常用的方式**：addAction()、addSeparator()、addWidget()、setToolButtonStyle()。下面的实现展示创建控件、配置初始值，再用信号槽处理变化。

**本 demo**：带刷新动作和模式下拉框的工具栏。

**操作步骤**：改变模式并点击刷新，观察状态。

**注意事项**：addWidget 创建的 QWidgetAction 在普通 QWidget 布局中的窄工具栏扩展菜单里可能不完整呈现，正式主窗口优先使用 addToolBar。

全部示例在 GUI 线程操作控件；QObject 子对象由父对象释放。未出现显式资源释放代码时，仍应检查模型、场景、布局项和对话框的所有权。

### 头文件：`examples/windows/toolbarexample.h`

```cpp
#ifndef TOOLBAREXAMPLE_H
#define TOOLBAREXAMPLE_H

#include <QWidget>

/** @brief QToolBar 练习页：带刷新动作和模式下拉框的工具栏。 */
class ToolBarExample : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief 初始化QToolBar示例及信号槽
     * @param parent 父控件，可为空；页面和子对象遵循 Qt 父子所有权
     * @note 无返回值；在 QApplication 创建后的 GUI 线程调用，不执行硬件操作。
     */
    explicit ToolBarExample(QWidget *parent = nullptr);
};

#endif
```

### 实现文件：`examples/windows/toolbarexample.cpp`

```cpp
#include "toolbarexample.h"

#include <QAction>
#include <QComboBox>
#include <QLabel>
#include <QStyle>
#include <QToolBar>
#include <QVBoxLayout>

ToolBarExample::ToolBarExample(QWidget *parent)
    : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(12, 12, 12, 12);
    layout->setAlignment(Qt::AlignTop);
    auto *description = new QLabel(tr("带刷新动作和模式下拉框的工具栏。"), this);
    description->setWordWrap(true);
    layout->addWidget(description);
    // 所有界面操作在 GUI 线程；子控件由 Qt 的父子对象机制自动释放。
    auto *bar = new QToolBar(tr("演示工具栏"), this);
    bar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    auto *refresh = bar->addAction(style()->standardIcon(QStyle::SP_BrowserReload), tr("刷新"));
    bar->addSeparator();
    auto *mode = new QComboBox(bar);
    mode->addItems({ tr("实时"), tr("手动") });
    bar->addWidget(mode);
    auto *status = new QLabel(tr("等待刷新"), this);
    layout->addWidget(bar);
    layout->addWidget(status);
    /** @brief 模拟刷新；无参数、无返回值；读取模式并显示，不启动后台任务。 */
    connect(refresh, &QAction::triggered, this,
        [mode, status] { status->setText(tr("%1模式刷新完成").arg(mode->currentText())); });
}
```

## QStatusBar

**是什么**：显示临时消息和持续状态信息的区域。

**用途**：主窗口底部的操作反馈、连接状态。

**最常用的方式**：showMessage()、clearMessage()、addPermanentWidget()。下面的实现展示创建控件、配置初始值，再用信号槽处理变化。

**本 demo**：左边显示会超时消失的消息，右边保留演示模式状态。

**操作步骤**：点击提示按钮，等待两秒，观察永久标签仍保留。

全部示例在 GUI 线程操作控件；QObject 子对象由父对象释放。未出现显式资源释放代码时，仍应检查模型、场景、布局项和对话框的所有权。

### 头文件：`examples/windows/statusbarexample.h`

```cpp
#ifndef STATUSBAREXAMPLE_H
#define STATUSBAREXAMPLE_H

#include <QWidget>

/** @brief QStatusBar 练习页：左边显示会超时消失的消息，右边保留演示模式状态。 */
class StatusBarExample : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief 初始化QStatusBar示例及信号槽
     * @param parent 父控件，可为空；页面和子对象遵循 Qt 父子所有权
     * @note 无返回值；在 QApplication 创建后的 GUI 线程调用，不执行硬件操作。
     */
    explicit StatusBarExample(QWidget *parent = nullptr);
};

#endif
```

### 实现文件：`examples/windows/statusbarexample.cpp`

```cpp
#include "statusbarexample.h"

#include <QLabel>
#include <QPushButton>
#include <QStatusBar>
#include <QVBoxLayout>

StatusBarExample::StatusBarExample(QWidget *parent)
    : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(12, 12, 12, 12);
    layout->setAlignment(Qt::AlignTop);
    auto *description = new QLabel(tr("左边显示会超时消失的消息，右边保留演示模式状态。"), this);
    description->setWordWrap(true);
    layout->addWidget(description);
    // 所有界面操作在 GUI 线程；子控件由 Qt 的父子对象机制自动释放。
    auto *bar = new QStatusBar(this);
    bar->setSizeGripEnabled(false);
    auto *permanent = new QLabel(tr("模式：演示"), bar);
    bar->addPermanentWidget(permanent);
    auto *show = new QPushButton(tr("显示 2 秒临时消息"), this);
    layout->addWidget(show);
    layout->addStretch(1);
    layout->addWidget(bar);
    /** @brief 显示短期操作反馈；无参数、无返回值；毫秒超时由状态栏内部计时。 */
    connect(show, &QPushButton::clicked, this, [bar] { bar->showMessage(tr("操作完成"), 2000); });
}
```
