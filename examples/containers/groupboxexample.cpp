#include "groupboxexample.h"

#include <QGroupBox>
#include <QLabel>
#include <QRadioButton>
#include <QVBoxLayout>

GroupBoxExample::GroupBoxExample(QWidget *parent)
    : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(12, 12, 12, 12);
    layout->setAlignment(Qt::AlignTop);
    auto *description = new QLabel(tr("两组独立的单选模式，其中高级配置可以整体关闭。"), this);
    description->setWordWrap(true);
    layout->addWidget(description);
    // 所有界面操作在 GUI 线程；子控件由 Qt 的父子对象机制自动释放。
    auto *basic = new QGroupBox(tr("采样方式"), this);
    auto *basicLayout = new QVBoxLayout(basic);
    auto *fast = new QRadioButton(tr("快速"), basic);
    auto *accurate = new QRadioButton(tr("精细"), basic);
    fast->setChecked(true);
    basicLayout->addWidget(fast);
    basicLayout->addWidget(accurate);
    auto *advanced = new QGroupBox(tr("高级配置"), this);
    advanced->setCheckable(true);
    advanced->setChecked(true);
    auto *advancedLayout = new QVBoxLayout(advanced);
    auto *autoMode = new QRadioButton(tr("自动"), advanced);
    auto *manual = new QRadioButton(tr("手动"), advanced);
    autoMode->setChecked(true);
    advancedLayout->addWidget(autoMode);
    advancedLayout->addWidget(manual);
    layout->addWidget(basic);
    layout->addWidget(advanced);
}
