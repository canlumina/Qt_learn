# Qt Widgets 基本控件速查

按 Qt Designer 左侧控件栏的分类整理。每个控件说明：是什么、什么时候用、最常用的信号或方法。

**频率标记**

- ★★★ 高频：几乎每个项目都会用，优先学
- ★★ 中频：特定场景常用，用到再学
- ★ 低频：知道有这个东西即可

**学习进度**：✅ 表示 `learn/demos` 里已经写过示例。

---

## 一、先分清三个概念

| 概念 | 作用 | 例子 |
| --- | --- | --- |
| 控件（Widget） | 用户能看到、能操作的东西 | QPushButton、QLineEdit |
| 布局（Layout） | 不可见，负责排列控件的位置和大小 | QVBoxLayout、QGridLayout |
| 容器（Container） | 可见，用来装其他控件并分组 | QGroupBox、QTabWidget |

写界面的基本套路：**容器里放布局，布局里放控件**。

---

## 二、按钮类（Buttons）

用户点一下就触发动作，或者在几个选项里做选择。

| 控件 | 频率 | 是什么 | 什么时候用 | 常用信号 / 方法 |
| --- | --- | --- | --- | --- |
| QPushButton ✅ | ★★★ | 普通按钮 | 确定、取消、提交、打开等一切“点击执行”的动作 | `clicked()` |
| QCheckBox ✅ | ★★★ | 复选框，可多选 | 多个选项互不影响：记住密码、同意协议、功能开关 | `toggled(bool)`、`isChecked()` |
| QRadioButton ✅ | ★★★ | 单选按钮，同组互斥 | 几个选项只能选一个：性别、支付方式 | `toggled(bool)`，配合 QButtonGroup |
| QToolButton | ★★ | 工具按钮，通常只有图标 | 工具栏里的图标按钮、带下拉菜单的按钮 | `clicked()`、`setMenu()` |
| QDialogButtonBox ✅ | ★★ | 一组标准按钮（确定/取消/应用） | 对话框底部，自动按系统习惯排列按钮顺序 | `accepted()`、`rejected()` |
| QCommandLinkButton ✅ | ★ | 带说明文字的大按钮 | 向导页里“选择下一步做什么” | `clicked()` |

**选择建议**

- 单选用 QRadioButton，多选用 QCheckBox；选项超过 5 个的单选改用 QComboBox。
- 多组单选按钮要互不干扰，就把每组放进各自的 QGroupBox 或 QButtonGroup。

---

## 三、输入类（Input Widgets）

让用户输入或选择一个值。**选哪个控件取决于数据类型。**

| 控件 | 频率 | 是什么 | 什么时候用 | 常用信号 / 方法 |
| --- | --- | --- | --- | --- |
| QLineEdit ✅ | ★★★ | 单行文本框 | 用户名、密码、搜索框、路径 | `text()`、`textChanged()`、`returnPressed()`、`setEchoMode()` |
| QComboBox ✅ | ★★★ | 下拉选择框 | 从固定的一组选项里选一个：省份、语言、串口号 | `currentIndexChanged()`、`currentText()`、`addItems()` |
| QSpinBox | ★★★ | 整数输入框，带上下箭头 | 数量、年龄、端口号等有范围的整数 | `value()`、`valueChanged()`、`setRange()` |
| QDoubleSpinBox | ★★ | 小数输入框 | 价格、温度、比例等浮点数 | 同上，另有 `setDecimals()` |
| QTextEdit | ★★★ | 多行富文本编辑框 | 备注、聊天输入、显示带格式的内容 | `toPlainText()`、`setHtml()`、`append()` |
| QPlainTextEdit | ★★★ | 多行纯文本编辑框 | 日志输出、代码或配置文本，大文本性能比 QTextEdit 好 | `appendPlainText()`、`toPlainText()` |
| QSlider | ★★ | 滑块 | 音量、亮度、进度拖动等不需要精确数值的调节 | `valueChanged()`、`setRange()` |
| QDateEdit / QTimeEdit / QDateTimeEdit | ★★ | 日期、时间输入框 | 生日、预约时间、查询的起止日期 | `date()`、`dateChanged()`、`setCalendarPopup(true)` |
| QDial | ★ | 旋钮 | 模拟仪器面板上的旋钮 | `valueChanged()` |
| QScrollBar | ★ | 独立滚动条 | 很少单独用，一般由 QScrollArea 自动提供 | `valueChanged()` |
| QFontComboBox | ★ | 字体下拉框 | 文本编辑器里选字体 | `currentFontChanged()` |
| QKeySequenceEdit | ★ | 快捷键录入框 | 设置页里让用户自定义快捷键 | `keySequenceChanged()` |

**选择建议**

