#ifndef TREEVIEWEXAMPLE_H
#define TREEVIEWEXAMPLE_H

#include <QWidget>

/** @brief QTreeView 练习页：用 QStandardItemModel 构建设备和通道层级。 */
class TreeViewExample : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief 初始化QTreeView示例及信号槽
     * @param parent 父控件，可为空；页面和子对象遵循 Qt 父子所有权
     * @note 无返回值；在 QApplication 创建后的 GUI 线程调用，不执行硬件操作。
     */
    explicit TreeViewExample(QWidget *parent = nullptr);
};

#endif
