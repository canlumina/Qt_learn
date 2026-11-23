#include "textedit.h"

#include <QAction>
#include <QColor>
#include <QColorDialog>
#include <QComboBox>
#include <QFont>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSignalBlocker>
#include <QSpinBox>
#include <QTextCharFormat>
#include <QTextCursor>
#include <QTextDocument>
#include <QTextEdit>
#include <QToolBar>
#include <QVariant>
#include <QVector>
#include <QVBoxLayout>

TextEdit::TextEdit(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(10, 10, 10, 10);
    layout->setSpacing(6);
    QLabel *hint = new QLabel(tr("选中文字后修改格式；未选中时，格式用于后续输入。"), this);
    hint->setWordWrap(true);
    layout->addWidget(hint);

    textEdit = new QTextEdit(this);
    textEdit->setAcceptRichText(true);
    textEdit->setUndoRedoEnabled(true);
    textEdit->setPlaceholderText(tr("输入多行文本，或粘贴带格式的内容……"));

    /* 第一排是文档操作；空间不足时动作自动进入工具栏扩展菜单。 */
    QToolBar *editBar = new QToolBar(tr("编辑操作"), this);
    QAction *undoAction = editBar->addAction(tr("撤销"));
    QAction *redoAction = editBar->addAction(tr("重做"));
    editBar->addSeparator();
    QAction *cutAction = editBar->addAction(tr("剪切"));
    QAction *copyAction = editBar->addAction(tr("复制"));
    QAction *pasteAction = editBar->addAction(tr("粘贴"));
    editBar->addSeparator();
    QAction *selectAllAction = editBar->addAction(tr("全选"));
    QAction *clearAction = editBar->addAction(tr("清空"));
    clearAction->setToolTip(tr("清空全文，可通过撤销恢复"));
    undoAction->setEnabled(false);
    redoAction->setEnabled(false);
    cutAction->setEnabled(false);
    copyAction->setEnabled(false);
    layout->addWidget(editBar);

    /* 第二排区分字符格式与段落格式，两者使用不同的 API。 */
    QToolBar *formatBar = new QToolBar(tr("文本格式"), this);
    boldAction = formatBar->addAction(tr("加粗"));
    italicAction = formatBar->addAction(tr("斜体"));
    underlineAction = formatBar->addAction(tr("下划线"));
    boldAction->setCheckable(true);
    italicAction->setCheckable(true);
    underlineAction->setCheckable(true);
    formatBar->addSeparator();
    formatBar->addWidget(new QLabel(tr("字号 "), this));
    fontSizeBox = new QSpinBox(this);
    fontSizeBox->setRange(8, 48);
    fontSizeBox->setSuffix(tr(" pt"));
    fontSizeBox->setValue(12);
    fontSizeBox->setKeyboardTracking(false);
    formatBar->addWidget(fontSizeBox);
    QAction *colorAction = formatBar->addAction(tr("文字颜色"));
    alignmentBox = new QComboBox(this);
    alignmentBox->addItem(tr("左对齐"), static_cast<int>(Qt::AlignLeft));
    alignmentBox->addItem(tr("居中"), static_cast<int>(Qt::AlignHCenter));
    alignmentBox->addItem(tr("右对齐"), static_cast<int>(Qt::AlignRight));
    alignmentBox->addItem(tr("两端对齐"), static_cast<int>(Qt::AlignJustify));
    formatBar->addWidget(alignmentBox);
    layout->addWidget(formatBar);
    layout->addWidget(textEdit, 1);

    QHBoxLayout *findLayout = new QHBoxLayout;
    findEdit = new QLineEdit(this);
    findEdit->setPlaceholderText(tr("输入查找内容，按回车查找下一处"));
    findEdit->setClearButtonEnabled(true);
    QPushButton *findButton = new QPushButton(tr("查找下一处"), this);
    findLayout->addWidget(findEdit, 1);
    findLayout->addWidget(findButton);
    layout->addLayout(findLayout);
    findStatusLabel = new QLabel(tr("查找不区分大小写，到末尾后从头继续。"), this);
    findStatusLabel->setWordWrap(true);
    /* 状态包含用户输入，按纯文本显示，避免将关键字解释成 HTML。 */
    findStatusLabel->setTextFormat(Qt::PlainText);
    layout->addWidget(findStatusLabel);
    statisticsLabel = new QLabel(this);
    statisticsLabel->setWordWrap(true);
    layout->addWidget(statisticsLabel);

    connect(undoAction, &QAction::triggered, textEdit, &QTextEdit::undo);
    connect(redoAction, &QAction::triggered, textEdit, &QTextEdit::redo);
    connect(cutAction, &QAction::triggered, textEdit, &QTextEdit::cut);
    connect(copyAction, &QAction::triggered, textEdit, &QTextEdit::copy);
    connect(pasteAction, &QAction::triggered, textEdit, &QTextEdit::paste);
    connect(selectAllAction, &QAction::triggered, this, &TextEdit::selectAllText);
    connect(clearAction, &QAction::triggered, this, &TextEdit::clearText);
    connect(textEdit, &QTextEdit::undoAvailable, undoAction, &QAction::setEnabled);
    connect(textEdit, &QTextEdit::redoAvailable, redoAction, &QAction::setEnabled);
    connect(textEdit, &QTextEdit::copyAvailable, cutAction, &QAction::setEnabled);
    connect(textEdit, &QTextEdit::copyAvailable, copyAction, &QAction::setEnabled);
    connect(boldAction, &QAction::toggled, this, &TextEdit::setBold);
    connect(italicAction, &QAction::toggled, this, &TextEdit::setItalic);
    connect(underlineAction, &QAction::toggled, this, &TextEdit::setUnderline);
    /* Qt 5 的信号有重载，显式选择 int 版本以兼容两代 Qt。 */
    connect(fontSizeBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &TextEdit::setFontSize);
    connect(alignmentBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &TextEdit::setParagraphAlignment);
    connect(colorAction, &QAction::triggered, this, &TextEdit::chooseTextColor);
    connect(textEdit, &QTextEdit::currentCharFormatChanged, this, &TextEdit::syncFormatControls);
    connect(textEdit, &QTextEdit::cursorPositionChanged, this, &TextEdit::syncFormatControls);
    connect(textEdit, &QTextEdit::textChanged, this, &TextEdit::updateStatistics);
    connect(textEdit, &QTextEdit::selectionChanged, this, &TextEdit::updateStatistics);
    connect(findButton, &QPushButton::clicked, this, &TextEdit::findNext);
    connect(findEdit, &QLineEdit::returnPressed, this, &TextEdit::findNext);

    /* setHtml() 会重置撤销历史，只用于初始化，不用于每次刷新文本。 */
    textEdit->document()->setDefaultFont(QFont(textEdit->font().family(), 12));
    textEdit->setHtml(tr("<p><b>QTextEdit 富文本练习</b></p>"
                         "<p>选中这段文字，试试加粗、颜色和字号。</p>"
                         "<p>这一段可以练习居中和两端对齐。格式修改后试试撤销与重做。</p>"
                         "<p>在下面输入“文字”，连续查找，观察从文末回到开头的行为。</p>"));
    QTextCursor cursor = textEdit->textCursor();
    cursor.movePosition(QTextCursor::Start);
    textEdit->setTextCursor(cursor);
    syncFormatControls();
    updateStatistics();
}

