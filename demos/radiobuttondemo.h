#ifndef RADIOBUTTONDEMO_H
#define RADIOBUTTONDEMO_H

#include <QRadioButton>
#include <QWidget>

/* QRadioButton 练习（待实现） */
class RadioButtonDemo : public QWidget
{
    Q_OBJECT

public:
    explicit RadioButtonDemo(QWidget *parent = nullptr);

private:
    /* 在这里声明 QRadioButton 对象 */
    QRadioButton *radioButton1;
    QRadioButton *radioButton2;
};

#endif // RADIOBUTTONDEMO_H
