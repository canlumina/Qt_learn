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