- 文本：单行用 QLineEdit，多行纯文本用 QPlainTextEdit，需要加粗、颜色、图片才用 QTextEdit。
- 数字：要精确值用 QSpinBox，要手感用 QSlider，两者常绑在一起用。
- 选项：选项少且要一眼看全用 QRadioButton，选项多或空间紧用 QComboBox。
- 输入限制：QLineEdit 用 `setValidator()` 或 `setInputMask()` 限制格式，比事后检查省事。

---

## 四、显示类（Display Widgets）

只给用户看，一般不接收输入。

| 控件 | 频率 | 是什么 | 什么时候用 | 常用方法 |
| --- | --- | --- | --- | --- |
| QLabel | ★★★ | 标签，显示文字或图片 | 输入框前的说明文字、显示图片、显示状态 | `setText()`、`setPixmap()` |
| QProgressBar | ★★★ | 进度条 | 下载、复制、加载等耗时操作 | `setValue()`、`setRange()`；`setRange(0,0)` 表示忙碌状态 |
| QTextBrowser | ★★ | 只读富文本，支持超链接 | 帮助文档、更新说明 | `setHtml()`、`anchorClicked()` |
| QLCDNumber | ★ | 仿液晶数码管 | 时钟、计数器、仪表读数 | `display()` |
| QCalendarWidget | ★ | 月历 | 需要直接展示整个月历的页面 | `selectedDate()`、`clicked()` |
| QGraphicsView | ★★ | 图形视图 | 绘图、流程图、可缩放拖动的画布 | 配合 QGraphicsScene 使用 |
| Line（QFrame） | ★★ | 水平或垂直分隔线 | 把界面分成几块 | Designer 里直接拖 |

---

## 五、布局类（Layouts）

布局不可见，但决定界面好不好看、窗口缩放时会不会乱。**必学，全部高频。**

| 布局 | 频率 | 排列方式 | 什么时候用 |
| --- | --- | --- | --- |
| QVBoxLayout | ★★★ | 从上到下一列 | 竖着排的内容 |
| QHBoxLayout | ★★★ | 从左到右一行 | 一排按钮、标签加输入框 |
| QGridLayout | ★★★ | 行列网格，可跨行跨列 | 计算器键盘、较复杂的表单 |
| QFormLayout | ★★★ | 两列：左标签、右输入 | 登录、设置、信息填写表单 |
| QStackedLayout | ★★ | 多个页面叠在一起，只显示一个 | 一般直接用 QStackedWidget |
| Spacer（QSpacerItem） | ★★★ | 弹簧，占住空白 | 把按钮顶到右边或底部 |

**要点**

- 布局可以嵌套：外层 QVBoxLayout 里放几个 QHBoxLayout 是最常见的写法。
- `addStretch()` 加弹簧，`setSpacing()` 调间距，`setContentsMargins()` 调边距。
- 不要用 `setGeometry()` 写死坐标，窗口一缩放就乱。

---

## 六、容器类（Containers）

装其他控件，用来分组、分页、分区。

| 控件 | 频率 | 是什么 | 什么时候用 | 常用方法 |
| --- | --- | --- | --- | --- |
| QWidget | ★★★ | 最基础的空白容器，所有控件的基类 | 自定义页面、把一组控件包成一个整体 | `setLayout()` |
| QGroupBox | ★★★ | 带标题的分组框 | 把相关设置圈在一起，给单选按钮分组 | `setTitle()`、`setCheckable()` |
| QTabWidget | ★★★ | 选项卡 | 设置窗口的多个分页 | `addTab()`、`currentChanged()` |
| QStackedWidget | ★★★ | 堆叠页面，没有自带的切换按钮 | 左侧列表切换右侧页面（`learn` 的主窗口就是这个结构）、向导 | `addWidget()`、`setCurrentIndex()` |
| QScrollArea | ★★ | 滚动区域 | 内容超出窗口大小时 | `setWidget()`、`setWidgetResizable(true)` |
| QFrame | ★★ | 带边框的容器 | 需要边框或做分隔线 | `setFrameShape()` |
| QSplitter | ★★ | 分割器，中间可拖动 | 左右或上下分栏，让用户调整比例 | `addWidget()`、`setSizes()` |
| QToolBox | ★ | 抽屉式折叠面板 | 类似旧版 QQ 的好友分组 | `addItem()` |
| QDockWidget | ★★ | 可停靠、可浮动的面板 | IDE 风格的侧边栏，只能用在 QMainWindow 里 | `addDockWidget()` |
| QMdiArea | ★ | 多文档区域 | 一个窗口里开多个子窗口 | `addSubWindow()` |

**QTabWidget 和 QStackedWidget 的区别**：前者自带选项卡标签；后者只管页面切换，由你用列表、按钮等任何方式控制。

---

## 七、列表、表格、树（Item Widgets / Item Views）

