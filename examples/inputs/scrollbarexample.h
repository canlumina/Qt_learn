#ifndef SCROLLBAREXAMPLE_H
#define SCROLLBAREXAMPLE_H

#include <QWidget>

/** @brief QScrollBar 练习页：模拟在 0～900 的数据偏移中移动。 */
class ScrollBarExample : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief 初始化QScrollBar示例及信号槽
     * @param parent 父控件，可为空；页面和子对象遵循 Qt 父子所有权
     * @note 无返回值；在 QApplication 创建后的 GUI 线程调用，不执行硬件操作。
     */
    explicit ScrollBarExample(QWidget *parent = nullptr);
};

#endif
