#include "exampleswindow.h"

#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QSplitter>
#include <QStackedWidget>
#include <QVBoxLayout>

#include "buttons/toolbuttonexample.h"
#include "containers/dockwidgetexample.h"
#include "containers/groupboxexample.h"
#include "containers/mdiareaexample.h"
#include "containers/scrollareaexample.h"
#include "containers/splitterexample.h"
#include "containers/stackedwidgetexample.h"
#include "containers/tabwidgetexample.h"
#include "containers/toolboxexample.h"
#include "containers/widgetexample.h"
#include "dialogs/colordialogexample.h"
#include "dialogs/dialogexample.h"
#include "dialogs/filedialogexample.h"
#include "dialogs/fontdialogexample.h"
#include "dialogs/inputdialogexample.h"
#include "dialogs/messageboxexample.h"
#include "dialogs/progressdialogexample.h"
#include "display/calendarwidgetexample.h"
#include "display/frameexample.h"
#include "display/graphicsviewexample.h"
#include "display/labelexample.h"
#include "display/lcdnumberexample.h"
#include "display/progressbarexample.h"
#include "display/textbrowserexample.h"
#include "inputs/dateeditexample.h"
#include "inputs/datetimeeditexample.h"
#include "inputs/dialexample.h"
#include "inputs/doublespinboxexample.h"
#include "inputs/fontcomboboxexample.h"
#include "inputs/keysequenceeditexample.h"
#include "inputs/plaintexteditexample.h"
#include "inputs/scrollbarexample.h"
#include "inputs/sliderexample.h"
#include "inputs/timeeditexample.h"
#include "items/listviewexample.h"
#include "items/listwidgetexample.h"
#include "items/tableviewexample.h"
#include "items/tablewidgetexample.h"
#include "items/treeviewexample.h"
#include "items/treewidgetexample.h"
#include "layouts/formlayoutexample.h"
#include "layouts/gridlayoutexample.h"
#include "layouts/hboxlayoutexample.h"
#include "layouts/spaceritemexample.h"
#include "layouts/stackedlayoutexample.h"
#include "layouts/vboxlayoutexample.h"
#include "windows/actionexample.h"
#include "windows/mainwindowexample.h"
#include "windows/menubarexample.h"
#include "windows/menuexample.h"
#include "windows/statusbarexample.h"
#include "windows/toolbarexample.h"

namespace {
/** @brief 创建指定练习页；@param parent 父页面；@return 新建的 QWidget；GUI 线程调用，父对象管理生命周期。 */
template <typename Page> QWidget *createExample(QWidget *parent)
{
    return new Page(parent);
}

struct ExampleEntry {
    const char *category;
    const char *control;
    QWidget *(*create)(QWidget *);
};

const ExampleEntry entries[] = {
    { "按钮", "QToolButton", &createExample<ToolButtonExample> },
    { "输入", "QDoubleSpinBox", &createExample<DoubleSpinBoxExample> },
    { "输入", "QPlainTextEdit", &createExample<PlainTextEditExample> },
    { "输入", "QSlider", &createExample<SliderExample> },
    { "输入", "QDateEdit", &createExample<DateEditExample> },
    { "输入", "QTimeEdit", &createExample<TimeEditExample> },
    { "输入", "QDateTimeEdit", &createExample<DateTimeEditExample> },
    { "输入", "QDial", &createExample<DialExample> },
    { "输入", "QScrollBar", &createExample<ScrollBarExample> },
    { "输入", "QFontComboBox", &createExample<FontComboBoxExample> },
    { "输入", "QKeySequenceEdit", &createExample<KeySequenceEditExample> },
    { "显示", "QLabel", &createExample<LabelExample> },
    { "显示", "QProgressBar", &createExample<ProgressBarExample> },
    { "显示", "QTextBrowser", &createExample<TextBrowserExample> },
    { "显示", "QLCDNumber", &createExample<LCDNumberExample> },
    { "显示", "QCalendarWidget", &createExample<CalendarWidgetExample> },
    { "显示", "QGraphicsView", &createExample<GraphicsViewExample> },
    { "显示", "QFrame", &createExample<FrameExample> },
    { "布局", "QVBoxLayout", &createExample<VBoxLayoutExample> },
    { "布局", "QHBoxLayout", &createExample<HBoxLayoutExample> },
    { "布局", "QGridLayout", &createExample<GridLayoutExample> },
    { "布局", "QFormLayout", &createExample<FormLayoutExample> },
    { "布局", "QStackedLayout", &createExample<StackedLayoutExample> },
    { "布局", "QSpacerItem", &createExample<SpacerItemExample> },
    { "容器", "QWidget", &createExample<WidgetExample> },
    { "容器", "QGroupBox", &createExample<GroupBoxExample> },
    { "容器", "QTabWidget", &createExample<TabWidgetExample> },
    { "容器", "QStackedWidget", &createExample<StackedWidgetExample> },
    { "容器", "QScrollArea", &createExample<ScrollAreaExample> },
    { "容器", "QSplitter", &createExample<SplitterExample> },
    { "容器", "QToolBox", &createExample<ToolBoxExample> },
    { "容器", "QDockWidget", &createExample<DockWidgetExample> },
    { "容器", "QMdiArea", &createExample<MdiAreaExample> },
    { "列表表格与树", "QListWidget", &createExample<ListWidgetExample> },
    { "列表表格与树", "QTableWidget", &createExample<TableWidgetExample> },
    { "列表表格与树", "QTreeWidget", &createExample<TreeWidgetExample> },
    { "列表表格与树", "QListView", &createExample<ListViewExample> },
    { "列表表格与树", "QTableView", &createExample<TableViewExample> },
    { "列表表格与树", "QTreeView", &createExample<TreeViewExample> },
    { "主窗口", "QMainWindow", &createExample<MainWindowExample> },
    { "主窗口", "QMenuBar", &createExample<MenuBarExample> },
    { "主窗口", "QMenu", &createExample<MenuExample> },
    { "主窗口", "QAction", &createExample<ActionExample> },
    { "主窗口", "QToolBar", &createExample<ToolBarExample> },
    { "主窗口", "QStatusBar", &createExample<StatusBarExample> },
    { "对话框", "QMessageBox", &createExample<MessageBoxExample> },
    { "对话框", "QFileDialog", &createExample<FileDialogExample> },
    { "对话框", "QDialog", &createExample<DialogExample> },
    { "对话框", "QInputDialog", &createExample<InputDialogExample> },
    { "对话框", "QColorDialog", &createExample<ColorDialogExample> },
    { "对话框", "QFontDialog", &createExample<FontDialogExample> },
    { "对话框", "QProgressDialog", &createExample<ProgressDialogExample> },
};
const int exampleCount = static_cast<int>(sizeof(entries) / sizeof(entries[0]));
}

