#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class Widget : public QWidget
{
    Q_OBJECT
public:
    /**
     * @brief 创建 QWidget 容器练习页，通过复选框整体启用或禁用参数区域
     * @param parent 父控件，可为空；页面及子控件由 Qt 父子对象机制管理
     * @note 无返回值；须在 QApplication 创建后的 GUI 线程调用，仅编辑模拟参数，不保存或操作硬件。
     */
    explicit Widget(QWidget *parent = nullptr);
};

#endif
