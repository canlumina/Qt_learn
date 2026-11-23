#ifndef SCROLLAREAEXAMPLE_H
#define SCROLLAREAEXAMPLE_H

#include <QWidget>

/** @brief QScrollArea 练习页：一个包含 30 个参数输入框的长表单。 */
class ScrollAreaExample : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief 初始化QScrollArea示例及信号槽
     * @param parent 父控件，可为空；页面和子对象遵循 Qt 父子所有权
     * @note 无返回值；在 QApplication 创建后的 GUI 线程调用，不执行硬件操作。
     */
    explicit ScrollAreaExample(QWidget *parent = nullptr);
};

#endif
