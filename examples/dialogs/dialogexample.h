#ifndef DIALOGEXAMPLE_H
#define DIALOGEXAMPLE_H

#include <QWidget>

/** @brief QDialog 练习页：自定义通道名称对话框，确认后回显，取消保留原值。 */
class DialogExample : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief 初始化QDialog示例及信号槽
     * @param parent 父控件，可为空；页面和子对象遵循 Qt 父子所有权
     * @note 无返回值；在 QApplication 创建后的 GUI 线程调用，不执行硬件操作。
     */
    explicit DialogExample(QWidget *parent = nullptr);
};

#endif
