#ifndef FORMLAYOUT_H
#define FORMLAYOUT_H

#include <QWidget>

class FormLayout : public QWidget
{
    Q_OBJECT
public:
    /**
     * @brief 创建表单布局练习页，显示设备名称、采样周期和备注输入项
     * @param parent 父控件，可为空；页面及子控件由 Qt 父子对象机制管理
     * @note 无返回值；须在 QApplication 创建后的 GUI 线程调用，仅编辑模拟参数，不保存或操作硬件。
     */
    FormLayout(QWidget *parent = 0);
};


#endif
