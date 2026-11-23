#include "lcdnumberexample.h"

#include <QDoubleSpinBox>
#include <QLCDNumber>
#include <QLabel>
#include <QString>
#include <QVBoxLayout>
#include <QtGlobal>

LCDNumberExample::LCDNumberExample(QWidget *parent)
    : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(12, 12, 12, 12);
    layout->setAlignment(Qt::AlignTop);
    auto *description = new QLabel(tr("数值框调整模拟电压，LCD 回显带一位小数的读数。"), this);
    description->setWordWrap(true);
    layout->addWidget(description);
    // 所有界面操作在 GUI 线程；子控件由 Qt 的父子对象机制自动释放。
    auto *lcd = new QLCDNumber(6, this);
    lcd->setSegmentStyle(QLCDNumber::Flat);
    auto *value = new QDoubleSpinBox(this);
    value->setRange(0.0, 99.9);
    value->setDecimals(1);
    value->setSuffix(tr(" V"));
    value->setValue(12.0);
    lcd->display(QString::number(value->value(), 'f', 1));
    layout->addWidget(lcd);
    layout->addWidget(value);
    /** @brief 回显电压；@param voltage 当前模拟读数；无返回值；显示长度由 digitCount 限定。 */
    connect(value, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this,
        [lcd](double voltage) { lcd->display(QString::number(voltage, 'f', 1)); });
}
