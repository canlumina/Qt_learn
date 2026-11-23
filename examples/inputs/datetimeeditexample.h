#ifndef DATETIMEEDITEXAMPLE_H
#define DATETIMEEDITEXAMPLE_H

#include <QWidget>

/** @brief QDateTimeEdit 练习页：设置模拟预约时间，回显本地日期时间。 */
class DateTimeEditExample : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief 初始化QDateTimeEdit示例及信号槽
     * @param parent 父控件，可为空；页面和子对象遵循 Qt 父子所有权
     * @note 无返回值；在 QApplication 创建后的 GUI 线程调用，不执行硬件操作。
     */
    explicit DateTimeEditExample(QWidget *parent = nullptr);
};

#endif
