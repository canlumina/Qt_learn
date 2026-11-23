#ifndef SPACERITEMEXAMPLE_H
#define SPACERITEMEXAMPLE_H

#include <QWidget>

/** @brief QSpacerItem 练习页：固定宽度占位和水平伸缩占位同时演示。 */
class SpacerItemExample : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief 初始化QSpacerItem示例及信号槽
     * @param parent 父控件，可为空；页面和子对象遵循 Qt 父子所有权
     * @note 无返回值；在 QApplication 创建后的 GUI 线程调用，不执行硬件操作。
     */
    explicit SpacerItemExample(QWidget *parent = nullptr);
};

#endif
