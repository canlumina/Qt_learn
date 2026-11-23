#include "calendarwidgetexample.h"

#include <QCalendarWidget>
#include <QColor>
#include <QDate>
#include <QFont>
#include <QLabel>
#include <QTextCharFormat>
#include <QVBoxLayout>

CalendarWidgetExample::CalendarWidgetExample(QWidget *parent)
    : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(12, 12, 12, 12);
    layout->setAlignment(Qt::AlignTop);
    auto *description = new QLabel(tr("日历选择与日期回显，同时突出标记今天。"), this);
    description->setWordWrap(true);
    layout->addWidget(description);
    // 所有界面操作在 GUI 线程；子控件由 Qt 的父子对象机制自动释放。
    auto *calendar = new QCalendarWidget(this);
    calendar->setGridVisible(true);
    QTextCharFormat todayFormat;
    todayFormat.setForeground(QColor("#b54832"));
    todayFormat.setFontWeight(QFont::Bold);
    calendar->setDateTextFormat(QDate::currentDate(), todayFormat);
    auto *status = new QLabel(calendar->selectedDate().toString(Qt::ISODate), this);
    layout->addWidget(calendar, 1);
    layout->addWidget(status);
    /** @brief 回显选择；无参数、无返回值；通过 selectedDate 获取当前日期。 */
    connect(calendar, &QCalendarWidget::selectionChanged, this,
        [calendar, status] { status->setText(calendar->selectedDate().toString(Qt::ISODate)); });
}
