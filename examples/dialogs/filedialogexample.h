#ifndef FILEDIALOGEXAMPLE_H
#define FILEDIALOGEXAMPLE_H

#include <QWidget>

/** @brief QFileDialog 练习页：选择现有文件、目录或拟保存路径，仅回显路径。 */
class FileDialogExample : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief 初始化QFileDialog示例及信号槽
     * @param parent 父控件，可为空；页面和子对象遵循 Qt 父子所有权
     * @note 无返回值；在 QApplication 创建后的 GUI 线程调用，不执行硬件操作。
     */
    explicit FileDialogExample(QWidget *parent = nullptr);
};

#endif
