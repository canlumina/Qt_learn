#ifndef MAINWINDOWEXAMPLE_H
#define MAINWINDOWEXAMPLE_H

#include <QWidget>

/** @brief QMainWindow 练习页：嵌入一个具备菜单、工具栏和状态栏的小主窗口。 */
class MainWindowExample : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief 初始化QMainWindow示例及信号槽
     * @param parent 父控件，可为空；页面和子对象遵循 Qt 父子所有权
     * @note 无返回值；在 QApplication 创建后的 GUI 线程调用，不执行硬件操作。
     */
    explicit MainWindowExample(QWidget *parent = nullptr);
};

#endif
