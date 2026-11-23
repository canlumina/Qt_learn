#ifndef TOOLBUTTONEXAMPLE_H
#define TOOLBUTTONEXAMPLE_H

#include <QWidget>

/** @brief QToolButton 练习页：一个主操作加两个菜单选项，操作结果显示在标签中。 */
class ToolButtonExample : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief 初始化QToolButton示例及信号槽
     * @param parent 父控件，可为空；页面和子对象遵循 Qt 父子所有权
     * @note 无返回值；在 QApplication 创建后的 GUI 线程调用，不执行硬件操作。
     */
    explicit ToolButtonExample(QWidget *parent = nullptr);
};

#endif
