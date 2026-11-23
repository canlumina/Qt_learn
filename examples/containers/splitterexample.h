#ifndef SPLITTEREXAMPLE_H
#define SPLITTEREXAMPLE_H

#include <QWidget>

/** @brief QSplitter 练习页：左侧目录，右侧说明，分栏可拖动。 */
class SplitterExample : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief 初始化QSplitter示例及信号槽
     * @param parent 父控件，可为空；页面和子对象遵循 Qt 父子所有权
     * @note 无返回值；在 QApplication 创建后的 GUI 线程调用，不执行硬件操作。
     */
    explicit SplitterExample(QWidget *parent = nullptr);
};

#endif
