# QCommandLinkButton：点击按钮打开本地目录

日期：2026-11-14

## 本次做了什么

新增 `CommandLinkButton` 示例页面，在页面上放置一个 QCommandLinkButton。按钮显示标题和说明文字，点击后通过 `QDesktopServices::openUrl()` 请求系统打开 `/home` 目录。

主窗口左侧目录新增 `QCommandLinkButton` 项，可以切换到这个示例。

## 改动的文件

| 文件 | 改动 |
| --- | --- |
| `demos/commandlinkbutton.h / .cpp` | 新增页面类、命令链接按钮和点击槽函数 |
| `mainwindow.cpp` | 包含页面头文件并调用 `addDemo()` 注册页面 |
| `CMakeLists.txt` | 将示例的 `.h/.cpp` 加入 `learn` 构建目标 |
| `README.md` | 增加本篇学习文档入口 |

## 知识点

### 标题与说明文字

QCommandLinkButton 继承自 QPushButton，适合显示带说明文字的操作入口。当前使用包含标题、说明和父控件的构造函数：

```cpp
m_commandLinkButton = new QCommandLinkButton(
    "打开/home 目录",
    "点击此将调用系统的窗口打开/home 目录",
    this);
```

第一个字符串是标题，第二个字符串是补充说明，`this` 指定所属页面。按钮随父页面销毁，不需要单独手动删除。

当前按钮使用 `setGeometry(300, 200, 250, 60)` 设置位置和大小，坐标相对于示例页面。

### 函数指针形式的信号槽

```cpp
connect(m_commandLinkButton, &QCommandLinkButton::clicked,
        this, &CommandLinkButton::on_commandLinkButton_clicked);
```

与之前的 `SIGNAL()` / `SLOT()` 字符串写法相比，这种形式可以在编译时检查信号槽的类型兼容性。`clicked` 信号带有一个 `bool` 参数，当前槽函数不需要该参数，因此使用无参数槽，Qt 允许这种连接方式。

### 将本地路径转换为 URL

```cpp
QDesktopServices::openUrl(QUrl::fromLocalFile("/home"));
```

`QUrl::fromLocalFile()` 把本地文件系统路径转换为文件 URL，避免直接拼接 URL 时遗漏路径编码处理。

`QDesktopServices::openUrl()` 将打开请求交给系统关联的应用。桌面 Ubuntu 通常会使用文件管理器打开目录；该 API 的返回值为 `bool`，`true` 表示打开请求成功，`false` 表示失败。返回成功也不能证明外部应用已完成目录显示。

这里打开的是固定路径 `/home`，其中可能包含多个用户目录；它与当前用户自己的主目录不是同一个概念。

## 验证

- 用户已说明完成编译；本次按要求不执行编译，也不将用户的编译结果记作助手验证结果。
- 本次静态核对了新增页面源码、主窗口注册和 CMake 源文件清单。
- 提交前检查 Git 身份、工作区、暂存差异、行尾空格和敏感字段。
- 本次没有点击按钮启动外部文件管理器，也没有验证目标板运行效果。

## 当前限制

- 点击槽未检查 `QDesktopServices::openUrl()` 的返回值，失败时没有提示。
- 嵌入式设备上若缺少桌面服务、文件管理器或文件 URL 关联，即使编译通过，也可能无法打开目录。
- 按钮使用固定坐标和尺寸，小窗口或不同字体设置下可能出现裁切。
- 新增页面的构造函数和槽函数尚未提供符合工程规范的中文函数注释，后续修改这些函数时应补充功能、参数、返回值和调用限制说明。
