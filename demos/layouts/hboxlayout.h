#ifndef HBOXLAYOUT_H
#define HBOXLAYOUT_H
#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>


class HBoxLayout : public QWidget {
public:
    Q_OBJECT
public:
    /**
     * @brief 创建横向布局练习页，排列设备名称输入框、应用按钮和结果标签
     * @param parent 父控件，可为空；页面及子控件由 Qt 父子对象机制管理
     * @note 无返回值；须在 QApplication 创建后的 GUI 线程调用，仅回显输入，不保存配置。
     */
    explicit HBoxLayout(QWidget *parent = nullptr);

private:
    QHBoxLayout *layout;
    QLabel *description;
    QHBoxLayout *row;
    QLineEdit *input;
    QPushButton *apply;
    QLabel *status;
};

#endif
