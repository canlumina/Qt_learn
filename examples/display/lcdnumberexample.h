#ifndef LCDNUMBEREXAMPLE_H
#define LCDNUMBEREXAMPLE_H

#include <QWidget>

/** @brief QLCDNumber 练习页：数值框调整模拟电压，LCD 回显带一位小数的读数。 */
class LCDNumberExample : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief 初始化QLCDNumber示例及信号槽
     * @param parent 父控件，可为空；页面和子对象遵循 Qt 父子所有权
     * @note 无返回值；在 QApplication 创建后的 GUI 线程调用，不执行硬件操作。
     */
    explicit LCDNumberExample(QWidget *parent = nullptr);
};

#endif
