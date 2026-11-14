#ifndef COMMANDLINKBUTTON_H
#define COMMANDLINKBUTTON_H

#include <QCommandLinkButton>
#include <QWidget>

class CommandLinkButton : public QWidget {
public:
    Q_OBJECT
public:
    explicit CommandLinkButton(QWidget *parent = nullptr);

private:
    QCommandLinkButton *m_commandLinkButton;

private slots:
    void on_commandLinkButton_clicked();
};

#endif
