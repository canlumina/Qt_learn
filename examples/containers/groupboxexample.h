#ifndef GROUPBOXEXAMPLE_H
#define GROUPBOXEXAMPLE_H

#include <QWidget>

/** @brief QGroupBox 练习页：两组独立的单选模式，其中高级配置可以整体关闭。 */
class GroupBoxExample : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief 初始化QGroupBox示例及信号槽
     * @param parent 父控件，可为空；页面和子对象遵循 Qt 父子所有权
     * @note 无返回值；在 QApplication 创建后的 GUI 线程调用，不执行硬件操作。
     */
    explicit GroupBoxExample(QWidget *parent = nullptr);
};

#endif