ExamplesWindow::ExamplesWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle(tr("Qt Widgets 分类学习示例"));
    resize(1000, 640);
    auto *central = new QWidget(this);
    setCentralWidget(central);
    auto *layout = new QVBoxLayout(central);
    auto *hint = new QLabel(tr("按控件名筛选；每页的用途、练习步骤和完整源码见 docs/examples/。"), central);
    hint->setWordWrap(true);
    layout->addWidget(hint);
    auto *filter = new QLineEdit(central);
    filter->setPlaceholderText(tr("筛选控件或分类，例如 QSlider、布局、对话框"));
    filter->setClearButtonEnabled(true);
    layout->addWidget(filter);
    auto *splitter = new QSplitter(Qt::Horizontal, central);
    list = new QListWidget(splitter);
    list->setObjectName("examplesNavigation");
    stack = new QStackedWidget(splitter);
    stack->setObjectName("examplesPages");
    splitter->addWidget(list);
    splitter->addWidget(stack);
    splitter->setChildrenCollapsible(false);
    splitter->setStretchFactor(1, 1);
    splitter->setSizes({ 240, 740 });
    layout->addWidget(splitter, 1);
    pages.resize(exampleCount);
    for (int index = 0; index < exampleCount; ++index) {
        pages[index] = nullptr;
        list->addItem(
            QString::fromUtf8(entries[index].category) + " / " + QString::fromUtf8(entries[index].control));
    }
    // 按需创建页面：启动时不用同时实例化所有字体、模型和图形视图。
    connect(list, &QListWidget::currentRowChanged, this, &ExamplesWindow::showExample);
    connect(filter, &QLineEdit::textChanged, this, &ExamplesWindow::filterExamples);
    list->setCurrentRow(0);
}

void ExamplesWindow::showExample(int row)
{
    if (row < 0 || row >= exampleCount)
        return;
    if (!pages[row]) {
        pages[row] = entries[row].create(stack);
        stack->addWidget(pages[row]);
    }
    stack->setCurrentWidget(pages[row]);
}

void ExamplesWindow::filterExamples(const QString &text)
{
    int firstVisible = -1;
    for (int row = 0; row < list->count(); ++row) {
        const bool match = list->item(row)->text().contains(text, Qt::CaseInsensitive);
        list->item(row)->setHidden(!match);
        if (match && firstVisible < 0)
            firstVisible = row;
    }
    stack->setVisible(firstVisible >= 0);
    const int current = list->currentRow();
    if (firstVisible >= 0 && (current < 0 || list->item(current)->isHidden()))
        list->setCurrentRow(firstVisible);
}
