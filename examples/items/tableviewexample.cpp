#include "tableviewexample.h"

#include <QHeaderView>
#include <QLabel>
#include <QLineEdit>
#include <QSortFilterProxyModel>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QStringList>
#include <QTableView>
#include <QVBoxLayout>

TableViewExample::TableViewExample(QWidget *parent)
    : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(12, 12, 12, 12);
    layout->setAlignment(Qt::AlignTop);
    auto *description = new QLabel(tr("模型提供通道数据，代理模型按通道名筛选并排序。"), this);
    description->setWordWrap(true);
    layout->addWidget(description);
    // 所有界面操作在 GUI 线程；子控件由 Qt 的父子对象机制自动释放。
    auto *model = new QStandardItemModel(0, 2, this);
    model->setHorizontalHeaderLabels({ tr("通道"), tr("数值") });
    const QStringList names = { tr("温度一"), tr("电压一"), tr("温度二") };
    for (int row = 0; row < names.size(); ++row) {
        auto *value = new QStandardItem;
        value->setData((row + 1) * 5, Qt::DisplayRole);
        model->appendRow({ new QStandardItem(names.at(row)), value });
    }
    auto *proxy = new QSortFilterProxyModel(this);
    proxy->setSourceModel(model);
    proxy->setFilterKeyColumn(0);
    proxy->setFilterCaseSensitivity(Qt::CaseInsensitive);
    auto *filter = new QLineEdit(this);
    filter->setPlaceholderText(tr("按通道名称筛选"));
    auto *view = new QTableView(this);
    view->setModel(proxy);
    view->setSortingEnabled(true);
    view->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    layout->addWidget(filter);
    layout->addWidget(view, 1);
    connect(filter, &QLineEdit::textChanged, proxy, &QSortFilterProxyModel::setFilterFixedString);
}
