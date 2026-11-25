#ifndef VBOXLAYOUT_H
#define VBOXLAYOUT_H

#include <QWidget>
class VBoxLayout : public QWidget
{
public:
    Q_OBJECT
public:
    /**
     * @brief 创建纵向布局练习页，依次放置说明、可伸缩编辑区和底部按钮
     * @param parent 父控件，可为空；页面和子控件由 Qt 父子对象机制管理
     * @note 无返回值；须在 QApplication 创建后的 GUI 线程调用，按钮仅演示布局。
     */
    explicit VBoxLayout(QWidget *parent = 0);

};

#endif
