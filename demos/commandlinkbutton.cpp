#include "commandlinkbutton.h"
#include <QDesktopServices>
#include <QUrl>
CommandLinkButton::CommandLinkButton(QWidget *parent)
    : QWidget(parent)
{
    m_commandLinkButton = new QCommandLinkButton("打开/home 目录", "点击此将调用系统的窗口打开/home 目录",this);

    m_commandLinkButton->setGeometry(300, 200, 250, 60);

    connect(m_commandLinkButton, &QCommandLinkButton::clicked, this, &CommandLinkButton::on_commandLinkButton_clicked);
}

void CommandLinkButton::on_commandLinkButton_clicked()
{
    // 调用系统的窗口打开/home 目录
    QDesktopServices::openUrl(QUrl::fromLocalFile("/home"));
}