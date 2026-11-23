# Qt Widgets 剩余控件学习路线与示例

本教程覆盖原速查中未打勾的 52 个不同类。每个类对应 `examples/` 中独立的一对 `.h/.cpp`，同一行中的日期/时间、三种 View、菜单栏/菜单均拆为独立示例；QFrame 同时覆盖容器和分隔线。

这些是可供阅读和运行的参考示例，不等同于你已经掌握了全部控件。建议每次只学习一页，完成操作、独立修改参数，再尝试脱离示例复写。

## 编译和启动

沿用项目已有 Qt 5/Qt 6 与 CMake 工具链，无新增第三方依赖。独立目标不会替换 `learn`。

```bash
cmake --preset qt6-desktop
cmake --build build/qt6 --target widget_examples --parallel 4
./build/qt6/examples/widget_examples
```

若 Qt 安装在其他位置，调整预设的 `CMAKE_PREFIX_PATH`。程序支持按控件名或分类筛选，按需创建页面并保留已创建页面的状态。原 `demos/` 练习及正在编写的 PlainTextEdit 保留。

## 推荐学习顺序

1. **布局与容器基础**：QVBoxLayout → QHBoxLayout → QGridLayout → QFormLayout → QSpacerItem → QWidget → QGroupBox。
2. **输入与反馈**：QPlainTextEdit → QDoubleSpinBox → QSlider → 日期/时间输入 → QLabel → QProgressBar。
3. **分页与区域**：QTabWidget → QStackedWidget → QStackedLayout → QScrollArea → QSplitter。
4. **数据显示**：QListWidget → QTableWidget → QTreeWidget，再比较 QListView / QTableView / QTreeView。
5. **对话框与窗口命令**：QMessageBox → QInputDialog → QDialog → QFileDialog → QAction → 菜单/工具栏/状态栏 → QMainWindow。
6. **按需扩展**：颜色/字体选择、快捷键、日历、数码管、旋钮、QGraphicsView、QDockWidget、QMdiArea、QToolBox。

每个示例先回答三个问题：谁保存状态？什么信号通知变化？变化后由谁更新界面？布局、所有权和信号槽比背下每一个 API 更重要。

## 分类教程与完整源码

每一节包含用途、适用场景、常用 API、操作步骤、注意事项以及完整头文件和实现。代码直接从实际文件嵌入，后续修改后运行 `python3 examples/tools/render_docs.py` 同步；加 `--check` 可只检查同步状态。

| 分类 | 数量 | 阅读入口 |
| --- | --- | --- |
| 按钮 | 1 | [按钮教程](buttons.md) |
| 输入控件 | 10 | [输入控件教程](inputs.md) |
| 显示控件 | 7 | [显示控件教程](display.md) |
| 布局 | 6 | [布局教程](layouts.md) |
| 容器 | 9 | [容器教程](containers.md) |
| 列表、表格与树 | 6 | [列表、表格与树教程](items.md) |
| 主窗口 | 6 | [主窗口教程](windows.md) |
| 对话框 | 7 | [对话框教程](dialogs.md) |


## 控件到代码的对照

| 控件 | 分类 | examples/ 下的实现 | 示例功能 |
| --- | --- | --- | --- |

