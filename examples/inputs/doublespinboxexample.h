#ifndef DOUBLESPINBOXEXAMPLE_H
#define DOUBLESPINBOXEXAMPLE_H

#include <QWidget>

/** @brief QDoubleSpinBox 练习页：输入目标温度，实时显示取到的数值。 */
class DoubleSpinBoxExample : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief 初始化QDoubleSpinBox示例及信号槽
     * @param parent 父控件，可为空；页面和子对象遵循 Qt 父子所有权
     * @note 无返回值；在 QApplication 创建后的 GUI 线程调用，不执行硬件操作。
     */
    explicit DoubleSpinBoxExample(QWidget *parent = nullptr);
};

#endif
