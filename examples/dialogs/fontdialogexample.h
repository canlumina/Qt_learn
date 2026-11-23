#ifndef FONTDIALOGEXAMPLE_H
#define FONTDIALOGEXAMPLE_H

#include <QWidget>

/** @brief QFontDialog 练习页：选择字体并应用到中英文预览。 */
class FontDialogExample : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief 初始化QFontDialog示例及信号槽
     * @param parent 父控件，可为空；页面和子对象遵循 Qt 父子所有权
     * @note 无返回值；在 QApplication 创建后的 GUI 线程调用，不执行硬件操作。
     */
    explicit FontDialogExample(QWidget *parent = nullptr);
};

#endif
