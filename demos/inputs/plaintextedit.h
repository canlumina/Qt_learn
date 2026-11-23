#ifndef PLAINTEXTEDIT_H
#define PLAINTEXTEDIT_H
#include <QWidget>
#include <QPlainTextEdit>
#include <QRadioButton>

class PlainTextEdit : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief 创建纯文本页面，读取可执行文件同目录的 text.txt，并连接只读开关
     * @param parent 父控件，可为空；子控件由 Qt 父子对象机制释放
     * @note 无返回值；须在 QApplication 创建后的 GUI 线程调用。按 UTF-8 读取，编辑不写回文件。
     */
    explicit PlainTextEdit(QWidget *parent = nullptr);
private:
    QRadioButton *radioButton;
    QPlainTextEdit *plainTextEdit;

private slots:
    /**
     * @brief 根据单选按钮当前状态切换编辑区的只读属性
     * @note 无参数、无返回值；在 GUI 线程调用，不修改磁盘文件。
     */
    void radioButtonClicked();

};

#endif
