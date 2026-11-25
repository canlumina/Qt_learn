# QVBoxLayout：纵向排列与编辑区伸缩

日期：2026-11-25

## 本次练习

根据 `examples/layouts/vboxlayoutexample.h / .cpp`，在 `demos/layouts/` 自己实现 `VBoxLayout` 页面，并注册到 `learn` 的左侧目录。QVBoxLayout 是负责排列子控件的布局类，练习页面自身继承 QWidget。

页面从上到下包含：可换行的描述标签、“顶部说明”标签、多行纯文本编辑区和“确定”按钮。按钮只展示布局位置，尚未连接业务操作；编辑区内容不保存。

## 关键代码

```cpp
auto *layout = new QVBoxLayout(this);
layout->setContentsMargins(12, 12, 12, 12);
layout->setAlignment(Qt::AlignTop);

auto *editor = new QPlainTextEdit(this);
editor->setPlaceholderText(tr("请输入内容"));
layout->addWidget(new QLabel(tr("顶部说明"), this));
layout->addWidget(editor, 1);
layout->addWidget(new QPushButton(tr("确定"), this));
```

以上为关键代码节选，完整源码见 `demos/layouts/vboxlayout.cpp`。

- `new QVBoxLayout(this)` 为页面安装顶层布局，子控件由布局计算位置，不依赖固定坐标。
- `setContentsMargins(12, 12, 12, 12)` 设置左、上、右、下边距。
- `setWordWrap(true)` 使较长的描述随标签宽度换行。
- `addWidget(editor, 1)` 为编辑区设置伸缩因子，使其优先获得额外高度；实际尺寸仍受各控件最小尺寸及大小策略约束。
- 页面、布局和子控件由 Qt 的父子所有权管理，本例没有需要手动释放的独立资源。

## 文件与学习进度

- 新增 `demos/layouts/vboxlayout.h / .cpp` 与分类目录 README。
- 根目录 `CMakeLists.txt` 将源码加入 `learn`，`mainwindow.cpp` 注册 `QVBoxLayout` 页面。
- 补充构造函数的中文注释，说明功能、父对象参数、无返回值及 GUI 线程要求；清理新增文件的行末空白。
- 根 README 增加分类入口和开发记录索引；速查表保留 `✅ QVBoxLayout`，注明已完成个人练习，并将下一项布局练习推进到 QHBoxLayout。

## 验证与练习建议

使用当前 Qt 5.15.2、系统 C++ 编译器及 Ninja 配置验证 `learn` 目标：

```bash
cmake --build build/qt5 --target learn --parallel 4
```

上述命令执行成功，`learn` 目标重新配置、编译和链接通过；差异空白、文档相对链接和敏感字段检查通过。

建议运行后进入 `QVBoxLayout` 页面，输入多行文字，再拉高、缩小窗口观察编辑区高度变化；将伸缩因子从 1 改为 0，比较布局分配。尚未在真实桌面逐项手动验证窗口缩放和文本输入，也未验证 Qt 6 或开发板显示。
