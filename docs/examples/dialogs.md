# 对话框示例与完整代码

[返回学习路线](README.md)

## QMessageBox

**是什么**：标准提示、警告和确认对话框。

**用途**：错误提示、操作询问、信息反馈。

**最常用的方式**：information()、warning()、question()、StandardButton。下面的实现展示创建控件、配置初始值，再用信号槽处理变化。

**本 demo**：安全的模拟确认，默认选择否，不执行真实删除。

**操作步骤**：点击询问，分别选择是和否，观察返回结果。

**注意事项**：错误提示可改用 warning/critical；不要把未知外部内容直接当富文本显示。

全部示例在 GUI 线程操作控件；QObject 子对象由父对象释放。未出现显式资源释放代码时，仍应检查模型、场景、布局项和对话框的所有权。

### 头文件：`examples/dialogs/messageboxexample.h`

```cpp
#ifndef MESSAGEBOXEXAMPLE_H
#define MESSAGEBOXEXAMPLE_H

#include <QWidget>

/** @brief QMessageBox 练习页：安全的模拟确认，默认选择否，不执行真实删除。 */
class MessageBoxExample : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief 初始化QMessageBox示例及信号槽
     * @param parent 父控件，可为空；页面和子对象遵循 Qt 父子所有权
     * @note 无返回值；在 QApplication 创建后的 GUI 线程调用，不执行硬件操作。
     */
    explicit MessageBoxExample(QWidget *parent = nullptr);
};

#endif
```

### 实现文件：`examples/dialogs/messageboxexample.cpp`

```cpp
#include "messageboxexample.h"

#include <QLabel>
#include <QMessageBox>
#include <QPushButton>
#include <QVBoxLayout>

MessageBoxExample::MessageBoxExample(QWidget *parent)
    : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(12, 12, 12, 12);
    layout->setAlignment(Qt::AlignTop);
    auto *description = new QLabel(tr("安全的模拟确认，默认选择否，不执行真实删除。"), this);
    description->setWordWrap(true);
    layout->addWidget(description);
    // 所有界面操作在 GUI 线程；子控件由 Qt 的父子对象机制自动释放。
    auto *ask = new QPushButton(tr("模拟操作确认"), this);
    auto *status = new QLabel(tr("尚未确认"), this);
    layout->addWidget(ask);
    layout->addWidget(status);
    /** @brief 询问模拟操作；无参数、无返回值；模态对话框，默认 No，不修改文件。 */
    connect(ask, &QPushButton::clicked, this, [this, status] {
        const auto answer = QMessageBox::question(this, tr("确认"), tr("要执行这次模拟操作吗？"),
            QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
        status->setText(answer == QMessageBox::Yes ? tr("已确认模拟操作") : tr("已取消"));
    });
}
```

## QFileDialog

**是什么**：选择文件、目录或保存路径的标准对话框。

**用途**：打开文档、导入导出、指定目录。

**最常用的方式**：getOpenFileName()、getSaveFileName()、getExistingDirectory()。下面的实现展示创建控件、配置初始值，再用信号槽处理变化。

**本 demo**：选择现有文件、目录或拟保存路径，仅回显路径。

**操作步骤**：点击各按钮选择或取消；不会读取或写入所选文件。

**注意事项**：选择保存路径与实际保存是两步；真实保存还应检查权限、写入结果并考虑 QSaveFile。

全部示例在 GUI 线程操作控件；QObject 子对象由父对象释放。未出现显式资源释放代码时，仍应检查模型、场景、布局项和对话框的所有权。

### 头文件：`examples/dialogs/filedialogexample.h`

```cpp
#ifndef FILEDIALOGEXAMPLE_H
#define FILEDIALOGEXAMPLE_H

#include <QWidget>

/** @brief QFileDialog 练习页：选择现有文件、目录或拟保存路径，仅回显路径。 */
class FileDialogExample : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief 初始化QFileDialog示例及信号槽
     * @param parent 父控件，可为空；页面和子对象遵循 Qt 父子所有权
     * @note 无返回值；在 QApplication 创建后的 GUI 线程调用，不执行硬件操作。
     */
    explicit FileDialogExample(QWidget *parent = nullptr);
};

#endif
```

### 实现文件：`examples/dialogs/filedialogexample.cpp`

