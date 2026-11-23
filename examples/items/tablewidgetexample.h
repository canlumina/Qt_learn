#ifndef TABLEWIDGETEXAMPLE_H
#define TABLEWIDGETEXAMPLE_H

#include <QWidget>

/** @brief QTableWidget 练习页：三行模拟测量数据，允许编辑和点击表头排序。 */
class TableWidgetExample : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief 初始化QTableWidget示例及信号槽
     * @param parent 父控件，可为空；页面和子对象遵循 Qt 父子所有权
     * @note 无返回值；在 QApplication 创建后的 GUI 线程调用，不执行硬件操作。
     */
    explicit TableWidgetExample(QWidget *parent = nullptr);
};

#endif
