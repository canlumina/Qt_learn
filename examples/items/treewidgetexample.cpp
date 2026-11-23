#include "treewidgetexample.h"

#include <QLabel>
#include <QString>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QVBoxLayout>

TreeWidgetExample::TreeWidgetExample(QWidget *parent)
    : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(12, 12, 12, 12);
    layout->setAlignment(Qt::AlignTop);
    auto *description = new QLabel(tr("设备、分组与通道的两级树，点击显示条目路径。"), this);
    description->setWordWrap(true);
    layout->addWidget(description);
    // 所有界面操作在 GUI 线程；子控件由 Qt 的父子对象机制自动释放。
    auto *tree = new QTreeWidget(this);
    tree->setHeaderLabels({ tr("设备结构"), tr("类型") });
    auto *device = new QTreeWidgetItem(tree, { tr("演示设备"), tr("设备") });
    new QTreeWidgetItem(device, { tr("温度通道"), tr("模拟输入") });
    new QTreeWidgetItem(device, { tr("输出通道"), tr("模拟输出") });
    tree->expandAll();
    auto *status = new QLabel(tr("点击一个节点"), this);
    status->setTextFormat(Qt::PlainText);
    layout->addWidget(tree, 1);
    layout->addWidget(status);
    /** @brief 显示节点；@param item 点击的条目；@param column 点击列；无返回值；条目由树拥有。 */
    connect(tree, &QTreeWidget::itemClicked, this, [status](QTreeWidgetItem *item, int) {
        if (!item)
            return;
        const QString prefix = item->parent() ? item->parent()->text(0) + " / " : QString();
        status->setText(prefix + item->text(0));
    });
}
