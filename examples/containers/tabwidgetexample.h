#ifndef TABWIDGETEXAMPLE_H
#define TABWIDGETEXAMPLE_H

#include <QWidget>

/** @brief QTabWidget 练习页：连接配置与采样配置两个选项卡。 */
class TabWidgetExample : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief 初始化QTabWidget示例及信号槽
     * @param parent 父控件，可为空；页面和子对象遵循 Qt 父子所有权
     * @note 无返回值；在 QApplication 创建后的 GUI 线程调用，不执行硬件操作。
     */
    explicit TabWidgetExample(QWidget *parent = nullptr);
};

#endif
