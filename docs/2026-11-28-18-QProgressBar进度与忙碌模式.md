# QProgressBar：模拟进度、忙碌模式与重新开始

日期：2026-11-28

## 本次练习

根据 `examples/display/` 的进度条示例，在 `demos/display/progressbar.h / .cpp` 实现 `ProgressBar` 页面，通过 `learn` 主窗口的 `QProgressBar` 项打开。页面继承 QWidget，使用 QVBoxLayout 排列说明文字、进度条、忙碌模式复选框和开始按钮。

QProgressBar 常用于下载、文件复制、设备升级等耗时操作的进度反馈。已知总量时，用 `setRange(0, 100)` 和 `setValue()` 显示百分比；总量未知时，用 `setRange(0, 0)` 显示忙碌状态。本练习由 QTimer 模拟任务，不执行下载、文件写入或硬件操作。

点击“开始/重新开始”后，模拟进度清零，定时器以 80 ms 为间隔，每次增加 2 个百分点，理想情况下约 4 秒完成；实际耗时受 GUI 事件循环调度影响。达到 100 后停止定时器，退出忙碌模式并显示 100%。

## 关键实现

```cpp
auto *progressBar = new QProgressBar(this);
progressBar->setRange(0, 100);
progressBar->setValue(0);
auto *timer = new QTimer(this);
timer->setInterval(80);

/**
 * @brief 按复选框状态切换进度显示方式
 * @param enabled true 使用忙碌模式，false 恢复确定进度
 * @note 无返回值；在 GUI 线程执行，切换模式不重置模拟进度。
 */
connect(busy, &QCheckBox::toggled, this, [this, progressBar](bool enabled) {
    progressBar->setRange(0, enabled ? 0 : 100);
    if (!enabled)
        progressBar->setValue(completed);
});
```

以上为代码节选，完整构造函数、布局及定时器连接见 `demos/display/progressbar.cpp`。

- `completed` 独立保存已完成的百分比，忙碌模式只切换显示方式，模拟任务继续推进。
- 退出忙碌模式后，用 `setValue(completed)` 恢复实际进度；原先传入 `enabled` 会把 `false` 转成 0，导致进度暂时回零，本次已修正。
- 重新开始时将 `completed` 清零，保留当前显示模式，并重新启动定时器。
- 说明标签已加入布局，避免标签未参与布局而显示异常。
- 所有操作在 GUI 线程执行；定时器回调只更新模拟计数，不执行阻塞任务。真实耗时工作应避免阻塞 GUI 事件循环。
- 控件和定时器均以页面为父对象，连接以页面为上下文，页面销毁后由 Qt 释放对象并断开连接，无需额外析构函数。

## 文件和学习进度

- 新增 `demos/display/progressbar.h / .cpp`，补充构造函数及三个信号回调的中文注释。
- 根 `CMakeLists.txt` 将源码加入 `learn`；`mainwindow.cpp` 包含头文件并注册页面。
- 更新显示分类 README、根 README 文档索引和控件速查的分类汇总。
- 保留已有 `✅ QProgressBar`，注明已完成个人练习；显示类下一项推进到 QTextBrowser。

## 验证

沿用现有 Qt 5.15.2、系统 C++ 编译器和 Ninja 配置，提交前检查 `learn` 目标：

```bash
cmake --build build/qt5 --target learn --parallel 4
```

上述命令执行成功，`learn` 目标编译、链接通过。

另用临时 Qt 验证程序，在 `QT_QPA_PLATFORM=offscreen` 下直接触发定时器超时信号，确认说明标签已加入布局、初始进度为 0、退出忙碌模式恢复累计进度、两种模式下重新开始会清零，以及两种模式完成后均停止定时器并显示 100%。这些检查全部通过，临时验证文件未加入提交。

无桌面验证未检查实际定时间隔和动画外观，Qt 6 和开发板表现也需单独验证。建议运行后点击开始，在中途勾选并取消忙碌模式，确认恢复累计百分比；分别在普通模式和忙碌模式下重新开始，再等待完成，确认最终显示 100%。
