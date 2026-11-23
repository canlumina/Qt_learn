#ifndef DATEEDITEXAMPLE_H
#define DATEEDITEXAMPLE_H

#include <QWidget>

/** @brief QDateEdit 练习页：带日历弹窗的日期输入，选择后显示 ISO 日期。 */
class DateEditExample : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief 初始化QDateEdit示例及信号槽
     * @param parent 父控件，可为空；页面和子对象遵循 Qt 父子所有权
     * @note 无返回值；在 QApplication 创建后的 GUI 线程调用，不执行硬件操作。
     */
    explicit DateEditExample(QWidget *parent = nullptr);
};

#endif
