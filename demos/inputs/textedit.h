#ifndef TEXTEDIT_H
#define TEXTEDIT_H

#include <QTextEdit>
#include <QPushButton>

class TextEdit : public QTextEdit
{
    Q_OBJECT
public:
    explicit TextEdit(QWidget *parent = 0);

private:
    QPushButton *pushButtonSelectAll;
    QPushButton *pushButtonClearAll;
    QTextEdit *textEdit;

private slots:
    void pushButtonSelectAllClicked();
    void pushButtonClearAllClicked();
};

#endif
