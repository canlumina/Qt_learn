#ifndef TEXTBROWSEREXAMPLE_H
#define TEXTBROWSEREXAMPLE_H

#include <QWidget>

/** @brief QTextBrowser 练习页：内置帮助内容与锚点导航，不启动外部浏览器。 */
class TextBrowserExample : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief 初始化QTextBrowser示例及信号槽
     * @param parent 父控件，可为空；页面和子对象遵循 Qt 父子所有权
     * @note 无返回值；在 QApplication 创建后的 GUI 线程调用，不执行硬件操作。
     */
    explicit TextBrowserExample(QWidget *parent = nullptr);
};

#endif
