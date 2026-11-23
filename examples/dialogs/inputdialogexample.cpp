#include "inputdialogexample.h"

#include <QInputDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QString>
#include <QVBoxLayout>

InputDialogExample::InputDialogExample(QWidget *parent)
    : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(12, 12, 12, 12);
    layout->setAlignment(Qt::AlignTop);
    auto *description = new QLabel(tr("输入通道名称或采样次数，正确区分确认与取消。"), this);
    description->setWordWrap(true);
    layout->addWidget(description);
    // 所有界面操作在 GUI 线程；子控件由 Qt 的父子对象机制自动释放。
    auto *text = new QPushButton(tr("输入名称"), this);
    auto *number = new QPushButton(tr("输入次数"), this);
    auto *status = new QLabel(tr("等待输入"), this);
    status->setTextFormat(Qt::PlainText);
    layout->addWidget(text);
    layout->addWidget(number);
    layout->addWidget(status);
    /** @brief 读取名称；无参数、无返回值；用 ok 区分取消与确认空字符串。 */
    connect(text, &QPushButton::clicked, this, [this, status] {
        bool ok = false;
        const QString name
            = QInputDialog::getText(this, tr("名称"), tr("通道名称："), QLineEdit::Normal, QString(), &ok);
        status->setText(ok ? tr("已确认名称：%1").arg(name) : tr("已取消"));
    });
    /** @brief 读取次数；无参数、无返回值；限制 1～1000，取消不使用返回值。 */
    connect(number, &QPushButton::clicked, this, [this, status] {
        bool ok = false;
        const int count = QInputDialog::getInt(this, tr("次数"), tr("采样次数："), 10, 1, 1000, 1, &ok);
        status->setText(ok ? tr("次数：%1").arg(count) : tr("已取消"));
    });
}
