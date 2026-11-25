#include "hboxlayout.h"

HBoxLayout::HBoxLayout(QWidget *parent) : QWidget(parent)
{
    layout = new QHBoxLayout(this);
    layout->setContentsMargins(12, 12, 12, 12);
    layout->setAlignment(Qt::AlignTop);
    description = new QLabel(tr("标签、可伸缩输入框、提交按钮位于同一行。"), this);
    layout->addWidget(description);

    row = new QHBoxLayout;
    input = new QLineEdit(this);
    apply = new QPushButton(tr("应用"), this);
    status = new QLabel(tr("等待输入"), this);

    status->setTextFormat(Qt::RichText);
    status->setWordWrap(true);
    row->addWidget(new QLabel(tr("设备名称:"), this));
    row->addWidget(input, 1);
    row->addWidget(apply);

    layout->addLayout(row);
    layout->addWidget(status);

    /**
     * @brief 点击应用后将输入内容回显到状态标签
     * @note 无参数、无返回值；在 GUI 线程执行，状态标签按当前 RichText 设置解释内容。
     */
    connect(apply, &QPushButton::clicked, this, [this]() {
        status->setText(tr("已应用: %1").arg(input->text()));
    });
}
