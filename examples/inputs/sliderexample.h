#ifndef SLIDEREXAMPLE_H
#define SLIDEREXAMPLE_H

#include <QWidget>

/** @brief QSlider 练习页：滑块与数值框双向同步，显示模拟亮度百分比。 */
class SliderExample : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief 初始化QSlider示例及信号槽
     * @param parent 父控件，可为空；页面和子对象遵循 Qt 父子所有权
     * @note 无返回值；在 QApplication 创建后的 GUI 线程调用，不执行硬件操作。
     */
    explicit SliderExample(QWidget *parent = nullptr);
};

#endif
