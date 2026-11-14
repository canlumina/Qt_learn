#ifndef COMBOBX_H
#define COMBOBX_H 

#include <QWidget>
#include <QComboBox>

class ComboBox : public QWidget {
public:
    Q_OBJECT
public:
    explicit ComboBox(QWidget *parent = nullptr);
private:
    QComboBox *comboBox;

private slots:
    void comboBoxIndexChanged(int index);
};

#endif
