#ifndef INPUTDIALOGEXAMPLE_H
#define INPUTDIALOGEXAMPLE_H

#include <QWidget>

/** @brief QInputDialog 练习页：输入通道名称或采样次数，正确区分确认与取消。 */
class InputDialogExample : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief 初始化QInputDialog示例及信号槽
     * @param parent 父控件，可为空；页面和子对象遵循 Qt 父子所有权
     * @note 无返回值；在 QApplication 创建后的 GUI 线程调用，不执行硬件操作。
     */
    explicit InputDialogExample(QWidget *parent = nullptr);
};

#endif
