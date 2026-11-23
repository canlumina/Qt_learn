#include "menuexample.h"

#include <QAction>
#include <QLabel>
#include <QMenu>
#include <QPlainTextEdit>
#include <QPoint>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

MenuExample::MenuExample(QWidget *parent)
    : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(12, 12, 12, 12);
    layout->setAlignment(Qt::AlignTop);
    auto *description = new QLabel(tr("文本区右键菜单，包含全选、清空和换行开关。"), this);
    description->setWordWrap(true);
    layout->addWidget(description);
    // 所有界面操作在 GUI 线程；子控件由 Qt 的父子对象机制自动释放。
    auto *editor = new QPlainTextEdit(this);
    editor->setPlainText(tr("这是右键菜单示例。输入一行长文本以观察换行开关。"));
    auto *menu = new QMenu(editor);
    auto *select = menu->addAction(tr("全选"));
    auto *clear = menu->addAction(tr("清空临时文本"));
    menu->addSeparator();
    auto *wrap = menu->addAction(tr("自动换行"));
    wrap->setCheckable(true);
    wrap->setChecked(true);
    auto *show = new QPushButton(tr("显示菜单"), this);
    editor->setContextMenuPolicy(Qt::CustomContextMenu);
    layout->addWidget(show);
    layout->addWidget(editor, 1);
    connect(select, &QAction::triggered, editor, &QPlainTextEdit::selectAll);
    connect(clear, &QAction::triggered, editor, &QPlainTextEdit::clear);
    /** @brief 显示右键菜单；@param position 视口局部坐标；无返回值；popup 非阻塞。 */
    connect(editor, &QWidget::customContextMenuRequested, this,
        [editor, menu](const QPoint &position) { menu->popup(editor->viewport()->mapToGlobal(position)); });
    /** @brief 提供触屏可用的菜单入口；无参数、无返回值；位置从按钮映射到全局。 */
    connect(show, &QPushButton::clicked, this,
        [show, menu] { menu->popup(show->mapToGlobal(QPoint(0, show->height()))); });
    /** @brief 设置换行模式；@param enabled 是否自动换行；无返回值；不修改文本。 */
    connect(wrap, &QAction::toggled, this, [editor](bool enabled) {
        editor->setLineWrapMode(enabled ? QPlainTextEdit::WidgetWidth : QPlainTextEdit::NoWrap);
    });
}
