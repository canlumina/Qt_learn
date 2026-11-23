#ifndef LISTVIEWEXAMPLE_H
#define LISTVIEWEXAMPLE_H

#include <QWidget>

/** @brief QListView 练习页：使用 QStringListModel 提供列表，选择时从 QModelIndex 读取数据。 */
class ListViewExample : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief 初始化QListView示例及信号槽
     * @param parent 父控件，可为空；页面和子对象遵循 Qt 父子所有权
     * @note 无返回值；在 QApplication 创建后的 GUI 线程调用，不执行硬件操作。
     */
    explicit ListViewExample(QWidget *parent = nullptr);
};

#endif
