#include "frameexample.h"

#include <QFrame>
#include <QLabel>
#include <QVBoxLayout>

FrameExample::FrameExample(QWidget *parent)
    : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(12, 12, 12, 12);
    layout->setAlignment(Qt::AlignTop);
    auto *description = new QLabel(tr("上方带边框的说明区域，下方使用水平分隔线。"), this);
    description->setWordWrap(true);
    layout->addWidget(description);
    // 所有界面操作在 GUI 线程；子控件由 Qt 的父子对象机制自动释放。
    auto *panel = new QFrame(this);
    panel->setFrameShape(QFrame::StyledPanel);
    panel->setFrameShadow(QFrame::Sunken);
    auto *panelLayout = new QVBoxLayout(panel);
    panelLayout->addWidget(new QLabel(tr("这是带边框的内容容器"), panel));
    auto *line = new QFrame(this);
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);
    layout->addWidget(panel);
    layout->addWidget(line);
    layout->addWidget(new QLabel(tr("这是分隔线下方的说明"), this));
}