| QToolButton | 按钮 | `buttons/toolbuttonexample.cpp` | 一个主操作加两个菜单选项，操作结果显示在标签中。 |
| QDoubleSpinBox | 输入控件 | `inputs/doublespinboxexample.cpp` | 输入目标温度，实时显示取到的数值。 |
| QPlainTextEdit | 输入控件 | `inputs/plaintexteditexample.cpp` | 追加模拟采样日志，可切换只读、清空并限制为 100 段。 |
| QSlider | 输入控件 | `inputs/sliderexample.cpp` | 滑块与数值框双向同步，显示模拟亮度百分比。 |
| QDateEdit | 输入控件 | `inputs/dateeditexample.cpp` | 带日历弹窗的日期输入，选择后显示 ISO 日期。 |
| QTimeEdit | 输入控件 | `inputs/timeeditexample.cpp` | 编辑模拟定时任务的执行时间。 |
| QDateTimeEdit | 输入控件 | `inputs/datetimeeditexample.cpp` | 设置模拟预约时间，回显本地日期时间。 |
| QDial | 输入控件 | `inputs/dialexample.cpp` | 用旋钮调整模拟输出百分比。 |
| QScrollBar | 输入控件 | `inputs/scrollbarexample.cpp` | 模拟在 0～900 的数据偏移中移动。 |
| QFontComboBox | 输入控件 | `inputs/fontcomboboxexample.cpp` | 为预览文字切换字体，保留固定字号。 |
| QKeySequenceEdit | 输入控件 | `inputs/keysequenceeditexample.cpp` | 录入快捷键，焦点离开录入框后按该快捷键更新计数。 |
| QLabel | 显示控件 | `display/labelexample.cpp` | 同时展示可复制文字和程序生成的色块图片。 |
| QProgressBar | 显示控件 | `display/progressbarexample.cpp` | 定时器模拟进度，可切换确定进度和忙碌模式，支持重新开始。 |
| QTextBrowser | 显示控件 | `display/textbrowserexample.cpp` | 内置帮助内容与锚点导航，不启动外部浏览器。 |
| QLCDNumber | 显示控件 | `display/lcdnumberexample.cpp` | 数值框调整模拟电压，LCD 回显带一位小数的读数。 |
| QCalendarWidget | 显示控件 | `display/calendarwidgetexample.cpp` | 日历选择与日期回显，同时突出标记今天。 |
| QGraphicsView | 显示控件 | `display/graphicsviewexample.cpp` | 可拖动的矩形与椭圆，提供放大、缩小和复位。 |
| QFrame | 显示控件 | `display/frameexample.cpp` | 上方带边框的说明区域，下方使用水平分隔线。 |
| QVBoxLayout | 布局 | `layouts/vboxlayoutexample.cpp` | 标题、可伸缩编辑区、底部操作按钮纵向排列。 |
| QHBoxLayout | 布局 | `layouts/hboxlayoutexample.cpp` | 标签、可伸缩输入框、提交按钮位于同一行。 |
| QGridLayout | 布局 | `layouts/gridlayoutexample.cpp` | 三行模拟通道输入与一个跨三列的说明。 |
| QFormLayout | 布局 | `layouts/formlayoutexample.cpp` | 设备名称、采样周期、备注组成一个可伸缩表单。 |
| QStackedLayout | 布局 | `layouts/stackedlayoutexample.cpp` | 下拉框切换两个布局页面。 |
| QSpacerItem | 布局 | `layouts/spaceritemexample.cpp` | 固定宽度占位和水平伸缩占位同时演示。 |
| QWidget | 容器 | `containers/widgetexample.cpp` | 一个整体启用或禁用的参数区域。 |
| QGroupBox | 容器 | `containers/groupboxexample.cpp` | 两组独立的单选模式，其中高级配置可以整体关闭。 |
| QTabWidget | 容器 | `containers/tabwidgetexample.cpp` | 连接配置与采样配置两个选项卡。 |
| QStackedWidget | 容器 | `containers/stackedwidgetexample.cpp` | 导航列表切换概览与参数页面。 |
| QScrollArea | 容器 | `containers/scrollareaexample.cpp` | 一个包含 30 个参数输入框的长表单。 |
| QSplitter | 容器 | `containers/splitterexample.cpp` | 左侧目录，右侧说明，分栏可拖动。 |
| QToolBox | 容器 | `containers/toolboxexample.cpp` | 常规、显示、维护三个工具页。 |
| QDockWidget | 容器 | `containers/dockwidgetexample.cpp` | 嵌入一个主窗口，提供可拖动日志面板和恢复显示按钮。 |
| QMdiArea | 容器 | `containers/mdiareaexample.cpp` | 新建多个临时文档窗口，提供平铺与层叠。 |
| QListWidget | 列表、表格与树 | `items/listwidgetexample.cpp` | 添加与删除条目，选中时显示文本。 |
| QTableWidget | 列表、表格与树 | `items/tablewidgetexample.cpp` | 三行模拟测量数据，允许编辑和点击表头排序。 |
| QTreeWidget | 列表、表格与树 | `items/treewidgetexample.cpp` | 设备、分组与通道的两级树，点击显示条目路径。 |
| QListView | 列表、表格与树 | `items/listviewexample.cpp` | 使用 QStringListModel 提供列表，选择时从 QModelIndex 读取数据。 |
| QTableView | 列表、表格与树 | `items/tableviewexample.cpp` | 模型提供通道数据，代理模型按通道名筛选并排序。 |
| QTreeView | 列表、表格与树 | `items/treeviewexample.cpp` | 用 QStandardItemModel 构建设备和通道层级。 |
| QMainWindow | 主窗口 | `windows/mainwindowexample.cpp` | 嵌入一个具备菜单、工具栏和状态栏的小主窗口。 |
| QMenuBar | 主窗口 | `windows/menubarexample.cpp` | 操作和帮助两个菜单，触发后回显。 |
| QMenu | 主窗口 | `windows/menuexample.cpp` | 文本区右键菜单，包含全选、清空和换行开关。 |
| QAction | 主窗口 | `windows/actionexample.cpp` | 一个“显示网格”动作同时放进工具栏和菜单，状态自动同步。 |
| QToolBar | 主窗口 | `windows/toolbarexample.cpp` | 带刷新动作和模式下拉框的工具栏。 |
| QStatusBar | 主窗口 | `windows/statusbarexample.cpp` | 左边显示会超时消失的消息，右边保留演示模式状态。 |
| QMessageBox | 对话框 | `dialogs/messageboxexample.cpp` | 安全的模拟确认，默认选择否，不执行真实删除。 |
| QFileDialog | 对话框 | `dialogs/filedialogexample.cpp` | 选择现有文件、目录或拟保存路径，仅回显路径。 |
| QDialog | 对话框 | `dialogs/dialogexample.cpp` | 自定义通道名称对话框，确认后回显，取消保留原值。 |
| QInputDialog | 对话框 | `dialogs/inputdialogexample.cpp` | 输入通道名称或采样次数，正确区分确认与取消。 |
| QColorDialog | 对话框 | `dialogs/colordialogexample.cpp` | 选择颜色并应用到预览标签，取消保留原色。 |
| QFontDialog | 对话框 | `dialogs/fontdialogexample.cpp` | 选择字体并应用到中英文预览。 |
| QProgressDialog | 对话框 | `dialogs/progressdialogexample.cpp` | 定时器驱动的模拟任务，可取消并重新开始。 |


## 通用边界

- 与采样、亮度、设备相关的数值仅为模拟，不控制真实硬件。
- 文件对话框只选择路径，不创建或覆盖文件；编辑框内的内容退出后不保存。
- 进度示例由 QTimer 驱动；真实耗时任务应放工作线程，通过信号回到 GUI。
- 对话框取消时检查返回值；菜单和快捷键存在平台差异。
- 目标板的字体、窗口管理、文件选择、浮动面板和剪贴板效果需要上板确认。

验证状态见 [开发记录](../2026-11-23-11-剩余控件分类示例.md)。
