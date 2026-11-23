# QPlainTextEdit：读取本地文本与只读切换

日期：2026-11-24

## 问题与原因

原代码使用 `QFile file(dir.filePath(":./text.txt"));`，但 `dir` 是可执行文件目录。实际检查中，该表达式仍得到 `:./text.txt`，没有定位到磁盘上的 `build/qt5/text.txt`；`res.qrc` 也未收录这个文本文件。

三种路径需要分清：

| 写法 | 查找位置 |
| --- | --- |
| `QFile("text.txt")` | 程序当前工作目录，取决于终端或 IDE 的启动配置 |
| `QFile(QDir(QCoreApplication::applicationDirPath()).filePath("text.txt"))` | 可执行文件所在目录，本 demo 采用此方式 |
| `QFile(":/text.txt")` | 已通过 `.qrc` 编译进程序且资源路径匹配的文件 |

不需要额外添加 Qt 库。已有 `Qt::Core`、`Qt::Widgets` 依赖满足本示例。

## 修改内容

- 使用 `dir.filePath("text.txt")` 读取普通磁盘文件，显式包含 `<QFile>`。
- 按 UTF-8 读取；Qt 5 使用 `setCodec("UTF-8")`，Qt 6 沿用默认 UTF-8 编码。
- 检查打开和读取结果，失败时在编辑区占位文字及控制台输出完整路径和错误原因。
- 修复头文件保护宏 `PLAINTEXTEDIT_H` 的拼写，补充构造函数和槽函数的中文说明。
- 保留 QRadioButton，设置 `setAutoExclusive(false)`，并使用 `toggled` 处理状态；再次点击可取消只读。
- 更新输入目录说明、README 索引及控件速查中的能力说明，保留原有 ✅，不重复标记。

## 使用方法

当前文件已在 `build/qt5/text.txt`，无需移动。重新编译并启动：

```bash
cmake --build build/qt5 --target learn --parallel 4
./build/qt5/learn
```

选择左侧 `QPlainTextEdit` 页面。文本在程序创建页面时读取一次；修改磁盘文件后需重新启动程序。切换只读仅影响编辑区，不会修改文件权限，也不自动保存编辑内容。

换用其他构建目录时，需要把 UTF-8 `text.txt` 放到那份 `learn` 可执行文件旁。构建目录下的测试文本继续按原忽略规则留在本地，本次未修改它，也未加入 Qt 资源或自动复制规则。

## 验证结果与限制

- 使用当前缓存配置执行 `cmake --build build/qt5 --target learn --parallel 4`，Qt 5.15.2 编译和链接通过。
- 临时 offscreen 检查程序复用实际编译的 demo 对象，分别验证用户文本副本及中文 UTF-8 文本，读取结果一致。
- 从可执行文件目录以外启动，仍能读取可执行文件旁的文本。
- 验证缺失文件及同名目录两种失败情况，均显示完整路径和错误提示。
- 连续两次点击单选按钮，能从可编辑切到只读，再恢复可编辑；重复包含头文件的编译检查通过。
- 测试数据位于临时目录，原 `build/qt5/text.txt` 未修改。

本次未重新构建 Qt 6，也未验证真实桌面显示或开发板。文件在 GUI 线程中一次性读取，适合本 demo 的小文件；大文件应另行设计分段读取或后台加载。固定坐标布局保持原样，小屏及窗口缩放时的排版仍需单独调整。

## 补充：connect 的编辑器诊断

用户反馈 `toggled(bool)` 连接到无参数 `radioButtonClicked()` 时出现重载不匹配提示。这种连接符合 Qt 规则：槽函数可以忽略信号末尾多余的参数，实际编译也已通过；`toggled` 声明在 QAbstractButton 中，QRadioButton 继承该信号，诊断中显示基类函数指针并不表示写法错误。

检查发现 `.vscode/settings.json` 仍指向不存在的 `build/qt6/compile_commands.json`，备用头文件路径也是 Qt 6，而当前 CMake 构建目录为 `build/qt5`。已将 C/C++ 扩展、clangd 的编译数据库路径及备用 Qt 头文件路径统一为当前 Qt 5 配置，并保留原信号连接写法。该文件按现有规则只留在本地。

编辑器应使用当前构建生成的编译数据库；切换 Qt 版本时也要同步调整。配置更新后若仍保留旧诊断，可重载 VS Code 窗口后再次检查。助手未直接读取重载后的 Problems 面板，红线是否清除仍需在编辑器中确认。
