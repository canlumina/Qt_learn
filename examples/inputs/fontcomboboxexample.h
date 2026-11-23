#ifndef FONTCOMBOBOXEXAMPLE_H
#define FONTCOMBOBOXEXAMPLE_H

#include <QWidget>

/** @brief QFontComboBox 练习页：为预览文字切换字体，保留固定字号。 */
class FontComboBoxExample : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief 初始化QFontComboBox示例及信号槽
     * @param parent 父控件，可为空；页面和子对象遵循 Qt 父子所有权
     * @note 无返回值；在 QApplication 创建后的 GUI 线程调用，不执行硬件操作。
     */
    explicit FontComboBoxExample(QWidget *parent = nullptr);
};

#endif
