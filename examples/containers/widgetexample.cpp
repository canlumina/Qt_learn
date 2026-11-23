#include "widgetexample.h"

#include <QCheckBox>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include <QVBoxLayout>
#include <QWidget>

WidgetExample::WidgetExample(QWidget *parent)
    : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(12, 12, 12, 12);
    layout->setAlignment(Qt::AlignTop);
    auto *description = new QLabel(tr("一个整体启用或禁用的参数区域。"), this);
    description->setWordWrap(true);
    layout->addWidget(description);
    // 所有界面操作在 GUI 线程；子控件由 Qt 的父子对象机制自动释放。
    auto *enabled = new QCheckBox(tr("启用参数区域"), this);
    enabled->setChecked(true);
    auto *panel = new QWidget(this);
    auto *panelLayout = new QFormLayout(panel);
    panelLayout->addRow(tr("名称："), new QLineEdit(panel));
    auto *value = new QSpinBox(panel);
    value->setRange(1, 100);
    panelLayout->addRow(tr("目标值："), value);
    layout->addWidget(enabled);
    layout->addWidget(panel);
    connect(enabled, &QCheckBox::toggled, panel, &QWidget::setEnabled);
}
