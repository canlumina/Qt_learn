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
