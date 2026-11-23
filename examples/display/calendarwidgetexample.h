#ifndef CALENDARWIDGETEXAMPLE_H
#define CALENDARWIDGETEXAMPLE_H

#include <QWidget>

/** @brief QCalendarWidget 练习页：日历选择与日期回显，同时突出标记今天。 */
class CalendarWidgetExample : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief 初始化QCalendarWidget示例及信号槽
     * @param parent 父控件，可为空；页面和子对象遵循 Qt 父子所有权
     * @note 无返回值；在 QApplication 创建后的 GUI 线程调用，不执行硬件操作。
     */
    explicit CalendarWidgetExample(QWidget *parent = nullptr);
};

#endif
