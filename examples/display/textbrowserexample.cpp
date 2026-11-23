#include "textbrowserexample.h"

#include <QLabel>
#include <QTextBrowser>
#include <QUrl>
#include <QVBoxLayout>

TextBrowserExample::TextBrowserExample(QWidget *parent)
    : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(12, 12, 12, 12);
    layout->setAlignment(Qt::AlignTop);
    auto *description = new QLabel(tr("内置帮助内容与锚点导航，不启动外部浏览器。"), this);
    description->setWordWrap(true);
    layout->addWidget(description);
    // 所有界面操作在 GUI 线程；子控件由 Qt 的父子对象机制自动释放。
    auto *browser = new QTextBrowser(this);
    auto *status = new QLabel(tr("尚未点击链接"), this);
    status->setTextFormat(Qt::PlainText);
    browser->setOpenExternalLinks(false);
    browser->setOpenLinks(false);
    browser->setHtml(tr("<h2>帮助页</h2><p><a href='#notes'>跳到注意事项</a></p>"
                        "<p>QTextBrowser 用于只读文档，不是完整网页浏览器。</p>"
                        "<p>这里可以显示标题、列表和文本链接。</p>"
                        "<h3 id='notes'>注意事项</h3><p>只处理本页锚点，不访问网络。</p>"));
    layout->addWidget(browser, 1);
    layout->addWidget(status);
    /** @brief 处理本页锚点；@param url 用户点击的链接；无返回值；其他协议不执行。 */
    connect(browser, &QTextBrowser::anchorClicked, this, [browser, status](const QUrl &url) {
        status->setText(tr("点击链接：%1").arg(url.toString()));
        if (url.scheme().isEmpty() && url.path().isEmpty())
            browser->scrollToAnchor(url.fragment());
    });
}
