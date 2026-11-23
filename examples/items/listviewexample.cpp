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
