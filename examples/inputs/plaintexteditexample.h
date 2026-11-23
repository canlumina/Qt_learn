#ifndef PLAINTEXTEDITEXAMPLE_H
#define PLAINTEXTEDITEXAMPLE_H

#include <QWidget>

/** @brief QPlainTextEdit 练习页：追加模拟采样日志，可切换只读、清空并限制为 100 段。 */
class PlainTextEditExample : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief 初始化QPlainTextEdit示例及信号槽
     * @param parent 父控件，可为空；页面和子对象遵循 Qt 父子所有权
     * @note 无返回值；在 QApplication 创建后的 GUI 线程调用，不执行硬件操作。
     */
    explicit PlainTextEditExample(QWidget *parent = nullptr);
};

#endif
