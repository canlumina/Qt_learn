#ifndef TEXTEDIT_H
#define TEXTEDIT_H

#include <QWidget>

class QAction;
class QComboBox;
class QLabel;
class QLineEdit;
class QSpinBox;
class QTextCharFormat;
class QTextEdit;

/* 富文本练习页面：页面负责布局，内部 QTextEdit 负责编辑文档。 */
class TextEdit : public QWidget
{
    Q_OBJECT
public:
    /**
     * @brief 创建富文本编辑页面并连接操作信号
     * @param parent 父控件，可为空；子控件随页面自动释放
     * @note 无返回值，必须在 QApplication 初始化后的 GUI 线程调用。
     */
    explicit TextEdit(QWidget *parent = nullptr);

private:
    /**
     * @brief 合并选中文字或后续输入的字符格式
     * @param format 仅包含本次需要修改的格式属性
     * @note 无返回值，只允许 GUI 线程调用；不自动选中整词，保留其他格式属性。
     */
    void mergeFormat(const QTextCharFormat &format);

    QTextEdit *textEdit;
    QAction *boldAction;
    QAction *italicAction;
    QAction *underlineAction;
    QSpinBox *fontSizeBox;
    QComboBox *alignmentBox;
    QLineEdit *findEdit;
    QLabel *findStatusLabel;
    QLabel *statisticsLabel;

private slots:
    /**
     * @brief 设置选中文字或后续输入是否加粗
     * @param enabled true 表示加粗，false 表示常规字重
     * @note 无返回值，GUI 线程调用；格式修改可撤销。
     */
    void setBold(bool enabled);

    /**
     * @brief 设置选中文字或后续输入是否使用斜体
     * @param enabled true 表示斜体，false 表示取消斜体
     * @note 无返回值，GUI 线程调用；不改变字重和颜色。
     */
    void setItalic(bool enabled);

    /**
     * @brief 设置选中文字或后续输入是否带下划线
     * @param enabled true 表示添加下划线，false 表示取消
     * @note 无返回值，GUI 线程调用；不改变其他字符格式。
     */
    void setUnderline(bool enabled);

    /**
     * @brief 设置选中文字或后续输入的字号
     * @param points 字号，单位为点，仅接受 8～48
     * @note 无返回值，GUI 线程调用；工具栏回显时阻断信号，避免误改文档。
     */
    void setFontSize(int points);

    /**
     * @brief 打开颜色对话框并应用用户确认的文字颜色
     * @note 无参数、无返回值，GUI 线程调用；对话框为模态，取消时保留原格式。
     */
    void chooseTextColor();

    /**
     * @brief 设置当前段落或选中段落的对齐方式
     * @param index 对齐下拉框的索引，非法索引不处理
     * @note 无返回值，GUI 线程调用；段落格式修改可撤销。
     */
    void setParagraphAlignment(int index);

    /**
     * @brief 根据光标处格式更新工具栏状态
     * @note 无参数、无返回值，GUI 线程调用；阻断控件信号，防止更新状态改写文档。
     */
    void syncFormatControls();

    /**
     * @brief 更新文档字符数、段落数及选中字符数
     * @note 无参数、无返回值，GUI 线程调用；字符按 Unicode 码点计数，含空白和换行。
     */
    void updateStatistics();

    /**
     * @brief 从当前光标处查找下一项，必要时从文档开头继续
     * @note 无参数、无返回值，GUI 线程调用；不区分大小写，无匹配时恢复原光标。
     */
    void findNext();

    /**
     * @brief 全选编辑区文本并将焦点交回编辑区
     * @note 无参数、无返回值，GUI 线程调用；不会修改文档内容。
     */
    void selectAllText();

    /**
     * @brief 删除整篇文档内容，并保留一次撤销恢复的能力
     * @note 无参数、无返回值，GUI 线程调用；使用 QTextCursor 编辑块，不调用 clear()。
     */
    void clearText();
};

#endif
