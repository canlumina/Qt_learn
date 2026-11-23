#ifndef MESSAGEBOXEXAMPLE_H
#define MESSAGEBOXEXAMPLE_H

#include <QWidget>

/** @brief QMessageBox 练习页：安全的模拟确认，默认选择否，不执行真实删除。 */
class MessageBoxExample : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief 初始化QMessageBox示例及信号槽
     * @param parent 父控件，可为空；页面和子对象遵循 Qt 父子所有权
     * @note 无返回值；在 QApplication 创建后的 GUI 线程调用，不执行硬件操作。
     */
    explicit MessageBoxExample(QWidget *parent = nullptr);
};

#endif
