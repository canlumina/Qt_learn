#include "progressdialogexample.h"

#include <QLabel>
#include <QProgressDialog>
#include <QPushButton>
#include <QTimer>
#include <QVBoxLayout>

ProgressDialogExample::ProgressDialogExample(QWidget *parent)
    : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(12, 12, 12, 12);
    layout->setAlignment(Qt::AlignTop);
    auto *description = new QLabel(tr("定时器驱动的模拟任务，可取消并重新开始。"), this);
    description->setWordWrap(true);
    layout->addWidget(description);
    // 所有界面操作在 GUI 线程；子控件由 Qt 的父子对象机制自动释放。
    auto *start = new QPushButton(tr("开始模拟任务"), this);
    auto *status = new QLabel(tr("任务未开始"), this);
    auto *dialog = new QProgressDialog(tr("模拟处理，请稍候……"), tr("取消"), 0, 100, this);
    dialog->setWindowTitle(tr("任务进度"));
    dialog->setWindowModality(Qt::NonModal);
    dialog->setMinimumDuration(0);
    dialog->setAutoReset(false);
    dialog->setAutoClose(false);
    dialog->hide();
    auto *timer = new QTimer(this);
    timer->setInterval(50);
    layout->addWidget(start);
    layout->addWidget(status);
    /** @brief 开始新任务；无参数、无返回值；复用对话框，不阻塞 GUI。 */
    connect(start, &QPushButton::clicked, this, [dialog, timer, start, status] {
        dialog->reset();
        dialog->setValue(0);
        dialog->show();
        start->setEnabled(false);
        status->setText(tr("模拟任务运行中"));
        timer->start();
    });
    /** @brief 推进任务；无参数、无返回值；完成后停止定时器并隐藏对话框。 */
    connect(timer, &QTimer::timeout, this, [dialog, timer, start, status] {
        const int next = dialog->value() + 2;
        dialog->setValue(next);
        if (next >= dialog->maximum()) {
            timer->stop();
            dialog->hide();
            start->setEnabled(true);
            status->setText(tr("任务完成"));
        }
    });
    /** @brief 取消模拟任务；无参数、无返回值；停止计时，允许重新开始。 */
    connect(dialog, &QProgressDialog::canceled, this, [timer, start, status] {
        timer->stop();
        start->setEnabled(true);
        status->setText(tr("任务已取消"));
    });
}
