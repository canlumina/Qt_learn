#include "dialexample.h"

#include <QDial>
#include <QLabel>
#include <QVBoxLayout>

DialExample::DialExample(QWidget *parent)
    : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(12, 12, 12, 12);
    layout->setAlignment(Qt::AlignTop);
    auto *description = new QLabel(tr("用旋钮调整模拟输出百分比。"), this);
    description->setWordWrap(true);
    layout->addWidget(description);
    // 所有界面操作在 GUI 线程；子控件由 Qt 的父子对象机制自动释放。
    auto *dial = new QDial(this);
    dial->setRange(0, 100);
    dial->setNotchesVisible(true);
    dial->setWrapping(false);
    dial->setValue(30);
    auto *status = new QLabel(tr("模拟输出：30 %"), this);
    layout->addWidget(dial, 1);
    layout->addWidget(status);
    /** @brief 显示旋钮数值；@param value 0～100 的值；无返回值；不控制真实外设。 */
    connect(dial, &QDial::valueChanged, this,
        [status](int value) { status->setText(tr("模拟输出：%1 %").arg(value)); });
}
