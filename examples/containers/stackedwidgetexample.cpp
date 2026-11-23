#include "stackedwidgetexample.h"

#include <QFormLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QWidget>

StackedWidgetExample::StackedWidgetExample(QWidget *parent)
    : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(12, 12, 12, 12);
    layout->setAlignment(Qt::AlignTop);
    auto *description = new QLabel(tr("导航列表切换概览与参数页面。"), this);
    description->setWordWrap(true);
    layout->addWidget(description);
    // 所有界面操作在 GUI 线程；子控件由 Qt 的父子对象机制自动释放。
    auto *row = new QHBoxLayout;
    auto *navigation = new QListWidget(this);
    navigation->addItems({ tr("概览"), tr("参数") });
    navigation->setMaximumWidth(140);
    auto *stack = new QStackedWidget(this);
    stack->addWidget(new QLabel(tr("概览页面：设备处于演示模式"), stack));
    auto *parameters = new QWidget(stack);
    auto *form = new QFormLayout(parameters);
    form->addRow(tr("名称："), new QLineEdit(parameters));
    stack->addWidget(parameters);
    row->addWidget(navigation);
    row->addWidget(stack, 1);
    layout->addLayout(row, 1);
    connect(navigation, &QListWidget::currentRowChanged, stack, &QStackedWidget::setCurrentIndex);
    navigation->setCurrentRow(0);
}
