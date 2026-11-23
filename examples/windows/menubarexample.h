#ifndef MENUBAREXAMPLE_H
#define MENUBAREXAMPLE_H

#include <QWidget>

/** @brief QMenuBar 练习页：操作和帮助两个菜单，触发后回显。 */
class MenuBarExample : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief 初始化QMenuBar示例及信号槽
     * @param parent 父控件，可为空；页面和子对象遵循 Qt 父子所有权
     * @note 无返回值；在 QApplication 创建后的 GUI 线程调用，不执行硬件操作。
     */
    explicit MenuBarExample(QWidget *parent = nullptr);
};

#endif
