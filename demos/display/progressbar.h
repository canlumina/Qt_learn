#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H

#include <QWidget>

class ProgressBar : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief 创建进度条练习页，模拟任务进度并支持忙碌模式和重新开始
     * @param parent 父控件，可为空；页面及子对象由 Qt 父子对象机制管理
     * @note 无返回值；须在 QApplication 创建后的 GUI 线程调用，仅模拟进度，不执行实际任务。
     */
    explicit ProgressBar(QWidget *parent = nullptr);

private:
    int completed = 0; // 已完成百分比，与忙碌模式的显示范围分开保存
};

#endif
