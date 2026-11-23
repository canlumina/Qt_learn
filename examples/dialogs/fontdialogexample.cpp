#include "fontdialogexample.h"

#include <QFont>
#include <QFontDialog>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

FontDialogExample::FontDialogExample(QWidget *parent)
    : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(12, 12, 12, 12);
    layout->setAlignment(Qt::AlignTop);
    auto *description = new QLabel(tr("选择字体并应用到中英文预览。"), this);
    description->setWordWrap(true);
    layout->addWidget(description);
    // 所有界面操作在 GUI 线程；子控件由 Qt 的父子对象机制自动释放。
    auto *choose = new QPushButton(tr("选择字体"), this);
    auto *preview = new QLabel(tr("字体预览 Qt Widgets 123 中文"), this);
    preview->setWordWrap(true);
    layout->addWidget(choose);
    layout->addWidget(preview, 1);
    /** @brief 应用确认字体；无参数、无返回值；取消时不改变预览，字体由系统提供。 */
    connect(choose, &QPushButton::clicked, this, [this, preview] {
        bool ok = false;
        const QFont font = QFontDialog::getFont(
            &ok, preview->font(), this, tr("选择字体"), QFontDialog::DontUseNativeDialog);
        if (ok)
            preview->setFont(font);
    });
}
