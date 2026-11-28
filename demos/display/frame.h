#ifndef _FRAME_H_
#define _FRAME_H_

#include <QWidget>

class Frame : public QWidget {
public:
    Q_OBJECT
public:
    /**
     * @brief 创建 QFrame 练习页，展示带边框的内容容器与水平分隔线
     * @param parent 父控件，可为空；页面及子控件由 Qt 父子对象机制管理
     * @note 无返回值；须在 QApplication 创建后的 GUI 线程调用，边框外观受当前样式影响。
     */
    explicit Frame(QWidget *parent = nullptr);
};

#endif
