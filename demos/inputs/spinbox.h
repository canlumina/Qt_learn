#ifndef SPINBOX_H
#define SPINBOX_H 

#include <QSpinBox>
#include <QWidget>

class SpinBox : public QSpinBox
{ 
public:
    Q_OBJECT
public:
    explicit SpinBox(QWidget *parent = nullptr);

private:
    QSpinBox *spinBox;

private slots:
    void onValueChanged(int value);

};

#endif
