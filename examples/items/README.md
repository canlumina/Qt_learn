# 列表、表格与树参考示例

本目录包含 6 个示例，每个类各有一对 `.h/.cpp`，由 `widget_examples` 统一运行。

[用途、常用方式、操作步骤与完整代码](../../docs/examples/items.md) · [返回示例目录](../README.md)

| 控件 | 头文件 | 实现文件 | 示例功能 |
| --- | --- | --- | --- |
| QListWidget | [listwidgetexample.h](listwidgetexample.h) | [listwidgetexample.cpp](listwidgetexample.cpp) | 添加与删除条目，选中时显示文本。 |
| QTableWidget | [tablewidgetexample.h](tablewidgetexample.h) | [tablewidgetexample.cpp](tablewidgetexample.cpp) | 三行模拟测量数据，允许编辑和点击表头排序。 |
| QTreeWidget | [treewidgetexample.h](treewidgetexample.h) | [treewidgetexample.cpp](treewidgetexample.cpp) | 设备、分组与通道的两级树，点击显示条目路径。 |
| QListView | [listviewexample.h](listviewexample.h) | [listviewexample.cpp](listviewexample.cpp) | 使用 QStringListModel 提供列表，选择时从 QModelIndex 读取数据。 |
| QTableView | [tableviewexample.h](tableviewexample.h) | [tableviewexample.cpp](tableviewexample.cpp) | 模型提供通道数据，代理模型按通道名筛选并排序。 |
| QTreeView | [treeviewexample.h](treeviewexample.h) | [treeviewexample.cpp](treeviewexample.cpp) | 用 QStandardItemModel 构建设备和通道层级。 |
