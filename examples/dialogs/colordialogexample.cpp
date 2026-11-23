#include "colordialogexample.h"

#include <QColor>
#include <QColorDialog>
#include <QLabel>
#include <QPalette>
#include <QPushButton>
#include <QVBoxLayout>

ColorDialogExample::ColorDialogExample(QWidget *parent)
    : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(12, 12, 12, 12);
    layout->setAlignment(Qt::AlignTop);
    auto *description = new QLabel(tr("选择颜色并应用到预览标签，取消保留原色。"), this);
    description->setWordWrap(true);
    layout->addWidget(description);
    // 所有界面操作在 GUI 线程；子控件由 Qt 的父子对象机制自动释放。
    auto *choose = new QPushButton(tr("选择颜色"), this);
    auto *preview = new QLabel(tr("文字颜色预览"), this);
    preview->setAlignment(Qt::AlignCenter);
    layout->addWidget(choose);
    layout->addWidget(preview, 1);
    /** @brief 应用确认颜色；无参数、无返回值；取消产生无效 QColor，保持原调色板。 */
    connect(choose, &QPushButton::clicked, this, [this, preview] {
        const QColor color = QColorDialog::getColor(preview->palette().color(QPalette::WindowText), this,
            tr("文字颜色"), QColorDialog::DontUseNativeDialog);
        if (!color.isValid())
            return;
        QPalette palette = preview->palette();
        palette.setColor(QPalette::WindowText, color);
        preview->setPalette(palette);
    });
}