void TextEdit::mergeFormat(const QTextCharFormat &format)
{
    /* 有选区时只修改选区，无选区时设置后续输入的格式，不自动选中整词。 */
    textEdit->mergeCurrentCharFormat(format);
    textEdit->setFocus();
    syncFormatControls();
}

void TextEdit::setBold(bool enabled)
{
    QTextCharFormat format;
    format.setFontWeight(enabled ? QFont::Bold : QFont::Normal);
    mergeFormat(format);
}

void TextEdit::setItalic(bool enabled)
{
    QTextCharFormat format;
    format.setFontItalic(enabled);
    mergeFormat(format);
}

void TextEdit::setUnderline(bool enabled)
{
    QTextCharFormat format;
    format.setFontUnderline(enabled);
    mergeFormat(format);
}

void TextEdit::setFontSize(int points)
{
    if (points < 8 || points > 48) {
        return;
    }
    QTextCharFormat format;
    format.setFontPointSize(points);
    mergeFormat(format);
}

void TextEdit::chooseTextColor()
{
    const QColor currentColor = textEdit->textColor();
    /* 使用 Qt 自身的对话框，使桌面和嵌入式采用相同的练习流程。 */
    const QColor color = QColorDialog::getColor(currentColor, this, tr("选择文字颜色"),
                                               QColorDialog::DontUseNativeDialog);
    if (!color.isValid()) {
        return;
    }
    QTextCharFormat format;
    format.setForeground(color);
    mergeFormat(format);
}

