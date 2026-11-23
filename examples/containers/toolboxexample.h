#ifndef TOOLBOXEXAMPLE_H
#define TOOLBOXEXAMPLE_H

#include <QWidget>

/** @brief QToolBox 练习页：常规、显示、维护三个工具页。 */
class ToolBoxExample : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief 初始化QToolBox示例及信号槽
     * @param parent 父控件，可为空；页面和子对象遵循 Qt 父子所有权
     * @note 无返回值；在 QApplication 创建后的 GUI 线程调用，不执行硬件操作。
     */
    explicit ToolBoxExample(QWidget *parent = nullptr);
};

#endif
