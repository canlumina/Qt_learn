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
