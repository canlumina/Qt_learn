# Qt_learn

Qt Widgets 控件学习示例，采用左侧目录、右侧示例页面的结构。

## 示例目录

- `demos/buttons/`：QPushButton、QRadioButton、QCheckBox、QCommandLinkButton、QDialogButtonBox。
- `demos/inputs/`：预留给输入控件，新增方法见 [目录说明](demos/inputs/README.md)。

各示例保持独立的 `.h/.cpp`，构建文件中显式列出源码，主窗口通过 `addDemo()` 注册页面。历史学习日志中的 `demos/xxx` 路径现已迁移为 `demos/buttons/xxx`。

## 学习文档

- [模块化拆分：每个控件一对文件](docs/2026-11-13-01-模块化拆分.md)
- [QRadioButton：用样式表换成开关图片](docs/2026-11-13-02-QRadioButton与资源文件.md)
- [QCheckBox：三态切换与图片样式](docs/2026-11-14-03-QCheckBox三态与样式表.md)
- [QCommandLinkButton：点击按钮打开本地目录](docs/2026-11-14-04-QCommandLinkButton打开目录.md)
- [QDialogButtonBox：标准按钮与自定义按钮](docs/2026-11-14-05-QDialogButtonBox标准与自定义按钮.md)
