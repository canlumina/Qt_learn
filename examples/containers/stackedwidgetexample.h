#ifndef STACKEDWIDGETEXAMPLE_H
#define STACKEDWIDGETEXAMPLE_H

#include <QWidget>

/** @brief QStackedWidget 练习页：导航列表切换概览与参数页面。 */
class StackedWidgetExample : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief 初始化QStackedWidget示例及信号槽
     * @param parent 父控件，可为空；页面和子对象遵循 Qt 父子所有权
     * @note 无返回值；在 QApplication 创建后的 GUI 线程调用，不执行硬件操作。
     */
    explicit StackedWidgetExample(QWidget *parent = nullptr);
};

#endif
