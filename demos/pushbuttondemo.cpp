#include "pushbuttondemo.h"

PushButtonDemo::PushButtonDemo(QWidget *parent)
    : QWidget(parent)
{
    /* 自定义的 QWidget 子类默认不绘制样式表里的背景，需要打开这个属性 */
    this->setAttribute(Qt::WA_StyledBackground, true);

    /* 实例化两个按钮 */
    pushButton1 = new QPushButton("窗口皮肤1", this);
    pushButton2 = new QPushButton("窗口皮肤2", this);

    /* 设置两个按钮的位置（坐标相对于本页面，不是整个窗口） */
    pushButton1->setGeometry(300, 200, 80, 40);
    pushButton2->setGeometry(400, 200, 80, 40);

    connect(pushButton1, SIGNAL(clicked()), this, SLOT(pushButton1Clicked()));
    connect(pushButton2, SIGNAL(clicked()), this, SLOT(pushButton2Clicked()));
}

void PushButtonDemo::pushButton1Clicked()
{
    /* 前面写上类名 PushButtonDemo 作为选择器，只改本页面的背景；
     * 不写的话，这个样式会一起传给页面里的按钮 */
    this->setStyleSheet("PushButtonDemo { background-color: rgb(238, 122, 233); }");
}

void PushButtonDemo::pushButton2Clicked()
{
    this->setStyleSheet("PushButtonDemo { background-color: rgb(255, 245, 238); }");
}
