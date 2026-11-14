#include "combobox.h"
#include <QDebug>

ComboBox::ComboBox(QWidget *parent)
    : QWidget(parent)
{ 
    comboBox = new QComboBox(this);
    comboBox->setGeometry(300, 200, 150, 30);
    
    comboBox->addItem("上海");
    comboBox->addItem("北京");
    comboBox->addItem("广州");

    connect(comboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &ComboBox::comboBoxIndexChanged);

    // connect(comboBox, &QComboBox::currentIndexChanged, this, &ComboBox::comboBoxIndexChanged);
    // connect(comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(comboBoxIndexChanged(int)));
}

void ComboBox::comboBoxIndexChanged(int index)
{
    qDebug() << "您选择的省份是:" << comboBox->itemText(index);
}