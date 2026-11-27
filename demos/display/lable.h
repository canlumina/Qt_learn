#ifndef LABLE_H
#define LABLE_H

#include <QWidget>

class Lable : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief 创建 QLabel 练习页，展示可复制文字和可切换颜色的图片
     * @param parent 父控件，可为空；页面及子控件由 Qt 父子对象机制管理
     * @note 无返回值；须在 QApplication 创建后的 GUI 线程调用。
     */
    explicit Lable(QWidget *parent = nullptr);
};

#endif
