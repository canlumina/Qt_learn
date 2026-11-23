#include "toolboxexample.h"

#include <QCheckBox>
#include <QLabel>
#include <QToolBox>
#include <QVBoxLayout>
#include <QWidget>

ToolBoxExample::ToolBoxExample(QWidget *parent)
    : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(12, 12, 12, 12);
    layout->setAlignment(Qt::AlignTop);
    auto *description = new QLabel(tr("常规、显示、维护三个工具页。"), this);
    description->setWordWrap(true);
    layout->addWidget(description);
    // 所有界面操作在 GUI 线程；子控件由 Qt 的父子对象机制自动释放。
    auto *box = new QToolBox(this);
    auto *general = new QWidget(box);
    auto *generalLayout = new QVBoxLayout(general);
    generalLayout->addWidget(new QCheckBox(tr("启用自动采样"), general));
    auto *display = new QWidget(box);
    auto *displayLayout = new QVBoxLayout(display);
    displayLayout->addWidget(new QCheckBox(tr("显示网格"), display));
    auto *maintenance = new QWidget(box);
    auto *maintenanceLayout = new QVBoxLayout(maintenance);
    maintenanceLayout->addWidget(new QLabel(tr("维护说明：本例没有擦除或烧录操作。"), maintenance));
    box->addItem(general, tr("常规"));
    box->addItem(display, tr("显示"));
    box->addItem(maintenance, tr("维护"));
    layout->addWidget(box, 1);
}
