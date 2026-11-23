#include "filedialogexample.h"

#include <QFileDialog>
#include <QLabel>
#include <QPushButton>
#include <QString>
#include <QVBoxLayout>

FileDialogExample::FileDialogExample(QWidget *parent)
    : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(12, 12, 12, 12);
    layout->setAlignment(Qt::AlignTop);
    auto *description = new QLabel(tr("选择现有文件、目录或拟保存路径，仅回显路径。"), this);
    description->setWordWrap(true);
    layout->addWidget(description);
    // 所有界面操作在 GUI 线程；子控件由 Qt 的父子对象机制自动释放。
    auto *open = new QPushButton(tr("选择文件"), this);
    auto *directory = new QPushButton(tr("选择目录"), this);
    auto *save = new QPushButton(tr("选择保存路径（不写入）"), this);
    auto *status = new QLabel(tr("尚未选择"), this);
    status->setTextFormat(Qt::PlainText);
    status->setWordWrap(true);
    layout->addWidget(open);
    layout->addWidget(directory);
    layout->addWidget(save);
    layout->addWidget(status);
    /** @brief 选择文件；无参数、无返回值；空路径表示取消；不读取文件。 */
    connect(open, &QPushButton::clicked, this, [this, status] {
        const QString path = QFileDialog::getOpenFileName(this, tr("选择文件"), QString(),
            tr("文本 (*.txt *.md);;所有文件 (*)"), nullptr, QFileDialog::DontUseNativeDialog);
        status->setText(path.isEmpty() ? tr("已取消选择") : path);
    });
    /** @brief 选择目录；无参数、无返回值；不修改目录内容。 */
    connect(directory, &QPushButton::clicked, this, [this, status] {
        const QString path = QFileDialog::getExistingDirectory(
            this, tr("选择目录"), QString(), QFileDialog::ShowDirsOnly | QFileDialog::DontUseNativeDialog);
        status->setText(path.isEmpty() ? tr("已取消选择") : path);
    });
    /** @brief 获取拟保存路径；无参数、无返回值；选择成功也不会创建或覆盖文件。 */
    connect(save, &QPushButton::clicked, this, [this, status] {
        const QString path = QFileDialog::getSaveFileName(this, tr("选择保存路径"), QString(),
            tr("文本 (*.txt)"), nullptr, QFileDialog::DontUseNativeDialog);
        status->setText(path.isEmpty() ? tr("已取消选择") : tr("仅选择，未写入：%1").arg(path));
    });
}
