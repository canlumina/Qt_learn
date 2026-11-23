#ifndef MDIAREAEXAMPLE_H
#define MDIAREAEXAMPLE_H

#include <QWidget>

/** @brief QMdiArea 练习页：新建多个临时文档窗口，提供平铺与层叠。 */
class MdiAreaExample : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief 初始化QMdiArea示例及信号槽
     * @param parent 父控件，可为空；页面和子对象遵循 Qt 父子所有权
     * @note 无返回值；在 QApplication 创建后的 GUI 线程调用，不执行硬件操作。
     */
    explicit MdiAreaExample(QWidget *parent = nullptr);
};

#endif
