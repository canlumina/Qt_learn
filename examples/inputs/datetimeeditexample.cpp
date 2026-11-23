#include "datetimeeditexample.h"

#include <QDateTime>
#include <QDateTimeEdit>
#include <QLabel>
#include <QVBoxLayout>

DateTimeEditExample::DateTimeEditExample(QWidget *parent)
    : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(12, 12, 12, 12);
    layout->setAlignment(Qt::AlignTop);
    auto *description = new QLabel(tr("设置模拟预约时间，回显本地日期时间。"), this);
    description->setWordWrap(true);
    layout->addWidget(description);
    // 所有界面操作在 GUI 线程；子控件由 Qt 的父子对象机制自动释放。
    auto *input = new QDateTimeEdit(QDateTime::currentDateTime(), this);
    input->setDisplayFormat("yyyy-MM-dd HH:mm:ss");
    input->setCalendarPopup(true);
    auto *status = new QLabel(input->dateTime().toString(Qt::ISODate), this);
    layout->addWidget(input);
    layout->addWidget(status);
    /** @brief 回显日期时间；@param value 控件当前时间值；无返回值；不修改系统时钟。 */
    connect(input, &QDateTimeEdit::dateTimeChanged, this,
        [status](const QDateTime &value) { status->setText(value.toString(Qt::ISODate)); });
}
