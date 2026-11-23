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
