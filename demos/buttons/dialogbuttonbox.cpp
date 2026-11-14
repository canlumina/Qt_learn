#include "dialogbuttonbox.h"
#include <QDebug>

DialogButtonBox::DialogButtonBox(QWidget *parent)
    : QDialogButtonBox(parent)
{
    dialogButtonBox = new QDialogButtonBox(this);
    dialogButtonBox->setGeometry(300, 200, 200, 30);

    dialogButtonBox->addButton(QDialogButtonBox::Cancel);
    dialogButtonBox->button(QDialogButtonBox::Cancel)->setText(tr("取消"));

    pushButton = new QPushButton(tr("自定义"));

    /* 将自定义按钮添加到对话框 */
    dialogButtonBox->addButton(pushButton, QDialogButtonBox::ActionRole);

    /* 推荐这种写法 */
    connect(dialogButtonBox, &QDialogButtonBox::clicked, this, &DialogButtonBox::dialogButtonBoxClicked);
    /* 这是老式写法，Qt6 已弃用*/
    // connect(dialogButtonBox, SIGNAL(clicked(QAbstractButton * )), this, SLOT(dialogButtonBoxClicked(QAbstractButton *)));
}

void DialogButtonBox::dialogButtonBoxClicked(QAbstractButton *button)
{
    if (button == dialogButtonBox->button(QDialogButtonBox::Cancel)) {
        qDebug() << "点击了取消按钮";
    } else if (button == pushButton) {
        qDebug() << "点击了自定义按钮";
    }
}