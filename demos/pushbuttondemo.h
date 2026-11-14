#ifndef PUSHBUTTONDEMO_H
#define PUSHBUTTONDEMO_H

#include <QPushButton>
#include <QWidget>

/* QPushButton 练习：点击两个按钮切换本页面的背景颜色 */
class PushButtonDemo : public QWidget
{
    Q_OBJECT

public:
    explicit PushButtonDemo(QWidget *parent = nullptr);

private slots:
    /* 声明对象PushButton1的槽函数 */
    void pushButton1Clicked();

    /* 声明对象PushButton2的槽函数 */
    void pushButton2Clicked();

private:
    QPushButton *pushButton1;
    QPushButton *pushButton2;
};

#endif // PUSHBUTTONDEMO_H
