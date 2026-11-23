#include "formlayoutexample.h"

#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include <QVBoxLayout>

FormLayoutExample::FormLayoutExample(QWidget *parent)
    : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(12, 12, 12, 12);
    layout->setAlignment(Qt::AlignTop);
    auto *description = new QLabel(tr("设备名称、采样周期、备注组成一个可伸缩表单。"), this);
    description->setWordWrap(true);
    layout->addWidget(description);
    // 所有界面操作在 GUI 线程；子控件由 Qt 的父子对象机制自动释放。
    auto *form = new QFormLayout;
    form->setRowWrapPolicy(QFormLayout::WrapLongRows);
    form->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
    auto *name = new QLineEdit(this);
    auto *period = new QSpinBox(this);
    period->setRange(10, 10000);
    period->setSuffix(tr(" ms"));
    auto *note = new QLineEdit(this);
    form->addRow(tr("设备名称："), name);
    form->addRow(tr("采样周期："), period);
    form->addRow(tr("备注："), note);
    layout->addLayout(form);
}
