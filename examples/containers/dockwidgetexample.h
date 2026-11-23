#ifndef DOCKWIDGETEXAMPLE_H
#define DOCKWIDGETEXAMPLE_H

#include <QWidget>

/** @brief QDockWidget 练习页：嵌入一个主窗口，提供可拖动日志面板和恢复显示按钮。 */
class DockWidgetExample : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief 初始化QDockWidget示例及信号槽
     * @param parent 父控件，可为空；页面和子对象遵循 Qt 父子所有权
     * @note 无返回值；在 QApplication 创建后的 GUI 线程调用，不执行硬件操作。
     */
    explicit DockWidgetExample(QWidget *parent = nullptr);
};

#endif
