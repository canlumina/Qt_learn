#ifndef _GRAPHICSVIEW_H_
#define _GRAPHICSVIEW_H_

#include <QWidget>

class GraphicsView : public QWidget
{
    Q_OBJECT
public:
    /**
     * @brief 创建图形视图练习页，展示可拖动图形及缩放、复位按钮
     * @param parent 父控件，可为空；页面及子对象由 Qt 父子对象机制管理
     * @note 无返回值；须在 QApplication 创建后的 GUI 线程调用，图形项由场景管理。
     */
    explicit GraphicsView(QWidget *parent = nullptr);
};

#endif
