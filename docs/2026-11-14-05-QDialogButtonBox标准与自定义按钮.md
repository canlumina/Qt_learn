# QDialogButtonBox：标准按钮与自定义按钮

日期：2026-11-14

## 本次做了什么

新增 `DialogButtonBox` 示例，注册到主窗口左侧目录的 `QDialogButtonBox` 项。示例中添加一个标准 Cancel 按钮，并将文字改为“取消”；另添加一个文字为“自定义”的按钮。

点击任一按钮时，槽函数识别按钮对象，通过 `qDebug()` 输出对应的中文日志。当前没有创建 QDialog，也没有实现关闭页面或取消操作的业务逻辑。

## 相关文件

| 文件 | 作用 |
| --- | --- |
| `demos/dialogbuttonbox.h / .cpp` | 定义示例类、添加按钮和处理点击信号 |
| `mainwindow.cpp` | 包含头文件并用 `addDemo()` 注册示例 |
| `CMakeLists.txt` | 将新增 `.h/.cpp` 加入构建目标 |
| `README.md` | 增加本篇开发日志入口 |

## 知识点

### 标准按钮与显示文字

```cpp
dialogButtonBox->addButton(QDialogButtonBox::Cancel);
dialogButtonBox->button(QDialogButtonBox::Cancel)->setText(tr("取消"));
```

`addButton(StandardButton)` 创建并添加标准按钮，`button(StandardButton)` 获取对应的 QPushButton 指针。当前先添加再获取，保证 Cancel 按钮存在；如果查询的是未添加的标准按钮，则可能返回空指针。

改变显示文字不会改变标准按钮身份或角色。`tr()` 将字符串标记为可翻译文本，实际翻译还需要相应的翻译文件和加载流程。

### 自定义按钮与角色

```cpp
pushButton = new QPushButton(tr("自定义"));
dialogButtonBox->addButton(pushButton, QDialogButtonBox::ActionRole);
```

`ActionRole` 表示执行某项操作的按钮，本身不表示接受或拒绝对话框。按钮角色也参与按钮盒的平台布局规则，因此显示顺序不一定等于添加顺序。

虽然创建自定义按钮时没有指定父对象，`addButton()` 会接管该按钮的所有权。按钮盒销毁时会释放按钮，无需另写析构函数删除它。

### 使用点击信号识别按钮

```cpp
connect(dialogButtonBox, &QDialogButtonBox::clicked,
        this, &DialogButtonBox::dialogButtonBoxClicked);
```

`clicked(QAbstractButton *)` 传入实际被点击的按钮对象。槽函数将参数与 Cancel 按钮指针、自定义按钮指针分别比较，从而选择日志内容。这比比较按钮文字更可靠，因为文字可能被修改或翻译。

函数指针形式可以在编译时检查信号槽的类型兼容性。源码注释把字符串形式的 `SIGNAL()` / `SLOT()` 写法描述为“Qt6 已弃用”，这一表述不准确：Qt 6 仍支持该形式，本示例使用函数指针形式是推荐做法。

### 按钮角色不会自动关闭页面

Cancel 标准按钮具有 `RejectRole`，点击时可触发按钮盒的 `rejected()` 信号。如果希望关闭真实对话框，通常还需要把该信号连接到 `QDialog::reject()`。

当前只连接 `clicked()`，所以点击“取消”仅输出“点击了取消按钮”，不会关闭主窗口或示例页面。

### 当前页面结构与资源释放

当前 `DialogButtonBox` 类本身继承 QDialogButtonBox，同时又通过 `new QDialogButtonBox(this)` 创建内部按钮盒，实际按钮放在内部对象中。内部按钮盒使用固定位置 `(300, 200)` 和大小 `200 × 30`。

外层页面销毁时，Qt 父子对象机制会删除内部按钮盒，再释放其拥有的按钮。本次保留当前结构，未做重构。

## 验证与限制

- 本次核对了新增源码、主窗口注册和 CMake 文件清单，并检查提交差异及敏感字段。
- 沿用用户此前要求，本次不执行编译，也未运行界面或验证日志输出。
- 不同平台的按钮布局、字体大小和固定尺寸可能影响显示效果，仍需运行验证。
- 当前新增函数尚未提供完整的中文函数注释；后续修改函数实现时应按工程规范补充功能、参数、返回值和调用限制。
