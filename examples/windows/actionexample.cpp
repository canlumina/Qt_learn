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
