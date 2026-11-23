#ifndef LABELEXAMPLE_H
#define LABELEXAMPLE_H

#include <QWidget>

/** @brief QLabel 练习页：同时展示可复制文字和程序生成的色块图片。 */
class LabelExample : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief 初始化QLabel示例及信号槽
     * @param parent 父控件，可为空；页面和子对象遵循 Qt 父子所有权
     * @note 无返回值；在 QApplication 创建后的 GUI 线程调用，不执行硬件操作。
     */
    explicit LabelExample(QWidget *parent = nullptr);
};

#endif
