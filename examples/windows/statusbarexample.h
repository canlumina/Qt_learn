#ifndef STATUSBAREXAMPLE_H
#define STATUSBAREXAMPLE_H

#include <QWidget>

/** @brief QStatusBar 练习页：左边显示会超时消失的消息，右边保留演示模式状态。 */
class StatusBarExample : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief 初始化QStatusBar示例及信号槽
     * @param parent 父控件，可为空；页面和子对象遵循 Qt 父子所有权
     * @note 无返回值；在 QApplication 创建后的 GUI 线程调用，不执行硬件操作。
     */
    explicit StatusBarExample(QWidget *parent = nullptr);
};

#endif
