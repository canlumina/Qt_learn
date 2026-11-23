#include "fontcomboboxexample.h"

#include <QFont>
#include <QFontComboBox>
#include <QLabel>
#include <QVBoxLayout>

FontComboBoxExample::FontComboBoxExample(QWidget *parent)
    : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(12, 12, 12, 12);
    layout->setAlignment(Qt::AlignTop);
    auto *description = new QLabel(tr("为预览文字切换字体，保留固定字号。"), this);
    description->setWordWrap(true);
    layout->addWidget(description);
    // 所有界面操作在 GUI 线程；子控件由 Qt 的父子对象机制自动释放。
    auto *fonts = new QFontComboBox(this);
    auto *preview = new QLabel(tr("字体预览 Qt Widgets 123 中文"), this);
    preview->setWordWrap(true);
    QFont initial = fonts->currentFont();
    initial.setPointSize(18);
    preview->setFont(initial);
    layout->addWidget(fonts);
    layout->addWidget(preview);
    /** @brief 更新预览字体；@param font 选定字体；无返回值；字体不含汉字时由系统回退。 */
    connect(fonts, &QFontComboBox::currentFontChanged, this, [preview](const QFont &font) {
        QFont displayFont = font;
        displayFont.setPointSize(18);
        preview->setFont(displayFont);
    });
}
