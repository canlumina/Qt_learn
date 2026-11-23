#ifndef TOOLBAREXAMPLE_H
#define TOOLBAREXAMPLE_H

#include <QWidget>

/** @brief QToolBar 练习页：带刷新动作和模式下拉框的工具栏。 */
class ToolBarExample : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief 初始化QToolBar示例及信号槽
     * @param parent 父控件，可为空；页面和子对象遵循 Qt 父子所有权
     * @note 无返回值；在 QApplication 创建后的 GUI 线程调用，不执行硬件操作。
     */
    explicit ToolBarExample(QWidget *parent = nullptr);
};

#endif
