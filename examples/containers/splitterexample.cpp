#include "splitterexample.h"

#include <QLabel>
#include <QListWidget>
#include <QPlainTextEdit>
#include <QSplitter>
#include <QVBoxLayout>

SplitterExample::SplitterExample(QWidget *parent)
    : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(12, 12, 12, 12);
    layout->setAlignment(Qt::AlignTop);
    auto *description = new QLabel(tr("左侧目录，右侧说明，分栏可拖动。"), this);
    description->setWordWrap(true);
    layout->addWidget(description);
    // 所有界面操作在 GUI 线程；子控件由 Qt 的父子对象机制自动释放。
    auto *splitter = new QSplitter(Qt::Horizontal, this);
    auto *list = new QListWidget(splitter);
    list->addItems({ tr("通道一"), tr("通道二"), tr("通道三") });
    auto *details = new QPlainTextEdit(splitter);
    details->setPlainText(tr("拖动中间分割线来调整比例。"));
    splitter->addWidget(list);
    splitter->addWidget(details);
    splitter->setChildrenCollapsible(false);
    splitter->setStretchFactor(1, 1);
    splitter->setSizes({ 140, 360 });
    layout->addWidget(splitter, 1);
}
