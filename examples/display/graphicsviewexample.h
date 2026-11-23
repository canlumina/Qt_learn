#ifndef GRAPHICSVIEWEXAMPLE_H
#define GRAPHICSVIEWEXAMPLE_H

#include <QWidget>

/** @brief QGraphicsView 练习页：可拖动的矩形与椭圆，提供放大、缩小和复位。 */
class GraphicsViewExample : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief 初始化QGraphicsView示例及信号槽
     * @param parent 父控件，可为空；页面和子对象遵循 Qt 父子所有权
     * @note 无返回值；在 QApplication 创建后的 GUI 线程调用，不执行硬件操作。
     */
    explicit GraphicsViewExample(QWidget *parent = nullptr);
};

#endif
