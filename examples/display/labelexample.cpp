#include "labelexample.h"

#include <QColor>
#include <QLabel>
#include <QPixmap>
#include <QPushButton>
#include <QVBoxLayout>

LabelExample::LabelExample(QWidget *parent)
    : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(12, 12, 12, 12);
    layout->setAlignment(Qt::AlignTop);
    auto *description = new QLabel(tr("同时展示可复制文字和程序生成的色块图片。"), this);
    description->setWordWrap(true);
    layout->addWidget(description);
    // 所有界面操作在 GUI 线程；子控件由 Qt 的父子对象机制自动释放。
    auto *text = new QLabel(tr("状态：设备空闲\n这段文字可以选择并复制。"), this);
    text->setTextFormat(Qt::PlainText);
    text->setWordWrap(true);
    text->setTextInteractionFlags(Qt::TextSelectableByMouse);
    auto *image = new QLabel(this);
    QPixmap pixmap(160, 80);
    pixmap.fill(QColor("#377bb5"));
    image->setPixmap(pixmap);
    image->setAlignment(Qt::AlignCenter);
    auto *change = new QPushButton(tr("切换色块"), this);
    change->setCheckable(true);
    layout->addWidget(text);
    layout->addWidget(image);
    layout->addWidget(change);
    /** @brief 更换图片；@param checked 是否选择第二种颜色；无返回值；图片按值由 Qt 管理。 */
    connect(change, &QPushButton::toggled, this, [image](bool checked) {
        QPixmap next(160, 80);
        next.fill(checked ? QColor("#c77a35") : QColor("#377bb5"));
        image->setPixmap(next);
    });
}
