#ifndef FORMLAYOUTEXAMPLE_H
#define FORMLAYOUTEXAMPLE_H

#include <QWidget>

/** @brief QFormLayout 练习页：设备名称、采样周期、备注组成一个可伸缩表单。 */
class FormLayoutExample : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief 初始化QFormLayout示例及信号槽
     * @param parent 父控件，可为空；页面和子对象遵循 Qt 父子所有权
     * @note 无返回值；在 QApplication 创建后的 GUI 线程调用，不执行硬件操作。
     */
    explicit FormLayoutExample(QWidget *parent = nullptr);
};

#endif
