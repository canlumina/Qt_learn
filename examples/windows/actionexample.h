#ifndef ACTIONEXAMPLE_H
#define ACTIONEXAMPLE_H

#include <QWidget>

/** @brief QAction 练习页：一个“显示网格”动作同时放进工具栏和菜单，状态自动同步。 */
class ActionExample : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief 初始化QAction示例及信号槽
     * @param parent 父控件，可为空；页面和子对象遵循 Qt 父子所有权
     * @note 无返回值；在 QApplication 创建后的 GUI 线程调用，不执行硬件操作。
     */
    explicit ActionExample(QWidget *parent = nullptr);
};

#endif
