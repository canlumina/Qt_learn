#ifndef EXAMPLESWINDOW_H
#define EXAMPLESWINDOW_H

#include <QMainWindow>
#include <QVector>

class QListWidget;
class QStackedWidget;

/** @brief 独立的分类示例浏览器，选择条目时才创建对应页面。 */
class ExamplesWindow : public QMainWindow {
    Q_OBJECT
public:
    /**
     * @brief 创建导航、筛选框和页面容器
     * @param parent 父窗口，可为空
     * @note 无返回值；GUI 线程调用，所有示例由窗口的子对象树管理。
     */
    explicit ExamplesWindow(QWidget *parent = nullptr);

private slots:
    /**
     * @brief 显示选定的控件练习页
     * @param row 注册表中的行号；越界或负数时不处理
     * @note 无返回值；首次访问才创建页面，后续访问保留输入状态。
     */
    void showExample(int row);

    /**
     * @brief 按控件名或分类筛选导航项
     * @param text 搜索文字，空字符串恢复全部条目
     * @note 无返回值；不销毁已创建页面，无匹配时隐藏内容区域。
     */
    void filterExamples(const QString &text);

private:
    QListWidget *list;
    QStackedWidget *stack;
    QVector<QWidget *> pages;
};

#endif