```cpp
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
```

## QDialog

**是什么**：用于短期交互任务的对话框基类。

**用途**：参数编辑、确认表单、登录或设置弹窗。

**最常用的方式**：exec()、accept()、reject()、QDialogButtonBox。下面的实现展示创建控件、配置初始值，再用信号槽处理变化。

**本 demo**：自定义通道名称对话框，确认后回显，取消保留原值。

**操作步骤**：打开对话框输入名称，分别试试确认、取消、Esc。

**注意事项**：模态 exec 启动嵌套事件循环；较复杂生产应用可用 open 加 finished，异步对话框不能是即将离开作用域的栈对象。

全部示例在 GUI 线程操作控件；QObject 子对象由父对象释放。未出现显式资源释放代码时，仍应检查模型、场景、布局项和对话框的所有权。

### 头文件：`examples/dialogs/dialogexample.h`

```cpp
#ifndef DIALOGEXAMPLE_H
#define DIALOGEXAMPLE_H

#include <QWidget>

/** @brief QDialog 练习页：自定义通道名称对话框，确认后回显，取消保留原值。 */
class DialogExample : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief 初始化QDialog示例及信号槽
     * @param parent 父控件，可为空；页面和子对象遵循 Qt 父子所有权
     * @note 无返回值；在 QApplication 创建后的 GUI 线程调用，不执行硬件操作。
     */
    explicit DialogExample(QWidget *parent = nullptr);
};

#endif
```

### 实现文件：`examples/dialogs/dialogexample.cpp`

```cpp
#include "dialogexample.h"

#include <QDialog>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>

DialogExample::DialogExample(QWidget *parent)
    : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(12, 12, 12, 12);
    layout->setAlignment(Qt::AlignTop);
    auto *description = new QLabel(tr("自定义通道名称对话框，确认后回显，取消保留原值。"), this);
    description->setWordWrap(true);
    layout->addWidget(description);
    // 所有界面操作在 GUI 线程；子控件由 Qt 的父子对象机制自动释放。
    auto *open = new QPushButton(tr("编辑名称"), this);
    auto *status = new QLabel(tr("通道一"), this);
    status->setTextFormat(Qt::PlainText);
    layout->addWidget(open);
    layout->addWidget(status);
    /** @brief 打开临时参数对话框；无参数、无返回值；栈对象仅在 exec 结束后销毁。 */
    connect(open, &QPushButton::clicked, this, [this, status] {
        QDialog dialog(this);
        dialog.setWindowTitle(tr("通道名称"));
        auto *form = new QFormLayout(&dialog);
        auto *input = new QLineEdit(status->text(), &dialog);
        auto *buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, &dialog);
        form->addRow(tr("名称："), input);
        form->addRow(buttons);
        connect(buttons, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
        connect(buttons, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);
        if (dialog.exec() == QDialog::Accepted)
            status->setText(input->text());
    });
}
```

## QInputDialog

**是什么**：用于获取单个文本、整数或选项的标准输入框。

**用途**：临时命名、输入数量、简单选项选择。

**最常用的方式**：getText()、getInt()、getItem()、ok 标志。下面的实现展示创建控件、配置初始值，再用信号槽处理变化。

**本 demo**：输入通道名称或采样次数，正确区分确认与取消。

**操作步骤**：尝试空名称、有效名称、取消，再输入次数。

全部示例在 GUI 线程操作控件；QObject 子对象由父对象释放。未出现显式资源释放代码时，仍应检查模型、场景、布局项和对话框的所有权。

### 头文件：`examples/dialogs/inputdialogexample.h`

```cpp
#ifndef INPUTDIALOGEXAMPLE_H
#define INPUTDIALOGEXAMPLE_H

#include <QWidget>

/** @brief QInputDialog 练习页：输入通道名称或采样次数，正确区分确认与取消。 */
class InputDialogExample : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief 初始化QInputDialog示例及信号槽
     * @param parent 父控件，可为空；页面和子对象遵循 Qt 父子所有权
     * @note 无返回值；在 QApplication 创建后的 GUI 线程调用，不执行硬件操作。
     */
    explicit InputDialogExample(QWidget *parent = nullptr);
};

#endif
```

### 实现文件：`examples/dialogs/inputdialogexample.cpp`

