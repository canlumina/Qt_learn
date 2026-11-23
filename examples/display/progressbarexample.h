#ifndef PROGRESSBAREXAMPLE_H
#define PROGRESSBAREXAMPLE_H

#include <QWidget>

/** @brief QProgressBar 练习页：定时器模拟进度，可切换确定进度和忙碌模式，支持重新开始。 */
class ProgressBarExample : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief 初始化QProgressBar示例及信号槽
     * @param parent 父控件，可为空；页面和子对象遵循 Qt 父子所有权
     * @note 无返回值；在 QApplication 创建后的 GUI 线程调用，不执行硬件操作。
     */
    explicit ProgressBarExample(QWidget *parent = nullptr);

private:
    int completed = 0; // 已完成百分比，与忙碌模式的显示范围分开保存。
};

#endif
