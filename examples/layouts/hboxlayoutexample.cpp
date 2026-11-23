#include "hboxlayoutexample.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>

HBoxLayoutExample::HBoxLayoutExample(QWidget *parent)
    : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(12, 12, 12, 12);
    layout->setAlignment(Qt::AlignTop);
    auto *description = new QLabel(tr("标签、可伸缩输入框、提交按钮位于同一行。"), this);
    description->setWordWrap(true);
    layout->addWidget(description);
    // 所有界面操作在 GUI 线程；子控件由 Qt 的父子对象机制自动释放。
    auto *row = new QHBoxLayout;
    auto *input = new QLineEdit(this);
    auto *apply = new QPushButton(tr("应用"), this);
    auto *status = new QLabel(tr("等待输入"), this);
    status->setTextFormat(Qt::PlainText);
    status->setWordWrap(true);
    row->addWidget(new QLabel(tr("设备名称："), this));
    row->addWidget(input, 1);
    row->addWidget(apply);
    layout->addLayout(row);
    layout->addWidget(status);
    /** @brief 显示输入；无参数、无返回值；只更新纯文本标签，不连接真实设备。 */
    connect(apply, &QPushButton::clicked, this, [input, status] { status->setText(input->text()); });
}
