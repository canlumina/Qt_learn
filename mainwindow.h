#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class QListWidget;
class QStackedWidget;

/* 主窗口只负责“外壳”：左侧是示例目录，右侧显示选中的示例页面。
 * 每个控件的练习代码都在 demos/ 目录下各自的文件里。 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    /* 注册一个示例：目录里加一项，并把对应页面放进右侧 */
    void addDemo(const QString &title, QWidget *page);

    Ui::MainWindow *ui;
    QListWidget *listWidget;        /* 左侧：示例目录 */
    QStackedWidget *stackedWidget;  /* 右侧：示例页面，一次只显示一页 */
};
#endif // MAINWINDOW_H
