# QGridLayout：通道参数与跨列说明

日期：2026-11-26

## 本次练习

根据 `examples/layouts/` 的网格布局示例，在 `demos/layouts/gridlayout.h / .cpp` 实现 `GridLayoutExample` 页面，并注册到 `learn` 主窗口的 `QGridLayout` 项。

页面自身继承 QWidget，顶层 QVBoxLayout 放置描述文字和 QGridLayout。网格共三列：通道名称、目标值、启用状态；第 0 行是表头，第 1～3 行是三个模拟通道，第 4 行的说明跨三列。

每个目标值由 QSpinBox 输入，范围为 0～1000；每个通道有独立的 QCheckBox。本次只练习控件排列和数据输入，没有连接启用状态与输入框的联动，也不访问硬件或保存参数。

## 关键代码

```cpp
for (int row = 1; row <= 3; ++row) {
    grid->addWidget(new QLabel(tr("通道 %1").arg(row), this), row, 0);
    auto *value = new QSpinBox(this);
    value->setRange(0, 1000);
    grid->addWidget(value, row, 1);
    grid->addWidget(new QCheckBox(this), row, 2);
}

grid->setColumnStretch(1, 1);
grid->addWidget(new QLabel(tr("本说明跨越三列，不访问硬件。"), this), 4, 0, 1, 3);
layout->addLayout(grid);
```

以上为代码节选，完整实现见 `demos/layouts/gridlayout.cpp`。

- `addWidget(widget, row, column)` 根据从 0 开始的行号、列号定位控件。
- 循环为每个通道创建独立的标签、数值框和复选框，三列保持对齐。
- `setColumnStretch(1, 1)` 设置第 1 列，即目标值列的伸缩因子，使其优先分配额外宽度，实际尺寸仍受控件最小尺寸等约束。
- 最后一个 `addWidget()` 的 `4, 0, 1, 3` 表示从第 4 行、第 0 列开始，占 1 行、3 列。
- `addLayout(grid)` 将网格嵌入页面的纵向布局；控件和布局由 Qt 父子对象机制管理。

## 文件和学习进度

- 新增 `demos/layouts/gridlayout.h / .cpp`，保留现有交互和布局；将构造函数注释调整为准确描述页面功能。
- 根 `CMakeLists.txt` 将源码加入 `learn`；`mainwindow.cpp` 包含头文件并注册页面。
- 更新布局分类 README、根 README 文档索引，以及控件速查中的分类汇总和能力说明。
- 保留已有 `✅ QGridLayout`，注明已完成个人练习；下一项布局练习推进到 QFormLayout。

## 验证结果与限制

沿用当前 Qt 5.15.2、系统 C++ 编译器和 Ninja 构建配置，执行：

```bash
cmake --build build/qt5 --target learn --parallel 4
```

`learn` 目标编译、链接通过。提交前另检查差异空白、文档相对链接、敏感字段及暂存范围，避免纳入编译产物或本地配置。

尚未在真实桌面逐项验证数值输入、复选框操作、长文本和窗口缩放，也未验证 Qt 6 或开发板。建议运行后调整目标值及勾选状态，拉宽窗口观察目标值列，再尝试修改跨行、跨列参数，比较布局效果。
