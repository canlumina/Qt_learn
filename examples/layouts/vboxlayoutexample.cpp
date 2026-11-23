#include "vboxlayoutexample.h"

#include <QLabel>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QVBoxLayout>

VBoxLayoutExample::VBoxLayoutExample(QWidget *parent)
    : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(12, 12, 12, 12);
    layout->setAlignment(Qt::AlignTop);
    auto *description = new QLabel(tr("标题、可伸缩编辑区、底部操作按钮纵向排列。"), this);
    description->setWordWrap(true);
    layout->addWidget(description);
    // 所有界面操作在 GUI 线程；子控件由 Qt 的父子对象机制自动释放。
    // 页面顶层 layout 本身就是 QVBoxLayout；stretch=1 的编辑区优先分配额外高度。
    auto *editor = new QPlainTextEdit(this);
    editor->setPlainText(tr("这里是可以伸缩的主要内容区域。"));
    layout->addWidget(new QLabel(tr("顶部说明"), this));
    layout->addWidget(editor, 1);
    layout->addWidget(new QPushButton(tr("底部按钮（仅演示布局）"), this));
}