```cpp
#include "inputdialogexample.h"

#include <QInputDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QString>
#include <QVBoxLayout>

InputDialogExample::InputDialogExample(QWidget *parent)
    : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(12, 12, 12, 12);
    layout->setAlignment(Qt::AlignTop);
    auto *description = new QLabel(tr("输入通道名称或采样次数，正确区分确认与取消。"), this);
    description->setWordWrap(true);
    layout->addWidget(description);
    // 所有界面操作在 GUI 线程；子控件由 Qt 的父子对象机制自动释放。
    auto *text = new QPushButton(tr("输入名称"), this);
    auto *number = new QPushButton(tr("输入次数"), this);
    auto *status = new QLabel(tr("等待输入"), this);
    status->setTextFormat(Qt::PlainText);
    layout->addWidget(text);
    layout->addWidget(number);
    layout->addWidget(status);
    /** @brief 读取名称；无参数、无返回值；用 ok 区分取消与确认空字符串。 */
    connect(text, &QPushButton::clicked, this, [this, status] {
        bool ok = false;
        const QString name
            = QInputDialog::getText(this, tr("名称"), tr("通道名称："), QLineEdit::Normal, QString(), &ok);
        status->setText(ok ? tr("已确认名称：%1").arg(name) : tr("已取消"));
    });
    /** @brief 读取次数；无参数、无返回值；限制 1～1000，取消不使用返回值。 */
    connect(number, &QPushButton::clicked, this, [this, status] {
        bool ok = false;
        const int count = QInputDialog::getInt(this, tr("次数"), tr("采样次数："), 10, 1, 1000, 1, &ok);
        status->setText(ok ? tr("次数：%1").arg(count) : tr("已取消"));
    });
}
```

## QColorDialog

**是什么**：选择颜色的标准对话框。

**用途**：文字颜色、图表配色、主题设置。

**最常用的方式**：getColor()、QColor::isValid()、currentColorChanged()。下面的实现展示创建控件、配置初始值，再用信号槽处理变化。

**本 demo**：选择颜色并应用到预览标签，取消保留原色。

**操作步骤**：选不同颜色，再打开并取消，观察颜色保留。

全部示例在 GUI 线程操作控件；QObject 子对象由父对象释放。未出现显式资源释放代码时，仍应检查模型、场景、布局项和对话框的所有权。

### 头文件：`examples/dialogs/colordialogexample.h`

```cpp
#ifndef COLORDIALOGEXAMPLE_H
#define COLORDIALOGEXAMPLE_H

#include <QWidget>

/** @brief QColorDialog 练习页：选择颜色并应用到预览标签，取消保留原色。 */
class ColorDialogExample : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief 初始化QColorDialog示例及信号槽
     * @param parent 父控件，可为空；页面和子对象遵循 Qt 父子所有权
     * @note 无返回值；在 QApplication 创建后的 GUI 线程调用，不执行硬件操作。
     */
    explicit ColorDialogExample(QWidget *parent = nullptr);
};

#endif
```

### 实现文件：`examples/dialogs/colordialogexample.cpp`

```cpp
#include "colordialogexample.h"

#include <QColor>
#include <QColorDialog>
#include <QLabel>
#include <QPalette>
#include <QPushButton>
#include <QVBoxLayout>

ColorDialogExample::ColorDialogExample(QWidget *parent)
    : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(12, 12, 12, 12);
    layout->setAlignment(Qt::AlignTop);
    auto *description = new QLabel(tr("选择颜色并应用到预览标签，取消保留原色。"), this);
    description->setWordWrap(true);
    layout->addWidget(description);
    // 所有界面操作在 GUI 线程；子控件由 Qt 的父子对象机制自动释放。
    auto *choose = new QPushButton(tr("选择颜色"), this);
    auto *preview = new QLabel(tr("文字颜色预览"), this);
    preview->setAlignment(Qt::AlignCenter);
    layout->addWidget(choose);
    layout->addWidget(preview, 1);
    /** @brief 应用确认颜色；无参数、无返回值；取消产生无效 QColor，保持原调色板。 */
    connect(choose, &QPushButton::clicked, this, [this, preview] {
        const QColor color = QColorDialog::getColor(preview->palette().color(QPalette::WindowText), this,
            tr("文字颜色"), QColorDialog::DontUseNativeDialog);
        if (!color.isValid())
            return;
        QPalette palette = preview->palette();
        palette.setColor(QPalette::WindowText, color);
        preview->setPalette(palette);
    });
}
```

