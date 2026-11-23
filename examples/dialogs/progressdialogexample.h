#ifndef PROGRESSDIALOGEXAMPLE_H
#define PROGRESSDIALOGEXAMPLE_H

#include <QWidget>

/** @brief QProgressDialog 练习页：定时器驱动的模拟任务，可取消并重新开始。 */
class ProgressDialogExample : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief 初始化QProgressDialog示例及信号槽
     * @param parent 父控件，可为空；页面和子对象遵循 Qt 父子所有权
     * @note 无返回值；在 QApplication 创建后的 GUI 线程调用，不执行硬件操作。
     */
    explicit ProgressDialogExample(QWidget *parent = nullptr);
};

#endif
