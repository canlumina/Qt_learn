#include "progressbar.h"
#include <QCheckBox>
#include <QLabel>
#include <QProgressBar>
#include <QPushButton>
#include <QTimer>
#include <QVBoxLayout>

ProgressBar::ProgressBar(QWidget *parent)
    : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(12, 12, 12, 12);
    layout->setAlignment(Qt::AlignTop);

    auto *description = new QLabel(tr("定时器模拟进度，可切换确定进度和忙碌模式，支持重新开始。"), this);
    description->setWordWrap(true);
    layout->addWidget(description);

    auto *progressBar = new QProgressBar(this);
    progressBar->setRange(0, 100);
    progressBar->setValue(0);

    auto *busy = new QCheckBox(tr("忙碌模式 (不显示百分比)"), this);
    auto *start = new QPushButton(tr("开始/重新开始"), this);
    auto *timer = new QTimer(this);
    timer->setInterval(80);
    layout->addWidget(progressBar);
    layout->addWidget(busy);
    layout->addWidget(start);

    /**
     * @brief 每次超时推进 2 个百分点，达到 100 后停止并恢复确定进度显示
     * @note 无参数、无返回值；在 GUI 线程执行，忙碌模式下仍记录实际模拟进度。
     */
    connect(timer, &QTimer::timeout, this, [this, progressBar, busy, timer]() {
        completed += 2;
        if (!busy->isChecked())
            progressBar->setValue(completed);
        if (completed >= 100) {
            timer->stop();
            busy->setChecked(false);
            progressBar->setValue(100);
        }
    });

    /**
     * @brief 清零模拟进度并启动或重新启动定时器
     * @note 无参数、无返回值；在 GUI 线程执行，保留当前显示模式，定时器由页面管理。
     */
    connect(start, &QPushButton::clicked, this, [this, progressBar, busy, timer]() {
        completed = 0;
        if (!busy->isChecked())
            progressBar->setValue(0);
        timer->start();
    });

    /**
     * @brief 切换忙碌和确定进度显示，退出忙碌模式时恢复已完成的百分比
     * @param enabled true 使用忙碌模式，false 显示 0～100 的确定进度
     * @note 无返回值；在 GUI 线程执行，仅改变显示方式，不暂停或重置模拟任务。
     */
    connect(busy, &QCheckBox::toggled, this, [this, progressBar](bool enabled) {
        progressBar->setRange(0, enabled ? 0 : 100);
        if (!enabled)
            progressBar->setValue(completed);
    });
}
