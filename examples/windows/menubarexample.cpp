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
