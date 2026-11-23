#include "stackedlayoutexample.h"

#include <QComboBox>
#include <QLabel>
#include <QStackedLayout>
#include <QVBoxLayout>
#include <QWidget>
#include <QtGlobal>

StackedLayoutExample::StackedLayoutExample(QWidget *parent)
    : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(12, 12, 12, 12);
    layout->setAlignment(Qt::AlignTop);
    auto *description = new QLabel(tr("下拉框切换两个布局页面。"), this);
    description->setWordWrap(true);
    layout->addWidget(description);
    // 所有界面操作在 GUI 线程；子控件由 Qt 的父子对象机制自动释放。
    auto *select = new QComboBox(this);
    select->addItems({ tr("概览"), tr("设置") });
    auto *host = new QWidget(this);
    auto *stack = new QStackedLayout(host);
    auto *overview = new QLabel(tr("概览：系统处于演示模式"), host);
    overview->setAlignment(Qt::AlignCenter);
    auto *settings = new QLabel(tr("设置：这里可以放参数输入控件"), host);
    settings->setAlignment(Qt::AlignCenter);
    stack->addWidget(overview);
    stack->addWidget(settings);
    layout->addWidget(select);
    layout->addWidget(host, 1);
    connect(
        select, QOverload<int>::of(&QComboBox::currentIndexChanged), stack, &QStackedLayout::setCurrentIndex);
}
