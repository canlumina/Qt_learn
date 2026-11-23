#ifndef WIDGETEXAMPLE_H
#define WIDGETEXAMPLE_H

#include <QWidget>

/** @brief QWidget 练习页：一个整体启用或禁用的参数区域。 */
class WidgetExample : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief 初始化QWidget示例及信号槽
     * @param parent 父控件，可为空；页面和子对象遵循 Qt 父子所有权
     * @note 无返回值；在 QApplication 创建后的 GUI 线程调用，不执行硬件操作。
     */
    explicit WidgetExample(QWidget *parent = nullptr);
};

#endif
