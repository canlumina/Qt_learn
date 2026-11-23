/*
 *   文本编辑框（难度：简单），用一个 QTextEdit 来演示文本的输入，用两个
 *   QPushButton 来模拟文本编辑的全选与清除。在 QTextEdit 里也可用键盘的快捷键（如 Ctrl+A）
 *   来完成全选，复制，粘贴等操作。Qt 提供了全选，复制粘贴等这一类的函数方便用户操作，下
 *   面用简单的实例来演示
*/
#include "textedit.h"

TextEdit::TextEdit(QWidget *parent)
    : QTextEdit(parent)
{
    this->setGeometry(QRect(100, 100, 400, 300));
    textEdit = new QTextEdit(this);
    textEdit->setGeometry(QRect(10, 10, 380, 280));

    pushButtonSelectAll = new QPushButton("全选", this);
    pushButtonSelectAll->setGeometry(QRect(10, 300, 80, 30));

    pushButtonClearAll = new QPushButton("清除", this);
    pushButtonClearAll->setGeometry(QRect(100, 300, 80, 30));

    connect(pushButtonSelectAll, &QPushButton::clicked, this, &TextEdit::pushButtonSelectAllClicked);
    connect(pushButtonClearAll, &QPushButton::clicked, this, &TextEdit::pushButtonClearAllClicked);
}

void TextEdit::pushButtonSelectAllClicked()
{
    /* 设置焦点 */
    textEdit->setFocus();
    /* 判断文本编辑是否为空 */
    if (!textEdit->toPlainText().isEmpty()){
        textEdit->selectAll();
    }
}

void TextEdit::pushButtonClearAllClicked()
{
    /* 删除所有内容 */
    textEdit->clear();
}