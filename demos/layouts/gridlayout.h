#ifndef GRIDLAYOUTEXAMPLE_H
#define GRIDLAYOUTEXAMPLE_H

#include <QWidget>

/** @brief QGridLayout 练习页：三行模拟通道输入与一个跨三列的说明。 */
class GridLayoutExample : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief 创建网格布局练习页，展示三行通道参数和跨三列的说明
     * @param parent 父控件，可为空；页面和子对象遵循 Qt 父子所有权
     * @note 无返回值；在 QApplication 创建后的 GUI 线程调用，不执行硬件操作。
     */
    explicit GridLayoutExample(QWidget *parent = nullptr);
};

#endif
