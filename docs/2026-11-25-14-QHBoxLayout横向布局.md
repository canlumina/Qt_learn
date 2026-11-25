# QHBoxLayout：横向排列与输入回显

日期：2026-11-25

## 本次练习

根据 `examples/layouts/` 的参考示例，在 `demos/layouts/hboxlayout.h / .cpp` 实现 `HBoxLayout` 页面，并注册到 `learn` 主窗口的 `QHBoxLayout` 项。

页面自身继承 QWidget。顶层 QHBoxLayout 从左到右排列说明标签、设备名称输入行和状态标签；输入行又由一个 QHBoxLayout 排列“设备名称”标签、QLineEdit 和“应用”按钮。点击“应用”，状态标签显示“已应用: 输入内容”。

## 关键实现

```cpp
row = new QHBoxLayout;
input = new QLineEdit(this);
apply = new QPushButton(tr("应用"), this);
status = new QLabel(tr("等待输入"), this);

row->addWidget(new QLabel(tr("设备名称:"), this));
row->addWidget(input, 1);
row->addWidget(apply);

layout->addLayout(row);
layout->addWidget(status);
```

以上为代码节选，完整实现见 `demos/layouts/hboxlayout.cpp`。

- `new QHBoxLayout(this)` 为页面安装横向布局，四周边距为 12，整体按顶部对齐。
- `addLayout(row)` 嵌套输入行；顶层也使用横向布局，因此说明、输入行、状态显示在水平方向排列。
- `addWidget(input, 1)` 设置输入框的伸缩因子，使其在输入行内优先获得额外宽度，具体尺寸仍受最小尺寸和大小策略约束。
- `clicked` 连接带 `this` 上下文的 lambda，从输入框读取文本后更新状态标签；父对象负责子控件和布局的生命周期。
- 状态标签当前设置为 `Qt::RichText`，输入中的 HTML 标记会按富文本解释。若要原样显示 `<b>` 等内容，可改用 `Qt::PlainText`。

“应用”只更新页面文字，不会保存配置、写入文件或控制设备。空输入仍会回显“已应用: ”，未添加额外校验。

## 文件和学习进度

- CMake 源码清单和 `mainwindow.cpp` 的页面注册随 demo 一并提交。
- 为构造函数及点击回调补充中文注释，说明功能、参数、无返回值和 GUI 线程要求；清理新增源码中的行末空白。
- 更新布局分类 README、根 README 文档索引，以及控件速查中的能力说明和分类汇总。
- 保留已有 `✅ QHBoxLayout`，注明已完成个人练习；下一项布局练习推进到 QGridLayout。

## 验证结果与限制

使用当前 Qt 5.15.2、系统 C++ 编译器及 Ninja 配置检查 `learn` 目标：

```bash
cmake --build build/qt5 --target learn --parallel 4
```

上述命令执行成功，`learn` 目标编译和链接通过；差异空白、文档相对链接及敏感字段检查通过。

尚未逐项手动检查真实桌面上的输入回显、长文本与窗口缩放，也未验证 Qt 6 或开发板显示效果。