显示多条数据。每种都有两个版本：

- **Widget 版**（QListWidget 等）：数据直接存在控件里，简单，适合入门和数据量小的场景。
- **View 版**（QListView 等）：数据存在独立的 Model 里，灵活、性能好，适合数据量大或要连数据库的场景。

| 控件 | 频率 | 是什么 | 什么时候用 | 常用方法 |
| --- | --- | --- | --- | --- |
| QListWidget | ★★★ | 列表 | 文件列表、导航菜单、聊天联系人 | `addItem()`、`currentRowChanged()`、`itemClicked()` |
| QTableWidget | ★★★ | 表格 | 行列数据：学生成绩、订单、设备参数 | `setRowCount()`、`setItem()`、`setHorizontalHeaderLabels()` |
| QTreeWidget | ★★★ | 树 | 有层级的数据：目录结构、组织架构 | `addTopLevelItem()`、`itemClicked()` |
| QListView / QTableView / QTreeView | ★★ | 上面三个的 Model/View 版 | 数据量大、多个视图共享一份数据、连数据库 | `setModel()` |

**学习顺序**：先学三个 Widget 版，熟练后再学 Model/View。

---

## 八、主窗口相关

QMainWindow 自带的几个固定区域。

| 控件 | 频率 | 是什么 | 什么时候用 |
| --- | --- | --- | --- |
| QMainWindow | ★★★ | 主窗口框架 | 带菜单栏、工具栏、状态栏的程序主界面 |
| QMenuBar / QMenu | ★★★ | 菜单栏和菜单 | 顶部的“文件、编辑”菜单，右键菜单 |
| QAction | ★★★ | 一个“动作” | 同一个功能同时出现在菜单、工具栏、快捷键里时，只写一次 |
| QToolBar | ★★ | 工具栏 | 菜单下面那排常用功能的图标 |
| QStatusBar | ★★ | 状态栏 | 窗口底部显示提示信息、当前状态 |

**三种窗口基类怎么选**

- QMainWindow：程序主窗口，需要菜单栏和状态栏。
- QDialog：弹出来的对话框，用完就关。
- QWidget：其他情况，比如嵌在别的窗口里的页面。

---

## 九、对话框（Dialogs）

Qt 已经做好的标准弹窗，一行代码就能用。

| 对话框 | 频率 | 作用 | 典型用法 |
| --- | --- | --- | --- |
| QMessageBox | ★★★ | 提示、警告、报错、询问 | `QMessageBox::information()`、`warning()`、`critical()`、`question()` |
| QFileDialog | ★★★ | 选择文件或目录 | `getOpenFileName()`、`getSaveFileName()`、`getExistingDirectory()` |
| QDialog | ★★★ | 自定义对话框的基类 | `exec()` 模态显示，`show()` 非模态显示 |
| QInputDialog | ★★ | 让用户输入一个值 | `getText()`、`getInt()`、`getItem()` |
| QColorDialog | ★ | 选颜色 | `getColor()` |
| QFontDialog | ★ | 选字体 | `getFont()` |
| QProgressDialog | ★ | 带取消按钮的进度弹窗 | 长时间任务 |

---

## 十、高频控件清单

如果时间有限，先把这 20 个学会，足够写出大部分常见界面。

| 类别 | 控件 |
| --- | --- |
| 按钮 | QPushButton ✅、QCheckBox ✅、QRadioButton ✅ |
| 输入 | QLineEdit ✅、QComboBox ✅、QSpinBox、QTextEdit、QPlainTextEdit |
| 显示 | QLabel、QProgressBar |
| 布局 | QVBoxLayout、QHBoxLayout、QGridLayout、QFormLayout |
| 容器 | QGroupBox、QTabWidget、QStackedWidget |
| 数据 | QListWidget、QTableWidget、QTreeWidget |
| 窗口 | QMainWindow、QAction、QMessageBox、QFileDialog |

---

## 十一、建议的后续学习顺序

按 `learn/demos` 现在的进度往下排：

1. **输入类补完**（放 `demos/inputs/`）：QSpinBox → QTextEdit / QPlainTextEdit → QSlider → QDateTimeEdit
2. **显示类**：QLabel（文字和图片）→ QProgressBar（配合 QTimer）
3. **布局**：四种布局各写一个示例，重点是嵌套和弹簧
4. **容器类**：QGroupBox → QTabWidget → QStackedWidget → QScrollArea → QSplitter
5. **数据类**：QListWidget → QTableWidget → QTreeWidget
6. **对话框**：QMessageBox → QFileDialog → 自定义 QDialog
7. **主窗口**：QAction、菜单栏、工具栏、状态栏
8. **进阶**：Model/View、自定义控件（重写 `paintEvent`）、QSS 样式表
