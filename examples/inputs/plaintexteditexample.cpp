#include "plaintexteditexample.h"

#include <QCheckBox>
#include <QDateTime>
#include <QHBoxLayout>
#include <QLabel>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QVBoxLayout>

PlainTextEditExample::PlainTextEditExample(QWidget *parent)
    : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(12, 12, 12, 12);
    layout->setAlignment(Qt::AlignTop);
    auto *description = new QLabel(tr("追加模拟采样日志，可切换只读、清空并限制为 100 段。"), this);
    description->setWordWrap(true);
    layout->addWidget(description);
    // 所有界面操作在 GUI 线程；子控件由 Qt 的父子对象机制自动释放。
    auto *editor = new QPlainTextEdit(this);
    editor->setPlaceholderText(tr("可输入纯文本，或追加模拟日志"));
    editor->setMaximumBlockCount(100);
    auto *readOnly = new QCheckBox(tr("只读模式"), this);
    auto *append = new QPushButton(tr("追加日志"), this);
    auto *clear = new QPushButton(tr("清空"), this);
    auto *row = new QHBoxLayout;
    row->addWidget(readOnly);
    row->addWidget(append);
    row->addWidget(clear);
    layout->addLayout(row);
    layout->addWidget(editor, 1);
    connect(readOnly, &QCheckBox::toggled, editor, &QPlainTextEdit::setReadOnly);
    connect(clear, &QPushButton::clicked, editor, &QPlainTextEdit::clear);
    /** @brief 追加当前时间的模拟日志；无参数、无返回值；不读取硬件或文件。 */
    connect(append, &QPushButton::clicked, this, [editor] {
        editor->appendPlainText(QDateTime::currentDateTime().toString("hh:mm:ss") + tr(" 采样正常"));
    });
}
