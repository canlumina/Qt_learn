#ifndef LINEEDIT_H
#define LINEEDIT_H
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>

class LineEdit : public QLineEdit
{
public:
    Q_OBJECT
public:
    explicit LineEdit(QWidget *parent = nullptr);
private:
    QLineEdit *lineEdit;
    QPushButton *pushButton;
    QLabel *label;

private slots:
    void on_pushButton_clicked();
};


#endif

