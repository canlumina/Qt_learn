#include "doublespinboxexample.h"

#include <QDoubleSpinBox>
#include <QLabel>
#include <QVBoxLayout>
#include <QtGlobal>

DoubleSpinBoxExample::DoubleSpinBoxExample(QWidget *parent)
    : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(12, 12, 12, 12);
    layout->setAlignment(Qt::AlignTop);
    auto *description = new QLabel(tr("输入目标温度，实时显示取到的数值。"), this);
    description->setWordWrap(true);
    layout->addWidget(description);
    // 所有界面操作在 GUI 线程；子控件由 Qt 的父子对象机制自动释放。
    auto *input = new QDoubleSpinBox(this);
    input->setRange(-40.0, 125.0);
    input->setDecimals(1);
    input->setSingleStep(0.5);
    input->setSuffix(tr(" °C"));
    input->setValue(25.0);
    auto *status = new QLabel(tr("目标温度：25.0 °C"), this);
    layout->addWidget(input);
    layout->addWidget(status);
    /** @brief 回显温度；@param value 不含单位后缀的浮点值；无返回值；仅更新 GUI。 */
    connect(input, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this,
        [status](double value) { status->setText(tr("目标温度：%1 °C").arg(value, 0, 'f', 1)); });
}
