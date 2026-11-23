#include "progressbarexample.h"

#include <QCheckBox>
#include <QLabel>
#include <QProgressBar>
#include <QPushButton>
#include <QTimer>
#include <QVBoxLayout>

ProgressBarExample::ProgressBarExample(QWidget *parent)
    : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(12, 12, 12, 12);
    layout->setAlignment(Qt::AlignTop);
    auto *description = new QLabel(tr("定时器模拟进度，可切换确定进度和忙碌模式，支持重新开始。"), this);
    description->setWordWrap(true);
    layout->addWidget(description);
    // 所有界面操作在 GUI 线程；子控件由 Qt 的父子对象机制自动释放。
    auto *progress = new QProgressBar(this);
    progress->setRange(0, 100);
    progress->setValue(0);
    auto *busy = new QCheckBox(tr("忙碌模式（不显示百分比）"), this);
    auto *start = new QPushButton(tr("开始 / 重新开始"), this);
    auto *timer = new QTimer(this);
    timer->setInterval(80);
    layout->addWidget(progress);
    layout->addWidget(busy);
    layout->addWidget(start);
    /** @brief 模拟一小步进度；无参数、无返回值；不阻塞 GUI，计数达到上限停止。 */
    connect(timer, &QTimer::timeout, this, [this, progress, busy, timer] {
        completed += 2;
        if (!busy->isChecked())
            progress->setValue(completed);
        if (completed >= 100) {
            timer->stop();
            busy->setChecked(false);
            progress->setValue(100);
        }
    });
    /** @brief 重新开始；无参数、无返回值；定时器由页面管理，销毁页面自动停止。 */
    connect(start, &QPushButton::clicked, this, [this, progress, busy, timer] {
        completed = 0;
        if (!busy->isChecked())
            progress->setValue(0);
        timer->start();
    });
    /** @brief 切换进度范围；@param enabled true 表示忙碌模式；无返回值；恢复时回显实际计数。 */
    connect(busy, &QCheckBox::toggled, this, [this, progress](bool enabled) {
        progress->setRange(0, enabled ? 0 : 100);
        if (!enabled)
            progress->setValue(completed);
    });
}
