#include "mainwindowexample.h"

#include <QAction>
#include <QLabel>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>
#include <QStyle>
#include <QTime>
#include <QToolBar>
#include <QVBoxLayout>

MainWindowExample::MainWindowExample(QWidget *parent)
    : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(12, 12, 12, 12);
    layout->setAlignment(Qt::AlignTop);
    auto *description = new QLabel(tr("嵌入一个具备菜单、工具栏和状态栏的小主窗口。"), this);
    description->setWordWrap(true);
    layout->addWidget(description);
    // 所有界面操作在 GUI 线程；子控件由 Qt 的父子对象机制自动释放。
    auto *window = new QMainWindow(this);
    window->setWindowFlags(Qt::Widget);
    auto *central = new QLabel(tr("这是主窗口的中央区域"), window);
    central->setAlignment(Qt::AlignCenter);
    window->setCentralWidget(central);
    auto *menu = window->menuBar()->addMenu(tr("操作"));
    window->menuBar()->setNativeMenuBar(false);
    auto *refresh = new QAction(style()->standardIcon(QStyle::SP_BrowserReload), tr("刷新"), window);
    menu->addAction(refresh);
    window->addToolBar(tr("常用"))->addAction(refresh);
    window->statusBar()->showMessage(tr("就绪"));
    layout->addWidget(window, 1);
    /** @brief 更新中央内容和状态；无参数、无返回值；仅操作本例内嵌窗口。 */
    connect(refresh, &QAction::triggered, this, [window, central] {
        central->setText(tr("刷新于 %1").arg(QTime::currentTime().toString("HH:mm:ss")));
        window->statusBar()->showMessage(tr("刷新完成"), 2000);
    });
}
