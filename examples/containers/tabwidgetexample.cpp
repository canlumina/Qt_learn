#include "tabwidgetexample.h"

#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QWidget>

TabWidgetExample::TabWidgetExample(QWidget *parent)
    : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(12, 12, 12, 12);
    layout->setAlignment(Qt::AlignTop);
    auto *description = new QLabel(tr("连接配置与采样配置两个选项卡。"), this);
    description->setWordWrap(true);
    layout->addWidget(description);
    // 所有界面操作在 GUI 线程；子控件由 Qt 的父子对象机制自动释放。
    auto *tabs = new QTabWidget(this);
    auto *connection = new QWidget(tabs);
    auto *connectionLayout = new QFormLayout(connection);
    connectionLayout->addRow(tr("设备名称："), new QLineEdit(connection));
    auto *sampling = new QWidget(tabs);
    auto *samplingLayout = new QFormLayout(sampling);
    samplingLayout->addRow(tr("采样次数："), new QSpinBox(sampling));
    tabs->addTab(connection, tr("连接"));
    tabs->addTab(sampling, tr("采样"));
    auto *status = new QLabel(tr("当前页：连接"), this);
    layout->addWidget(tabs, 1);
    layout->addWidget(status);
    /** @brief 回显标签页；@param index 当前页序号；无返回值；忽略没有当前页的情况。 */
    connect(tabs, &QTabWidget::currentChanged, this, [tabs, status](int index) {
        if (index >= 0)
            status->setText(tr("当前页：%1").arg(tabs->tabText(index)));
    });
}
