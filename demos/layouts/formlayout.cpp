#include "formlayout.h"

#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include <QVBoxLayout>

FormLayout::FormLayout(QWidget *parent)
    : QWidget(parent)
{ 
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(12, 12, 12, 12);
    layout->setAlignment(Qt::AlignTop);

    auto *description = new QLabel(tr("设备名称、采样周期、备注组成一个可伸缩表单") ,this);
    description->setWordWrap(true);
    layout->addWidget(description);

    auto *form = new QFormLayout;

    /* 设置表单的行自动换行 */
    form->setRowWrapPolicy(QFormLayout::WrapAllRows);
    /* 设置表单的列自动扩展 */
    form->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);

    auto *name = new QLineEdit(this);
    auto *period = new QSpinBox(this);
    period->setRange(10, 1000);
    period->setSuffix(" ms");
    auto *note = new QLineEdit(this);
    form->addRow(tr("设备名称"), name);
    form->addRow(tr("采样周期"), period);
    form->addRow(tr("备注"), note);
    layout->addLayout(form);
}