#ifndef LISTWIDGETEXAMPLE_H
#define LISTWIDGETEXAMPLE_H

#include <QWidget>

/** @brief QListWidget 练习页：添加与删除条目，选中时显示文本。 */
class ListWidgetExample : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief 初始化QListWidget示例及信号槽
     * @param parent 父控件，可为空；页面和子对象遵循 Qt 父子所有权
     * @note 无返回值；在 QApplication 创建后的 GUI 线程调用，不执行硬件操作。
     */
    explicit ListWidgetExample(QWidget *parent = nullptr);
};

#endif
