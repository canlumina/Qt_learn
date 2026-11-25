#include "vboxlayout.h"
#include <QLabel>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QVBoxLayout>


VBoxLayout::VBoxLayout(QWidget *parent)
    : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);

    /* 设置布局边距 */
    layout->setContentsMargins(12, 12, 12, 12);
    /* 设置布局对齐方式 */
    layout->setAlignment(Qt::AlignTop);
    auto *description = new QLabel(tr("标题、可伸缩编辑区、底部操作按钮纵向排列"), this);
    /* 设置自动换行 */
    description->setWordWrap(true);
    /* 添加控件 */
    layout->addWidget(description);

    // 所有界面操作在 GUI 线程；子控件由 Qt 的父子对象机制自动释放。
    // 页面顶层 layout 本身就是 QVBoxLayout；stretch=1 的编辑区优先分配额外高度。
    auto *editor = new QPlainTextEdit(this);

    /* 设置占位符 */
    editor->setPlaceholderText(tr("请输入内容"));
    /* 添加控件 */
    layout->addWidget(new QLabel(tr("顶部说明"), this));
    /* 添加控件，占满剩余空间 */
    layout->addWidget(editor, 1);
    /* 添加控件 */
    layout->addWidget(new QPushButton(tr("确定"), this));
}
