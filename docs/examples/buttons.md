# 按钮示例与完整代码

[返回学习路线](README.md)

## QToolButton

**是什么**：紧凑的工具按钮，支持图标、默认动作和下拉菜单。

**用途**：工具栏、快速操作入口、带更多选项的按钮。

**最常用的方式**：setDefaultAction()、setMenu()、setPopupMode()。下面的实现展示创建控件、配置初始值，再用信号槽处理变化。

**本 demo**：一个主操作加两个菜单选项，操作结果显示在标签中。

**操作步骤**：点击按钮正文，再点击右侧箭头，选择不同模式。

全部示例在 GUI 线程操作控件；QObject 子对象由父对象释放。未出现显式资源释放代码时，仍应检查模型、场景、布局项和对话框的所有权。

### 头文件：`examples/buttons/toolbuttonexample.h`

```cpp
#ifndef TOOLBUTTONEXAMPLE_H
#define TOOLBUTTONEXAMPLE_H

#include <QWidget>

/** @brief QToolButton 练习页：一个主操作加两个菜单选项，操作结果显示在标签中。 */
class ToolButtonExample : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief 初始化QToolButton示例及信号槽
     * @param parent 父控件，可为空；页面和子对象遵循 Qt 父子所有权
     * @note 无返回值；在 QApplication 创建后的 GUI 线程调用，不执行硬件操作。
     */
    explicit ToolButtonExample(QWidget *parent = nullptr);
};

#endif
```

### 实现文件：`examples/buttons/toolbuttonexample.cpp`

```cpp
#include "toolbuttonexample.h"

#include <QAction>
#include <QLabel>
#include <QMenu>
#include <QStyle>
#include <QToolButton>
#include <QVBoxLayout>

ToolButtonExample::ToolButtonExample(QWidget *parent)
    : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(12, 12, 12, 12);
    layout->setAlignment(Qt::AlignTop);
    auto *description = new QLabel(tr("一个主操作加两个菜单选项，操作结果显示在标签中。"), this);
    description->setWordWrap(true);
    layout->addWidget(description);
    // 所有界面操作在 GUI 线程；子控件由 Qt 的父子对象机制自动释放。
    auto *button = new QToolButton(this);
    auto *status = new QLabel(tr("等待操作"), this);
    auto *action = new QAction(style()->standardIcon(QStyle::SP_DialogApplyButton), tr("执行采样"), this);
    button->setDefaultAction(action);
    button->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    auto *menu = new QMenu(button);
    menu->addAction(tr("快速采样"));
    menu->addAction(tr("精细采样"));
    button->setMenu(menu);
    button->setPopupMode(QToolButton::MenuButtonPopup);
    layout->addWidget(button);
    layout->addWidget(status);
    /** @brief 响应主操作；无参数、无返回值；GUI 线程更新标签。 */
    connect(action, &QAction::triggered, this, [status] { status->setText(tr("已执行默认采样")); });
    /** @brief 显示菜单操作；@param selected 本次触发的动作；无返回值；动作由菜单管理。 */
    connect(menu, &QMenu::triggered, this,
        [status](QAction *selected) { status->setText(tr("已选择：%1").arg(selected->text())); });
}
```
