#include "mdiareaexample.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QMdiArea>
#include <QMdiSubWindow>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QVBoxLayout>

MdiAreaExample::MdiAreaExample(QWidget *parent)
    : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(12, 12, 12, 12);
    layout->setAlignment(Qt::AlignTop);
    auto *description = new QLabel(tr("新建多个临时文档窗口，提供平铺与层叠。"), this);
    description->setWordWrap(true);
    layout->addWidget(description);
    // 所有界面操作在 GUI 线程；子控件由 Qt 的父子对象机制自动释放。
    auto *area = new QMdiArea(this);
    auto *row = new QHBoxLayout;
    auto *create = new QPushButton(tr("新建文档"), this);
    auto *tile = new QPushButton(tr("平铺"), this);
    auto *cascade = new QPushButton(tr("层叠"), this);
    row->addWidget(create);
    row->addWidget(tile);
    row->addWidget(cascade);
    layout->addLayout(row);
    layout->addWidget(area, 1);
    /** @brief 创建临时子窗口；无参数、无返回值；关闭时删除窗口和文档，不访问磁盘。 */
    connect(create, &QPushButton::clicked, this, [area] {
        auto *editor = new QPlainTextEdit;
        editor->setPlainText(tr("临时文档，关闭后内容不保留。"));
        auto *subWindow = area->addSubWindow(editor);
        subWindow->setAttribute(Qt::WA_DeleteOnClose);
        subWindow->setWindowTitle(tr("临时文档"));
        subWindow->resize(260, 180);
        subWindow->show();
    });
    connect(tile, &QPushButton::clicked, area, &QMdiArea::tileSubWindows);
    connect(cascade, &QPushButton::clicked, area, &QMdiArea::cascadeSubWindows);
    create->click();
}
