#include "gridlayoutexample.h"

#include <QCheckBox>
#include <QGridLayout>
#include <QLabel>
#include <QSpinBox>
#include <QVBoxLayout>

GridLayoutExample::GridLayoutExample(QWidget *parent)
    : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(12, 12, 12, 12);
    layout->setAlignment(Qt::AlignTop);
    auto *description = new QLabel(tr("三行模拟通道输入与一个跨三列的说明。"), this);
    description->setWordWrap(true);
    layout->addWidget(description);
    // 所有界面操作在 GUI 线程；子控件由 Qt 的父子对象机制自动释放。
    auto *grid = new QGridLayout;
    grid->addWidget(new QLabel(tr("通道"), this), 0, 0);
    grid->addWidget(new QLabel(tr("目标值"), this), 0, 1);
    grid->addWidget(new QLabel(tr("启用"), this), 0, 2);
    for (int row = 1; row <= 3; ++row) {
        grid->addWidget(new QLabel(tr("通道 %1").arg(row), this), row, 0);
        auto *value = new QSpinBox(this);
        value->setRange(0, 1000);
        grid->addWidget(value, row, 1);
        grid->addWidget(new QCheckBox(this), row, 2);
    }
    grid->setColumnStretch(1, 1);
    grid->addWidget(new QLabel(tr("本说明跨越三列，不访问硬件。"), this), 4, 0, 1, 3);
    layout->addLayout(grid);
}
