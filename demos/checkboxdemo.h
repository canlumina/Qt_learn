#ifndef CHECKBOXDEMO_H
#define CHECKBOXDEMO_H

#include <QCheckBox>
#include <QWidget>

/* CheckBox 练习 */
class CheckBoxDemo : public QWidget {
public:
    Q_OBJECT
public:
    explicit CheckBoxDemo(QWidget *parent = nullptr);

private:
    /* 声明CheckBox对象 */
    QCheckBox *checkBox;

private slots:
    /* CheckBox的槽函数，并带参数，这个参数接受信号的参数*/
    void checkBoxStateClicked(int state);


};

#endif
