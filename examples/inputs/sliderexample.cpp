#include "sliderexample.h"

#include <QLabel>
#include <QSlider>
#include <QSpinBox>
#include <QVBoxLayout>
#include <QtGlobal>

SliderExample::SliderExample(QWidget *parent)
    : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(12, 12, 12, 12);
    layout->setAlignment(Qt::AlignTop);
    auto *description = new QLabel(tr("滑块与数值框双向同步，显示模拟亮度百分比。"), this);
    description->setWordWrap(true);
    layout->addWidget(description);
    // 所有界面操作在 GUI 线程；子控件由 Qt 的父子对象机制自动释放。
    auto *slider = new QSlider(Qt::Horizontal, this);
    auto *spin = new QSpinBox(this);
    slider->setRange(0, 100);
    spin->setRange(0, 100);
    spin->setSuffix(tr(" %"));
    slider->setValue(50);
    spin->setValue(50);
    layout->addWidget(new QLabel(tr("模拟亮度（不会修改设备亮度）"), this));
    layout->addWidget(slider);
    layout->addWidget(spin);
    // 值未变化时 setValue 不会继续发信号，因此这种双向连接不会无限递归。
    connect(slider, &QSlider::valueChanged, spin, &QSpinBox::setValue);
    connect(spin, QOverload<int>::of(&QSpinBox::valueChanged), slider, &QSlider::setValue);
}
