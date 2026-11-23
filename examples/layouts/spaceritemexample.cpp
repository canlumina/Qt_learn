#include "spaceritemexample.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QSizePolicy>
#include <QSpacerItem>
#include <QVBoxLayout>

SpacerItemExample::SpacerItemExample(QWidget *parent)
    : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(12, 12, 12, 12);
    layout->setAlignment(Qt::AlignTop);
    auto *description = new QLabel(tr("固定宽度占位和水平伸缩占位同时演示。"), this);
    description->setWordWrap(true);
    layout->addWidget(description);
    // 所有界面操作在 GUI 线程；子控件由 Qt 的父子对象机制自动释放。
    auto *row = new QHBoxLayout;
    row->addWidget(new QLabel(tr("左侧说明"), this));
    // addItem 后由布局拥有占位项，不需要单独 delete。
    row->addItem(new QSpacerItem(24, 0, QSizePolicy::Fixed, QSizePolicy::Minimum));
    row->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));
    row->addWidget(new QPushButton(tr("取消（布局示意）"), this));
    row->addWidget(new QPushButton(tr("应用（布局示意）"), this));
    layout->addLayout(row);
    layout->addStretch(1);
    layout->addWidget(new QLabel(tr("上方还有一个竖向弹簧，这段文字保持在底部。"), this));
}
