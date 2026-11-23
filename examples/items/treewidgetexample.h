#ifndef TREEWIDGETEXAMPLE_H
#define TREEWIDGETEXAMPLE_H

#include <QWidget>

/** @brief QTreeWidget 练习页：设备、分组与通道的两级树，点击显示条目路径。 */
class TreeWidgetExample : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief 初始化QTreeWidget示例及信号槽
     * @param parent 父控件，可为空；页面和子对象遵循 Qt 父子所有权
     * @note 无返回值；在 QApplication 创建后的 GUI 线程调用，不执行硬件操作。
     */
    explicit TreeWidgetExample(QWidget *parent = nullptr);
};

#endif
