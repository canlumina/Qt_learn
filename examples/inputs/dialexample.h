#ifndef DIALEXAMPLE_H
#define DIALEXAMPLE_H

#include <QWidget>

/** @brief QDial 练习页：用旋钮调整模拟输出百分比。 */
class DialExample : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief 初始化QDial示例及信号槽
     * @param parent 父控件，可为空；页面和子对象遵循 Qt 父子所有权
     * @note 无返回值；在 QApplication 创建后的 GUI 线程调用，不执行硬件操作。
     */
    explicit DialExample(QWidget *parent = nullptr);
};

#endif
