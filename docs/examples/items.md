# 列表、表格与树示例与完整代码

[返回学习路线](README.md)

## QListWidget

**是什么**：内部持有条目的简单列表。

**用途**：少量文件名、导航、联系人列表。

**最常用的方式**：addItem()、currentItemChanged()、takeItem()。下面的实现展示创建控件、配置初始值，再用信号槽处理变化。

**本 demo**：添加与删除条目，选中时显示文本。

**操作步骤**：添加几条，选择条目，再删除当前项。

全部示例在 GUI 线程操作控件；QObject 子对象由父对象释放。未出现显式资源释放代码时，仍应检查模型、场景、布局项和对话框的所有权。

### 头文件：`examples/items/listwidgetexample.h`

```cpp
#ifndef LISTWIDGETEXAMPLE_H
#define LISTWIDGETEXAMPLE_H

#include <QWidget>

/** @brief QListWidget 练习页：添加与删除条目，选中时显示文本。 */
class ListWidgetExample : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief 初始化QListWidget示例及信号槽
     * @param parent 父控件，可为空；页面和子对象遵循 Qt 父子所有权
     * @note 无返回值；在 QApplication 创建后的 GUI 线程调用，不执行硬件操作。
     */
    explicit ListWidgetExample(QWidget *parent = nullptr);
};

#endif
```

### 实现文件：`examples/items/listwidgetexample.cpp`

```cpp
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
```

## QTableWidget

**是什么**：直接以单元格条目保存数据的表格。

**用途**：小规模设备参数、记录表。

**最常用的方式**：setItem()、setHorizontalHeaderLabels()、cellChanged()、setSortingEnabled()。下面的实现展示创建控件、配置初始值，再用信号槽处理变化。

**本 demo**：三行模拟测量数据，允许编辑和点击表头排序。

**操作步骤**：编辑单元格，点击表头切换排序，观察修改提示。

**注意事项**：排序后行号可能改变；业务标识应存 UserRole 或数据模型中，不能依赖显示行号。

全部示例在 GUI 线程操作控件；QObject 子对象由父对象释放。未出现显式资源释放代码时，仍应检查模型、场景、布局项和对话框的所有权。

### 头文件：`examples/items/tablewidgetexample.h`

```cpp
#ifndef TABLEWIDGETEXAMPLE_H
#define TABLEWIDGETEXAMPLE_H

#include <QWidget>

/** @brief QTableWidget 练习页：三行模拟测量数据，允许编辑和点击表头排序。 */
class TableWidgetExample : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief 初始化QTableWidget示例及信号槽
     * @param parent 父控件，可为空；页面和子对象遵循 Qt 父子所有权
     * @note 无返回值；在 QApplication 创建后的 GUI 线程调用，不执行硬件操作。
     */
    explicit TableWidgetExample(QWidget *parent = nullptr);
};

#endif
```

### 实现文件：`examples/items/tablewidgetexample.cpp`

```cpp
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
```

## QTreeWidget

**是什么**：直接保存父子条目的树。

**用途**：设备层级、分类、目录结构。

**最常用的方式**：addTopLevelItem()、addChild()、itemClicked()、expandAll()。下面的实现展示创建控件、配置初始值，再用信号槽处理变化。

**本 demo**：设备、分组与通道的两级树，点击显示条目路径。

**操作步骤**：展开和折叠分组，点击不同子项。

全部示例在 GUI 线程操作控件；QObject 子对象由父对象释放。未出现显式资源释放代码时，仍应检查模型、场景、布局项和对话框的所有权。

### 头文件：`examples/items/treewidgetexample.h`

```cpp
#ifndef TREEWIDGETEXAMPLE_H
#define TREEWIDGETEXAMPLE_H

#include <QWidget>

/** @brief QTreeWidget 练习页：设备、分组与通道的两级树，点击显示条目路径。 */
class TreeWidgetExample : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief 初始化QTreeWidget示例及信号槽
     * @param parent 父控件，可为空；页面和子对象遵循 Qt 父子所有权
     * @note 无返回值；在 QApplication 创建后的 GUI 线程调用，不执行硬件操作。
     */
    explicit TreeWidgetExample(QWidget *parent = nullptr);
};

#endif
```

### 实现文件：`examples/items/treewidgetexample.cpp`

```cpp
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
```

## QListView

**是什么**：通过独立模型显示一列数据的视图。

**用途**：共享数据、多数据源、模型驱动列表。

**最常用的方式**：setModel()、QStringListModel::setStringList()、QItemSelectionModel::currentChanged()。下面的实现展示创建控件、配置初始值，再用信号槽处理变化。

**本 demo**：使用 QStringListModel 提供列表，选择时从 QModelIndex 读取数据。

**操作步骤**：选择不同条目，双击编辑一项。

**注意事项**：setModel 不转移模型所有权，本例给模型设置页面父对象。

全部示例在 GUI 线程操作控件；QObject 子对象由父对象释放。未出现显式资源释放代码时，仍应检查模型、场景、布局项和对话框的所有权。

