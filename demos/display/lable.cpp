#include "lable.h"
#include <QLabel>
#include <QColor>
#include <QPixmap>
#include <QPushButton>
#include <QVBoxLayout>

Lable::Lable(QWidget *parent)
    : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(12, 12, 12, 12);
    layout->setAlignment(Qt::AlignTop);
    auto *description = new QLabel(tr("同时展示可复制文字和程序生成的色块图片。"), this);
    description->setWordWrap(true);
    layout->addWidget(description);

    auto *text = new QLabel(tr("状态：设备空闲\n这段文字可以选择并复制。"), this);
    text->setWordWrap(true);
    text->setTextFormat(Qt::PlainText);
    /* 允许选择并复制 */
    text->setTextInteractionFlags(Qt::TextSelectableByMouse);
    auto *image = new QLabel(this);
    /* 程序生成图片，无需额外图片文件；QLabel 持有设置后的图片。 */
    QPixmap pixmap(160, 80);
    pixmap.fill(QColor("#377bb5"));
    image->setPixmap(pixmap);
    image->setAlignment(Qt::AlignCenter);

    auto *change = new QPushButton(tr("改变颜色"), this);
    change->setCheckable(true);
    layout->addWidget(text);
    layout->addWidget(image);
    layout->addWidget(change);

    /**
     * @brief 根据按钮的选中状态替换色块图片
     * @param checked true 显示橙色，false 恢复蓝色
     * @note 无返回值；在 GUI 线程执行，以页面为连接上下文，页面销毁后自动断开连接。
     */
    connect(change, &QPushButton::toggled, this, [image](bool checked) {
        QPixmap next(160, 80);
        next.fill(checked ? QColor("#c77a35") : QColor("#377bb5"));
        image->setPixmap(next);
    });
}
