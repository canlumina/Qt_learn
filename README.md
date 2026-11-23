# Qt_learn

Qt Widgets 控件学习示例，采用左侧目录、右侧示例页面的结构。

## 本机开发（Qt 6.12.0）

`qt6-local` 预设使用 `/home/yangcan/Qt/6.12.0/gcc_64`、系统 GCC 13.3
和 Qt 安装目录中的 Ninja，以 Debug 模式构建：

Ubuntu 首次配置若提示缺少 `WrapOpenGL`，先安装开发依赖：

```sh
sudo apt-get install libgl-dev libopengl-dev
```

```sh
cmake --preset qt6-local
cmake --build --preset qt6-local --parallel
./build/qt6-local/learn
```

在支持 CMake Presets 的 IDE 中选择 `Qt 6.12.0 (local GCC 13.3)` 配置预设，
构建目标选择 `learn`。构建目录会生成 `compile_commands.json`，供 clangd 等工具使用。
本机路径配置在 `cmake/toolchain-qt6-local.cmake`，更换安装位置时修改该文件。

VS Code 中按 `Ctrl+Shift+B` 运行默认的 `Qt: build local` 任务，会先配置再编译。
CMake Tools 的配置预设和构建预设均建议选择 `qt6-local`。
原“使用工具链文件配置预设”已兼容本机工具链；若旧缓存报找不到 Ninja，
执行 `cmake --fresh --preset "使用工具链文件配置预设"`。
`.vscode/` 配置按项目现有忽略规则仅保存在本机。

## 示例目录

- `demos/buttons/`：QPushButton、QRadioButton、QCheckBox、QCommandLinkButton、QDialogButtonBox。
- `demos/inputs/`：QComboBox、QLineEdit、QSpinBox、QTextEdit；后续的输入控件也放这里，新增方法见 [目录说明](demos/inputs/README.md)。

各示例保持独立的 `.h/.cpp`，构建文件中显式列出源码，主窗口通过 `addDemo()` 注册页面。历史学习日志中的 `demos/xxx` 路径现已迁移为 `demos/buttons/xxx`。

## 学习文档

- [Qt Widgets 基本控件速查](docs/Qt基本控件速查.md)：按分类整理的控件说明，带学习进度标记
- [模块化拆分：每个控件一对文件](docs/2026-11-13-01-模块化拆分.md)
- [QRadioButton：用样式表换成开关图片](docs/2026-11-13-02-QRadioButton与资源文件.md)
- [QCheckBox：三态切换与图片样式](docs/2026-11-14-03-QCheckBox三态与样式表.md)
- [QCommandLinkButton：点击按钮打开本地目录](docs/2026-11-14-04-QCommandLinkButton打开目录.md)
- [QDialogButtonBox：标准按钮与自定义按钮](docs/2026-11-14-05-QDialogButtonBox标准与自定义按钮.md)
- [QComboBox：选择项变化时输出当前省份](docs/2026-11-14-06-QComboBox选中项切换.md)
- [QLineEdit：读取输入的文本并显示](docs/2026-11-16-07-QLineEdit读取输入文本.md)
- [QSpinBox：用数值框调节窗口不透明度](docs/2026-11-17-08-QSpinBox调节窗口不透明度.md)
- [QTextEdit：多行文本的全选与清除](docs/2026-11-23-09-QTextEdit全选与清除.md)
- [QTextEdit：富文本编辑器、查找与撤销](docs/2026-11-23-10-QTextEdit富文本编辑器.md)
