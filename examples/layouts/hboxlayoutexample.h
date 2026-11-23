#ifndef HBOXLAYOUTEXAMPLE_H
#define HBOXLAYOUTEXAMPLE_H

#include <QWidget>

/** @brief QHBoxLayout 练习页：标签、可伸缩输入框、提交按钮位于同一行。 */
class HBoxLayoutExample : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief 初始化QHBoxLayout示例及信号槽
     * @param parent 父控件，可为空；页面和子对象遵循 Qt 父子所有权
     * @note 无返回值；在 QApplication 创建后的 GUI 线程调用，不执行硬件操作。
     */
    explicit HBoxLayoutExample(QWidget *parent = nullptr);
};

#endif
