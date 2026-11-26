#include "gridlayout.h"

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

    // 第 0 行是表头，数据行从第 1 行开始，共生成 3 个模拟通道。
    /* 循环填充通道行:每行 = 通道名标签 + 目标值 SpinBox + 启用 CheckBox */
    for (int row = 1; row <= 3; ++row) {
        /* 第 0 列:通道名称,行号即 row */
        grid->addWidget(new QLabel(tr("通道 %1").arg(row), this), row, 0);
        auto *value = new QSpinBox(this);
        /* 目标值取值范围 0 ~ 1000 */
        value->setRange(0, 1000);
        /* 第 1 列:目标值输入控件 */
        grid->addWidget(value, row, 1);
        /* 第 2 列:该通道是否启用 */
        grid->addWidget(new QCheckBox(this), row, 2);
    }

    grid->setColumnStretch(1, 1);
    grid->addWidget(new QLabel(tr("本说明跨越三列，不访问硬件。"), this), 4, 0, 1, 3);
    layout->addLayout(grid);
}
