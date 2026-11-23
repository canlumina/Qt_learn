#include "timeeditexample.h"

#include <QLabel>
#include <QTime>
#include <QTimeEdit>
#include <QVBoxLayout>

TimeEditExample::TimeEditExample(QWidget *parent)
    : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(12, 12, 12, 12);
    layout->setAlignment(Qt::AlignTop);
    auto *description = new QLabel(tr("编辑模拟定时任务的执行时间。"), this);
    description->setWordWrap(true);
    layout->addWidget(description);
    // 所有界面操作在 GUI 线程；子控件由 Qt 的父子对象机制自动释放。
    auto *input = new QTimeEdit(QTime(8, 30, 0), this);
    input->setDisplayFormat("HH:mm:ss");
    auto *status = new QLabel(tr("执行时间：08:30:00"), this);
    layout->addWidget(input);
    layout->addWidget(status);
    /** @brief 回显时刻；@param time 一天中的时间；无返回值；不实际创建系统定时任务。 */
    connect(input, &QTimeEdit::timeChanged, this,
        [status](const QTime &time) { status->setText(tr("执行时间：%1").arg(time.toString("HH:mm:ss"))); });
}
