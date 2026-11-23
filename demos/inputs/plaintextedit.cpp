/* 读取可执行文件旁的 UTF-8 文本，用 QRadioButton 切换 QPlainTextEdit 的只读状态。 */
#include "plaintextedit.h"
#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QTextStream>

PlainTextEdit::PlainTextEdit(QWidget *parent)
    : QWidget(parent)
{
    QDir dir(QCoreApplication::applicationDirPath());
    this->setGeometry(0, 0, 800, 480);
    plainTextEdit = new QPlainTextEdit(this);
    plainTextEdit->setGeometry(0, 50, 800, 430);

    radioButton = new QRadioButton(this);
    radioButton->setGeometry(650, 20, 100, 20);
    radioButton->setText("只读");
    // 单个按钮用作开关：关闭默认互斥，才能再次点击取消只读。
    radioButton->setAutoExclusive(false);

    // 本地文件不加 ':'；applicationDirPath() 指向 learn 所在目录，与启动工作目录无关。
    QFile file(dir.filePath("text.txt"));
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
        // Qt 5 默认使用系统编码；明确采用 UTF-8，与 Qt 6 的默认编码一致。
        in.setCodec("UTF-8");
#endif
        const QString text = in.readAll();
        if (in.status() == QTextStream::Ok && file.error() == QFileDevice::NoError) {
            plainTextEdit->setPlainText(text);
        } else {
            const QString message = tr("读取文件失败：%1\n原因：%2")
                                        .arg(file.fileName(), file.errorString());
            plainTextEdit->setPlaceholderText(message);
            qWarning().noquote() << message;
        }
        // QFile 是局部对象，离开构造函数时会自动关闭。
    } else {
        const QString message = tr("无法打开文件：%1\n原因：%2")
                                    .arg(file.fileName(), file.errorString());
        plainTextEdit->setPlaceholderText(message);
        qWarning().noquote() << message;
    }

    // Qt 允许槽函数少于信号的参数个数；本槽不接收 bool，而是读取按钮当前状态。
    connect(radioButton, &QRadioButton::toggled, this, &PlainTextEdit::radioButtonClicked);
}

void PlainTextEdit::radioButtonClicked()
{
    /* 检查状态 */
    plainTextEdit->setReadOnly(radioButton->isChecked());
}