## QFontDialog

**是什么**：选择字体、字号和字形的标准对话框。

**用途**：文档样式、显示偏好、图表字体设置。

**最常用的方式**：getFont()、ok 标志、QWidget::setFont()。下面的实现展示创建控件、配置初始值，再用信号槽处理变化。

**本 demo**：选择字体并应用到中英文预览。

**操作步骤**：改变字体字号并确认，然后测试取消。

全部示例在 GUI 线程操作控件；QObject 子对象由父对象释放。未出现显式资源释放代码时，仍应检查模型、场景、布局项和对话框的所有权。

### 头文件：`examples/dialogs/fontdialogexample.h`

```cpp
#ifndef FONTDIALOGEXAMPLE_H
#define FONTDIALOGEXAMPLE_H

#include <QWidget>

/** @brief QFontDialog 练习页：选择字体并应用到中英文预览。 */
class FontDialogExample : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief 初始化QFontDialog示例及信号槽
     * @param parent 父控件，可为空；页面和子对象遵循 Qt 父子所有权
     * @note 无返回值；在 QApplication 创建后的 GUI 线程调用，不执行硬件操作。
     */
    explicit FontDialogExample(QWidget *parent = nullptr);
};

#endif
```

### 实现文件：`examples/dialogs/fontdialogexample.cpp`

```cpp
#include "fontdialogexample.h"

#include <QFont>
#include <QFontDialog>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

FontDialogExample::FontDialogExample(QWidget *parent)
    : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(12, 12, 12, 12);
    layout->setAlignment(Qt::AlignTop);
    auto *description = new QLabel(tr("选择字体并应用到中英文预览。"), this);
    description->setWordWrap(true);
    layout->addWidget(description);
    // 所有界面操作在 GUI 线程；子控件由 Qt 的父子对象机制自动释放。
    auto *choose = new QPushButton(tr("选择字体"), this);
    auto *preview = new QLabel(tr("字体预览 Qt Widgets 123 中文"), this);
    preview->setWordWrap(true);
    layout->addWidget(choose);
    layout->addWidget(preview, 1);
    /** @brief 应用确认字体；无参数、无返回值；取消时不改变预览，字体由系统提供。 */
    connect(choose, &QPushButton::clicked, this, [this, preview] {
        bool ok = false;
        const QFont font = QFontDialog::getFont(
            &ok, preview->font(), this, tr("选择字体"), QFontDialog::DontUseNativeDialog);
        if (ok)
            preview->setFont(font);
    });
}
```

## QProgressDialog

**是什么**：具有进度条和取消入口的任务对话框。

**用途**：加载、导入等需反馈或允许取消的任务。

**最常用的方式**：setValue()、setMinimumDuration()、canceled()、reset()。下面的实现展示创建控件、配置初始值，再用信号槽处理变化。

**本 demo**：定时器驱动的模拟任务，可取消并重新开始。

**操作步骤**：开始后点击取消，再开始并等待完成，检查主界面仍响应。

**注意事项**：真实任务取消需要通知工作线程协作退出；隐藏对话框本身不会停止后台工作。

全部示例在 GUI 线程操作控件；QObject 子对象由父对象释放。未出现显式资源释放代码时，仍应检查模型、场景、布局项和对话框的所有权。

### 头文件：`examples/dialogs/progressdialogexample.h`

```cpp
#ifndef PROGRESSDIALOGEXAMPLE_H
#define PROGRESSDIALOGEXAMPLE_H

#include <QWidget>

/** @brief QProgressDialog 练习页：定时器驱动的模拟任务，可取消并重新开始。 */
class ProgressDialogExample : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief 初始化QProgressDialog示例及信号槽
     * @param parent 父控件，可为空；页面和子对象遵循 Qt 父子所有权
     * @note 无返回值；在 QApplication 创建后的 GUI 线程调用，不执行硬件操作。
     */
    explicit ProgressDialogExample(QWidget *parent = nullptr);
};

#endif
```

### 实现文件：`examples/dialogs/progressdialogexample.cpp`

```cpp
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
```
