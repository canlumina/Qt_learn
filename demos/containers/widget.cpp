#include "widget.h"

#include <QCheckBox>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include <QVBoxLayout>
#include <QWidget>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(12, 12, 12, 12);
    layout->setAlignment(Qt::AlignTop);
    auto *description = new QLabel(tr("一个整体启用或禁用的参数区域。"), this);
    description->setWordWrap(true);
    layout->addWidget(description);

    auto *enabled = new QCheckBox(tr("启用参数区域"), this);
    enabled->setChecked(true);
    auto *panel = new QWidget(this);
    auto *panelLayout = new QFormLayout(panel);
    /* 参数控件统一归属于 panel，便于整体管理启用状态和生命周期。 */
    panelLayout->addRow(tr("名称："), new QLineEdit(panel));
    auto *value = new QSpinBox(panel);
    value->setRange(0, 100);
    panelLayout->addRow(tr("目标值："), value);
    layout->addWidget(enabled);
    layout->addWidget(panel);

    /* 禁用父容器会同时禁用其子控件，但保留已输入的参数；复选框位于容器外，可再次启用。 */
    connect(enabled, &QCheckBox::toggled, panel, &QWidget::setEnabled);
}
