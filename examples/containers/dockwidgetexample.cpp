#include "dockwidgetexample.h"

#include <QDockWidget>
#include <QLabel>
#include <QMainWindow>
#include <QPlainTextEdit>
#include <QToolButton>
#include <QVBoxLayout>

DockWidgetExample::DockWidgetExample(QWidget *parent)
    : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(12, 12, 12, 12);
    layout->setAlignment(Qt::AlignTop);
    auto *description = new QLabel(tr("嵌入一个主窗口，提供可拖动日志面板和恢复显示按钮。"), this);
    description->setWordWrap(true);
    layout->addWidget(description);
    // 所有界面操作在 GUI 线程；子控件由 Qt 的父子对象机制自动释放。
    auto *window = new QMainWindow(this);
    window->setWindowFlags(Qt::Widget);
    window->setCentralWidget(new QLabel(tr("中央编辑区域"), window));
    auto *dock = new QDockWidget(tr("日志面板"), window);
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea | Qt::BottomDockWidgetArea);
    auto *log = new QPlainTextEdit(dock);
    log->setReadOnly(true);
    log->setPlainText(tr("拖动标题栏可改变停靠位置。"));
    dock->setWidget(log);
    window->addDockWidget(Qt::BottomDockWidgetArea, dock);
    auto *show = new QToolButton(this);
    show->setDefaultAction(dock->toggleViewAction());
    layout->addWidget(show);
    layout->addWidget(window, 1);
}
