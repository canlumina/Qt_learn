#include "checkboxdemo.h"
#include <QFile>

CheckBoxDemo::CheckBoxDemo(QWidget *parent)
    : QWidget(parent)
{
    /* 自定义的 QWidget 子类默认不绘制样式表里的背景，需要打开这个属性 */
    this->setAttribute(Qt::WA_StyledBackground, true);

    /* 实例化对象*/
    checkBox = new QCheckBox(this);
    checkBox->setGeometry(350, 200, 250, 50);

    /* 初始化三态复选框的状态为Checked */
    checkBox->setCheckState(Qt::Checked);

    /* 设置初始化显示的文本 */
    checkBox->setText("初始化显示的文本");

    /* 必须先开启三态模式，否则只有两种状态*/
    checkBox->setTristate(true);

    connect(checkBox, SIGNAL(stateChanged(int)), this, SLOT(checkBoxStateClicked(int)));

    QFile file(":/style.qss");
    if (file.open(QFile::ReadOnly)) {
        QString styleSheet = QLatin1String(file.readAll());
        this->setStyleSheet(styleSheet);
        file.close();
    }
}

void CheckBoxDemo::checkBoxStateClicked(int state)
{
    /* 判断状态，设置文本 */
    switch (state) {
    case Qt::Checked:
        checkBox->setText("Checked");
        break;
    case Qt::Unchecked:
        checkBox->setText("Unchecked");
        break;
    case Qt::PartiallyChecked:
        checkBox->setText("PartiallyChecked");
        break;
    default:
        break;
    }

}