### 头文件：`examples/items/listviewexample.h`

```cpp
#ifndef LISTVIEWEXAMPLE_H
#define LISTVIEWEXAMPLE_H

#include <QWidget>

/** @brief QListView 练习页：使用 QStringListModel 提供列表，选择时从 QModelIndex 读取数据。 */
class ListViewExample : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief 初始化QListView示例及信号槽
     * @param parent 父控件，可为空；页面和子对象遵循 Qt 父子所有权
     * @note 无返回值；在 QApplication 创建后的 GUI 线程调用，不执行硬件操作。
     */
    explicit ListViewExample(QWidget *parent = nullptr);
};

#endif
```

### 实现文件：`examples/items/listviewexample.cpp`

```cpp
#include "listviewexample.h"

#include <QItemSelectionModel>
#include <QLabel>
#include <QListView>
#include <QModelIndex>
#include <QStringListModel>
#include <QVBoxLayout>

ListViewExample::ListViewExample(QWidget *parent)
    : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(12, 12, 12, 12);
    layout->setAlignment(Qt::AlignTop);
    auto *description
        = new QLabel(tr("使用 QStringListModel 提供列表，选择时从 QModelIndex 读取数据。"), this);
    description->setWordWrap(true);
    layout->addWidget(description);
    // 所有界面操作在 GUI 线程；子控件由 Qt 的父子对象机制自动释放。
    auto *model = new QStringListModel(this);
    model->setStringList({ tr("温度采样"), tr("电压采样"), tr("数字输入") });
    auto *view = new QListView(this);
    view->setModel(model);
    auto *status = new QLabel(tr("从模型读取当前项"), this);
    status->setTextFormat(Qt::PlainText);
    layout->addWidget(view, 1);
    layout->addWidget(status);
    /** @brief 回显模型数据；@param current 当前索引；@param previous 原索引；无返回值；验证索引有效性。 */
    connect(view->selectionModel(), &QItemSelectionModel::currentChanged, this,
        [status](const QModelIndex &current, const QModelIndex &) {
            status->setText(current.isValid() ? current.data().toString() : tr("尚未选择"));
        });
}
```

## QTableView

**是什么**：通过模型展示行列数据的表格视图。

**用途**：需要筛选、排序或与其他视图共享的二维数据。

**最常用的方式**：setModel()、QStandardItemModel、QSortFilterProxyModel::setFilterFixedString()。下面的实现展示创建控件、配置初始值，再用信号槽处理变化。

**本 demo**：模型提供通道数据，代理模型按通道名筛选并排序。

**操作步骤**：输入“温度”筛选，清空恢复；点击表头排序。

**注意事项**：代理索引不等于源模型索引；回写源数据时使用 mapToSource()。

全部示例在 GUI 线程操作控件；QObject 子对象由父对象释放。未出现显式资源释放代码时，仍应检查模型、场景、布局项和对话框的所有权。

### 头文件：`examples/items/tableviewexample.h`

```cpp
#ifndef TABLEVIEWEXAMPLE_H
#define TABLEVIEWEXAMPLE_H

#include <QWidget>

/** @brief QTableView 练习页：模型提供通道数据，代理模型按通道名筛选并排序。 */
class TableViewExample : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief 初始化QTableView示例及信号槽
     * @param parent 父控件，可为空；页面和子对象遵循 Qt 父子所有权
     * @note 无返回值；在 QApplication 创建后的 GUI 线程调用，不执行硬件操作。
     */
    explicit TableViewExample(QWidget *parent = nullptr);
};

#endif
```

### 实现文件：`examples/items/tableviewexample.cpp`

```cpp
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
```

## QTreeView

**是什么**：通过模型展示层级数据的树视图。

**用途**：目录、设备拓扑、大规模树形数据。

**最常用的方式**：setModel()、QStandardItem::appendRow()、expandAll()。下面的实现展示创建控件、配置初始值，再用信号槽处理变化。

**本 demo**：用 QStandardItemModel 构建设备和通道层级。

**操作步骤**：展开分组，选择节点，观察模型索引回显。

**注意事项**：QStandardItem 由模型或父条目拥有，不要把同一个条目加入多个模型。

全部示例在 GUI 线程操作控件；QObject 子对象由父对象释放。未出现显式资源释放代码时，仍应检查模型、场景、布局项和对话框的所有权。

### 头文件：`examples/items/treeviewexample.h`

```cpp
#ifndef TREEVIEWEXAMPLE_H
#define TREEVIEWEXAMPLE_H

#include <QWidget>

/** @brief QTreeView 练习页：用 QStandardItemModel 构建设备和通道层级。 */
class TreeViewExample : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief 初始化QTreeView示例及信号槽
     * @param parent 父控件，可为空；页面和子对象遵循 Qt 父子所有权
     * @note 无返回值；在 QApplication 创建后的 GUI 线程调用，不执行硬件操作。
     */
    explicit TreeViewExample(QWidget *parent = nullptr);
};

#endif
```

### 实现文件：`examples/items/treeviewexample.cpp`

```cpp
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
```
