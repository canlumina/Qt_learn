#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "demos/pushbuttondemo.h"
#include "demos/radiobuttondemo.h"
#include "demos/checkboxdemo.h"
#include "demos/commandlinkbutton.h"

#include <QHBoxLayout>
#include <QListWidget>
#include <QStackedWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    /* 要放在 setupUi() 之后，否则会被 .ui 文件里的 800x600 覆盖 */
    this->setGeometry(0, 0, 800, 480);

    listWidget = new QListWidget(this);
    listWidget->setFixedWidth(150);
    stackedWidget = new QStackedWidget(this);

    /* 左右排列：目录 | 示例页面 */
    QHBoxLayout *layout = new QHBoxLayout(ui->centralwidget);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addWidget(listWidget);
    layout->addWidget(stackedWidget);

    /* 点击目录的第 n 项，右侧就切换到第 n 个页面 */
    connect(listWidget, SIGNAL(currentRowChanged(int)),
            stackedWidget, SLOT(setCurrentIndex(int)));

    /* ---- 示例注册处 ----
     * 新增一个示例只需三步：
     *   1. 在 demos/ 下新建 xxxdemo.h / xxxdemo.cpp（继承 QWidget）
     *   2. 把这两个文件加进 CMakeLists.txt 的 add_executable()
     *   3. 在本文件 #include 它，并在下面加一行 addDemo() */
    addDemo("QPushButton", new PushButtonDemo(this));
    addDemo("QRadioButton", new RadioButtonDemo(this));
    addDemo("QCheckBox", new CheckBoxDemo(this));
    addDemo("QCommandLinkButton", new CommandLinkButton(this));

    listWidget->setCurrentRow(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addDemo(const QString &title, QWidget *page)
{
    listWidget->addItem(title);
    stackedWidget->addWidget(page);
}
