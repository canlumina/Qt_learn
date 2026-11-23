#ifndef MENUEXAMPLE_H
#define MENUEXAMPLE_H

#include <QWidget>

/** @brief QMenu 练习页：文本区右键菜单，包含全选、清空和换行开关。 */
class MenuExample : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief 初始化QMenu示例及信号槽
     * @param parent 父控件，可为空；页面和子对象遵循 Qt 父子所有权
     * @note 无返回值；在 QApplication 创建后的 GUI 线程调用，不执行硬件操作。
     */
    explicit MenuExample(QWidget *parent = nullptr);
};

#endif
