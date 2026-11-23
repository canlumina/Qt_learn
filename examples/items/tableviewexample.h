#ifndef TABLEVIEWEXAMPLE_H
#define TABLEVIEWEXAMPLE_H

#include <QWidget>

/** @brief QTableView 练习页：模型提供通道数据，代理模型按通道名筛选并排序。 */
class TableViewExample : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief 初始化QTableView示例及信号槽
     * @param parent 父控件，可为空；页面和子对象遵循 Qt 父子所有权
     * @note 无返回值；在 QApplication 创建后的 GUI 线程调用，不执行硬件操作。
     */
    explicit TableViewExample(QWidget *parent = nullptr);
};

#endif
