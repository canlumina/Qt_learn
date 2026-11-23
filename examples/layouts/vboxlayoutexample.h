#ifndef VBOXLAYOUTEXAMPLE_H
#define VBOXLAYOUTEXAMPLE_H

#include <QWidget>

/** @brief QVBoxLayout 练习页：标题、可伸缩编辑区、底部操作按钮纵向排列。 */
class VBoxLayoutExample : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief 初始化QVBoxLayout示例及信号槽
     * @param parent 父控件，可为空；页面和子对象遵循 Qt 父子所有权
     * @note 无返回值；在 QApplication 创建后的 GUI 线程调用，不执行硬件操作。
     */
    explicit VBoxLayoutExample(QWidget *parent = nullptr);
};

#endif
