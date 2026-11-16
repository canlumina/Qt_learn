#include "lineedit.h"
#include <QString>

LineEdit::LineEdit(QWidget *parent)
    : QLineEdit(parent)
{
    lineEdit = new QLineEdit(this);
    lineEdit->setGeometry(280, 200, 200, 20);

    pushButton = new QPushButton(this);
    pushButton->setGeometry(500, 200, 100, 20);
    pushButton->setText("确认");

    label = new QLabel(this);
    label->setGeometry(280, 250, 400, 20);
    label->setText("您输入的文本是：");

    connect(pushButton, &QPushButton::clicked, this, &LineEdit::on_pushButton_clicked);
}

void LineEdit::on_pushButton_clicked()
{
    QString str = "您输入的文本是：" + lineEdit->text();
    label->setText(str);
    lineEdit->clear();
}