#ifndef FRAMEEXAMPLE_H
#define FRAMEEXAMPLE_H

#include <QWidget>

/** @brief QFrame 练习页：上方带边框的说明区域，下方使用水平分隔线。 */
class FrameExample : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief 初始化QFrame示例及信号槽
     * @param parent 父控件，可为空；页面和子对象遵循 Qt 父子所有权
     * @note 无返回值；在 QApplication 创建后的 GUI 线程调用，不执行硬件操作。
     */
    explicit FrameExample(QWidget *parent = nullptr);
};

#endif
