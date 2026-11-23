#include "treeviewexample.h"

#include <QLabel>
#include <QModelIndex>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QTreeView>
#include <QVBoxLayout>

TreeViewExample::TreeViewExample(QWidget *parent)
    : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(12, 12, 12, 12);
    layout->setAlignment(Qt::AlignTop);
    auto *description = new QLabel(tr("用 QStandardItemModel 构建设备和通道层级。"), this);
    description->setWordWrap(true);
    layout->addWidget(description);
    // 所有界面操作在 GUI 线程；子控件由 Qt 的父子对象机制自动释放。
    auto *model = new QStandardItemModel(this);
    model->setHorizontalHeaderLabels({ tr("节点"), tr("说明") });
    auto *group = new QStandardItem(tr("模拟设备"));
    group->appendRow({ new QStandardItem(tr("温度")), new QStandardItem(tr("输入通道")) });
    group->appendRow({ new QStandardItem(tr("控制量")), new QStandardItem(tr("输出通道")) });
    model->appendRow({ group, new QStandardItem(tr("设备根节点")) });
    auto *view = new QTreeView(this);
    view->setModel(model);
    view->expandAll();
    auto *status = new QLabel(tr("点击树节点"), this);
    status->setTextFormat(Qt::PlainText);
    layout->addWidget(view, 1);
    layout->addWidget(status);
    /** @brief 显示模型项；@param index 被点击索引；无返回值；空索引不读取数据。 */
    connect(view, &QTreeView::clicked, this, [status](const QModelIndex &index) {
        if (index.isValid())
            status->setText(index.data().toString());
    });
}
