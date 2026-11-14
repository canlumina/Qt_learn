#include "radiobuttondemo.h"
#include <QFile>

RadioButtonDemo::RadioButtonDemo(QWidget *parent)
    : QWidget(parent)
{
    /* 在这里写 QRadioButton 的练习代码 */

    /* 自定义的 QWidget 子类默认不绘制样式表里的背景，需要打开这个属性 */
    this->setAttribute(Qt::WA_StyledBackground, true);
    /* 实例化两个按钮 */
    radioButton1 = new QRadioButton(this);
    radioButton2 = new QRadioButton(this);

    radioButton1->setGeometry(300, 200, 100, 50);
    radioButton2->setGeometry(400, 200, 100, 50);

    radioButton1->setText("开关一");
    radioButton2->setText("开关二");

    radioButton1->setChecked(true);
    radioButton2->setChecked(false);


    QFile file(":/style.qss");
    if(file.exists()){
        file.open(QFile::ReadOnly);
        QString styleSheet = QLatin1String(file.readAll());
        // 设置样式表
        this->setStyleSheet(styleSheet);
        // this->setStyleSheet("RadioButtonDemo{background-color: rgb(229, 150, 227);}" + styleSheet);
        file.close();
    }
}
