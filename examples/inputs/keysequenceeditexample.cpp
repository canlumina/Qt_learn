#include "keysequenceeditexample.h"

#include <QKeySequence>
#include <QKeySequenceEdit>
#include <QLabel>
#include <QPushButton>
#include <QShortcut>
#include <QVBoxLayout>

KeySequenceEditExample::KeySequenceEditExample(QWidget *parent)
    : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(12, 12, 12, 12);
    layout->setAlignment(Qt::AlignTop);
    auto *description = new QLabel(tr("录入快捷键，焦点离开录入框后按该快捷键更新计数。"), this);
    description->setWordWrap(true);
    layout->addWidget(description);
    // 所有界面操作在 GUI 线程；子控件由 Qt 的父子对象机制自动释放。
    auto *input = new QKeySequenceEdit(QKeySequence(Qt::CTRL | Qt::Key_J), this);
    auto *test = new QPushButton(tr("点这里，再按快捷键测试"), this);
    auto *status = new QLabel(tr("触发次数：0"), this);
    auto *shortcut = new QShortcut(input->keySequence(), this);
    shortcut->setContext(Qt::WidgetWithChildrenShortcut);
    shortcut->setAutoRepeat(false);
    layout->addWidget(input);
    layout->addWidget(test);
    layout->addWidget(status);
    /** @brief 更新绑定；@param key 用户录入的序列；无返回值；空序列会禁用快捷键。 */
    connect(input, &QKeySequenceEdit::keySequenceChanged, this, [shortcut](const QKeySequence &key) {
        shortcut->setKey(key);
        shortcut->setEnabled(!key.isEmpty());
    });
    /** @brief 累加触发次数；无参数、无返回值；仅在该示例获得焦点时响应。 */
    connect(shortcut, &QShortcut::activated, this,
        [this, status] { status->setText(tr("触发次数：%1").arg(++triggerCount)); });
}
