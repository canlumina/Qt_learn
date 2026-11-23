#include "dialogexample.h"

#include <QDialog>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>

DialogExample::DialogExample(QWidget *parent)
    : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(12, 12, 12, 12);
    layout->setAlignment(Qt::AlignTop);
    auto *description = new QLabel(tr("自定义通道名称对话框，确认后回显，取消保留原值。"), this);
    description->setWordWrap(true);
    layout->addWidget(description);
    // 所有界面操作在 GUI 线程；子控件由 Qt 的父子对象机制自动释放。
    auto *open = new QPushButton(tr("编辑名称"), this);
    auto *status = new QLabel(tr("通道一"), this);
    status->setTextFormat(Qt::PlainText);
    layout->addWidget(open);
    layout->addWidget(status);
    /** @brief 打开临时参数对话框；无参数、无返回值；栈对象仅在 exec 结束后销毁。 */
    connect(open, &QPushButton::clicked, this, [this, status] {
        QDialog dialog(this);
        dialog.setWindowTitle(tr("通道名称"));
        auto *form = new QFormLayout(&dialog);
        auto *input = new QLineEdit(status->text(), &dialog);
        auto *buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, &dialog);
        form->addRow(tr("名称："), input);
        form->addRow(buttons);
        connect(buttons, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
        connect(buttons, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);
        if (dialog.exec() == QDialog::Accepted)
            status->setText(input->text());
    });
}
