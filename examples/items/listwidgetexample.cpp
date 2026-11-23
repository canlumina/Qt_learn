#include "listwidgetexample.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QListWidget>
#include <QListWidgetItem>
#include <QPushButton>
#include <QVBoxLayout>

ListWidgetExample::ListWidgetExample(QWidget *parent)
    : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(12, 12, 12, 12);
    layout->setAlignment(Qt::AlignTop);
    auto *description = new QLabel(tr("添加与删除条目，选中时显示文本。"), this);
    description->setWordWrap(true);
    layout->addWidget(description);
    // 所有界面操作在 GUI 线程；子控件由 Qt 的父子对象机制自动释放。
    auto *list = new QListWidget(this);
    list->addItems({ tr("温度通道"), tr("电压通道"), tr("状态通道") });
    auto *status = new QLabel(tr("尚未选中"), this);
    status->setTextFormat(Qt::PlainText);
    auto *addButton = new QPushButton(tr("追加通道"), this);
    auto *remove = new QPushButton(tr("删除选中项"), this);
    auto *row = new QHBoxLayout;
    row->addWidget(addButton);
    row->addWidget(remove);
    layout->addLayout(row);
    layout->addWidget(list, 1);
    layout->addWidget(status);
    /** @brief 追加示例条目；无参数、无返回值；条目由列表拥有。 */
    connect(addButton, &QPushButton::clicked, this, [list] { list->addItem(tr("新通道")); });
    /** @brief 删除当前条目；无参数、无返回值；takeItem 释放所有权，调用方负责 delete。 */
    connect(remove, &QPushButton::clicked, this, [list] {
        const int row = list->currentRow();
        if (row >= 0)
            delete list->takeItem(row);
    });
    /** @brief 回显当前项；@param current 新当前项，可为空；@param previous 原项；无返回值。 */
    connect(
        list, &QListWidget::currentItemChanged, this, [status](QListWidgetItem *current, QListWidgetItem *) {
            status->setText(current ? current->text() : tr("尚未选中"));
        });
}
