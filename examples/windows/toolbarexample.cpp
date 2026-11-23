#include "toolbarexample.h"

#include <QAction>
#include <QComboBox>
#include <QLabel>
#include <QStyle>
#include <QToolBar>
#include <QVBoxLayout>

ToolBarExample::ToolBarExample(QWidget *parent)
    : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(12, 12, 12, 12);
    layout->setAlignment(Qt::AlignTop);
    auto *description = new QLabel(tr("带刷新动作和模式下拉框的工具栏。"), this);
    description->setWordWrap(true);
    layout->addWidget(description);
    // 所有界面操作在 GUI 线程；子控件由 Qt 的父子对象机制自动释放。
    auto *bar = new QToolBar(tr("演示工具栏"), this);
    bar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    auto *refresh = bar->addAction(style()->standardIcon(QStyle::SP_BrowserReload), tr("刷新"));
    bar->addSeparator();
    auto *mode = new QComboBox(bar);
    mode->addItems({ tr("实时"), tr("手动") });
    bar->addWidget(mode);
    auto *status = new QLabel(tr("等待刷新"), this);
    layout->addWidget(bar);
    layout->addWidget(status);
    /** @brief 模拟刷新；无参数、无返回值；读取模式并显示，不启动后台任务。 */
    connect(refresh, &QAction::triggered, this,
        [mode, status] { status->setText(tr("%1模式刷新完成").arg(mode->currentText())); });
}
