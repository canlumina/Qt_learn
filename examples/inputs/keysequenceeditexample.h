#ifndef KEYSEQUENCEEDITEXAMPLE_H
#define KEYSEQUENCEEDITEXAMPLE_H

#include <QWidget>

/** @brief QKeySequenceEdit 练习页：录入快捷键，焦点离开录入框后按该快捷键更新计数。 */
class KeySequenceEditExample : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief 初始化QKeySequenceEdit示例及信号槽
     * @param parent 父控件，可为空；页面和子对象遵循 Qt 父子所有权
     * @note 无返回值；在 QApplication 创建后的 GUI 线程调用，不执行硬件操作。
     */
    explicit KeySequenceEditExample(QWidget *parent = nullptr);

private:
    int triggerCount = 0; // 页面内的快捷键触发次数。
};

#endif
