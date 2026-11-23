#include "dateeditexample.h"

#include <QDate>
#include <QDateEdit>
#include <QLabel>
#include <QVBoxLayout>

DateEditExample::DateEditExample(QWidget *parent)
    : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(12, 12, 12, 12);
    layout->setAlignment(Qt::AlignTop);
    auto *description = new QLabel(tr("带日历弹窗的日期输入，选择后显示 ISO 日期。"), this);
    description->setWordWrap(true);
    layout->addWidget(description);
    // 所有界面操作在 GUI 线程；子控件由 Qt 的父子对象机制自动释放。
    auto *input = new QDateEdit(QDate::currentDate(), this);
    input->setDisplayFormat("yyyy-MM-dd");
    input->setDateRange(QDate(2000, 1, 1), QDate(2100, 12, 31));
    input->setCalendarPopup(true);
    auto *status = new QLabel(input->date().toString(Qt::ISODate), this);
    layout->addWidget(input);
    layout->addWidget(status);
    /** @brief 显示选定日期；@param date 有效日期；无返回值；不修改系统时间。 */
    connect(input, &QDateEdit::dateChanged, this,
        [status](const QDate &date) { status->setText(date.toString(Qt::ISODate)); });
}
