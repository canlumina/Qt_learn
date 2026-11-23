#ifndef COLORDIALOGEXAMPLE_H
#define COLORDIALOGEXAMPLE_H

#include <QWidget>

/** @brief QColorDialog 练习页：选择颜色并应用到预览标签，取消保留原色。 */
class ColorDialogExample : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief 初始化QColorDialog示例及信号槽
     * @param parent 父控件，可为空；页面和子对象遵循 Qt 父子所有权
     * @note 无返回值；在 QApplication 创建后的 GUI 线程调用，不执行硬件操作。
     */
    explicit ColorDialogExample(QWidget *parent = nullptr);
};

#endif
