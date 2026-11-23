#ifndef TIMEEDITEXAMPLE_H
#define TIMEEDITEXAMPLE_H

#include <QWidget>

/** @brief QTimeEdit 练习页：编辑模拟定时任务的执行时间。 */
class TimeEditExample : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief 初始化QTimeEdit示例及信号槽
     * @param parent 父控件，可为空；页面和子对象遵循 Qt 父子所有权
     * @note 无返回值；在 QApplication 创建后的 GUI 线程调用，不执行硬件操作。
     */
    explicit TimeEditExample(QWidget *parent = nullptr);
};

#endif
