#ifndef DIALOGBUTTONBOX_H
#define DIALOGBUTTONBOX_H

#include <QDialogButtonBox>
#include <QPushButton>
#include <QWidget>

class DialogButtonBox : public QDialogButtonBox {
public:
    Q_OBJECT
public:
    explicit DialogButtonBox(QWidget *parent = nullptr);

private:
    QPushButton *pushButton;
    QDialogButtonBox *dialogButtonBox;

private slots:
    /* 带QAbstractButton参数的 clicked 信号槽函数，用于判断是那个按钮被点击*/
    void dialogButtonBoxClicked(QAbstractButton *button);
};

#endif
