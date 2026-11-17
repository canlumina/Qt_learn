#include "spinbox.h"

SpinBox::SpinBox(QWidget *parent)
    : QSpinBox(parent)
{
    /* 自定义的 QWidget 子类默认不绘制样式表里的背景，需要打开这个属性 */
    this->setAttribute(Qt::WA_StyledBackground, true);
    this->setStyleSheet("background-color: #f091ed;");

    spinBox = new QSpinBox(this);
    spinBox->setGeometry(QRect(10, 10, 100, 30));

    spinBox->setSingleStep(10);
    spinBox->setRange(0, 100);
    spinBox->setValue(100);
    spinBox->setSuffix("%s不透明度");

    connect(spinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &SpinBox::onValueChanged);
}

void SpinBox::onValueChanged(int value)
{
    /* 转换为 double 数据类型 */
    double dobleValue = (double)value / 100.0;
    /* 设置透明度, 0.0 - 1.0。
     * setWindowOpacity() 只对顶层窗口有效，本页面是嵌在主窗口里的子控件，
     * 直接对 this 调用不起作用，所以先用 window() 取得所在的主窗口 */
    this->window()->setWindowOpacity(dobleValue);
}
