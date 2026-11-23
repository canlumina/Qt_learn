#include "messageboxexample.h"

#include <QLabel>
#include <QMessageBox>
#include <QPushButton>
#include <QVBoxLayout>

MessageBoxExample::MessageBoxExample(QWidget *parent)
    : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(12, 12, 12, 12);
    layout->setAlignment(Qt::AlignTop);
    auto *description = new QLabel(tr("安全的模拟确认，默认选择否，不执行真实删除。"), this);
    description->setWordWrap(true);
    layout->addWidget(description);
    // 所有界面操作在 GUI 线程；子控件由 Qt 的父子对象机制自动释放。
    auto *ask = new QPushButton(tr("模拟操作确认"), this);
    auto *status = new QLabel(tr("尚未确认"), this);
    layout->addWidget(ask);
    layout->addWidget(status);
    /** @brief 询问模拟操作；无参数、无返回值；模态对话框，默认 No，不修改文件。 */
    connect(ask, &QPushButton::clicked, this, [this, status] {
        const auto answer = QMessageBox::question(this, tr("确认"), tr("要执行这次模拟操作吗？"),
            QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
        status->setText(answer == QMessageBox::Yes ? tr("已确认模拟操作") : tr("已取消"));
    });
}
