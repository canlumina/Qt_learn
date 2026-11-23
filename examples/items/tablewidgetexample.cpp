#include "tablewidgetexample.h"

#include <QHeaderView>
#include <QLabel>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QVBoxLayout>

TableWidgetExample::TableWidgetExample(QWidget *parent)
    : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(12, 12, 12, 12);
    layout->setAlignment(Qt::AlignTop);
    auto *description = new QLabel(tr("三行模拟测量数据，允许编辑和点击表头排序。"), this);
    description->setWordWrap(true);
    layout->addWidget(description);
    // 所有界面操作在 GUI 线程；子控件由 Qt 的父子对象机制自动释放。
    auto *table = new QTableWidget(3, 2, this);
    table->setHorizontalHeaderLabels({ tr("通道"), tr("测量值") });
    for (int row = 0; row < 3; ++row) {
        table->setItem(row, 0, new QTableWidgetItem(tr("通道 %1").arg(row + 1)));
        auto *value = new QTableWidgetItem;
        value->setData(Qt::DisplayRole, (row + 1) * 10);
        table->setItem(row, 1, value);
    }
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    // 填充结束再开启排序，避免初始化过程中行位置移动。
    table->setSortingEnabled(true);
    auto *status = new QLabel(tr("可编辑单元格；点击表头可排序。"), this);
    layout->addWidget(table, 1);
    layout->addWidget(status);
    /** @brief 报告修改位置；@param row 当前行号；@param column 当前列号；无返回值；不回写单元格。 */
    connect(table, &QTableWidget::cellChanged, this, [status](int row, int column) {
        status->setText(tr("已修改第 %1 行、第 %2 列").arg(row + 1).arg(column + 1));
    });
}