void TextEdit::setParagraphAlignment(int index)
{
    if (index < 0 || index >= alignmentBox->count()) {
        return;
    }
    textEdit->setAlignment(static_cast<Qt::Alignment>(alignmentBox->itemData(index).toInt()));
    textEdit->setFocus();
    syncFormatControls();
}

void TextEdit::syncFormatControls()
{
    /* 回显引起的信号会误改文本，RAII 阻断信号并在退出作用域时自动恢复。 */
    const QSignalBlocker boldBlocker(boldAction);
    const QSignalBlocker italicBlocker(italicAction);
    const QSignalBlocker underlineBlocker(underlineAction);
    const QSignalBlocker sizeBlocker(fontSizeBox);
    const QSignalBlocker alignmentBlocker(alignmentBox);
    const QTextCharFormat format = textEdit->currentCharFormat();
    boldAction->setChecked(format.fontWeight() >= QFont::Bold);
    italicAction->setChecked(format.fontItalic());
    underlineAction->setChecked(format.fontUnderline());
    qreal points = format.fontPointSize();
    if (points <= 0) {
        points = textEdit->document()->defaultFont().pointSizeF();
    }
    fontSizeBox->setValue(qRound(points));

    const Qt::Alignment alignment = textEdit->alignment();
    /* 忽略 AlignAbsolute 等辅助标志，仅回显四种水平对齐模式。 */
    const int horizontalAlignment = static_cast<int>(alignment & (Qt::AlignLeft | Qt::AlignRight
                                                               | Qt::AlignHCenter | Qt::AlignJustify));
    alignmentBox->setCurrentIndex(alignmentBox->findData(horizontalAlignment));
}

void TextEdit::updateStatistics()
{
    /* 按 Unicode 码点计数，部分 emoji 等辅助平面字符不会被算作两个字符。 */
    const auto characters = textEdit->toPlainText().toUcs4().size();
    const auto selected = textEdit->textCursor().selectedText().toUcs4().size();
    statisticsLabel->setText(tr("字符（含空白/换行）：%1    段落：%2    已选字符：%3")
                            .arg(characters)
                            .arg(textEdit->document()->blockCount())
                            .arg(selected));
}

void TextEdit::findNext()
{
    const QString keyword = findEdit->text();
    if (keyword.isEmpty()) {
        findStatusLabel->setText(tr("请先输入查找内容。"));
        findEdit->setFocus();
        return;
    }

    const QTextCursor originalCursor = textEdit->textCursor();
    bool wrapped = false;
    if (!textEdit->find(keyword)) {
        QTextCursor startCursor = originalCursor;
        startCursor.movePosition(QTextCursor::Start);
        textEdit->setTextCursor(startCursor);
        wrapped = true;
        if (!textEdit->find(keyword)) {
            textEdit->setTextCursor(originalCursor);
            findStatusLabel->setText(tr("未找到：%1").arg(keyword));
            return;
        }
    }
    findStatusLabel->setText(wrapped ? tr("已从头继续查找：%1").arg(keyword)
                                    : tr("已找到：%1").arg(keyword));
    /* 保留查找框焦点，便于连续按回车；编辑区保留匹配选区。 */
    findEdit->setFocus();
    textEdit->ensureCursorVisible();
}

void TextEdit::selectAllText()
{
    textEdit->selectAll();
    textEdit->setFocus();
}

void TextEdit::clearText()
{
    if (textEdit->document()->isEmpty()) {
        return;
    }
    /* clear() 清空撤销历史；编辑块删除全文可一次撤销恢复文字及其格式。 */
    QTextCursor cursor = textEdit->textCursor();
    cursor.beginEditBlock();
    cursor.select(QTextCursor::Document);
    cursor.removeSelectedText();
    cursor.endEditBlock();
    textEdit->setTextCursor(cursor);
    textEdit->setFocus();
}
