# Qt Widgets 分类参考示例

独立程序 `widget_examples`，覆盖原控件速查中未标记的 52 个类。每个示例各有一个 `.h` 和一个 `.cpp`，按类型放在本目录子文件夹。

[学习路线、功能索引和完整代码教程](../docs/examples/README.md)

| 分类目录 | 示例数量 |
| --- | --- |
| [按钮](buttons/README.md) | 1 |
| [输入控件](inputs/README.md) | 10 |
| [显示控件](display/README.md) | 7 |
| [布局](layouts/README.md) | 6 |
| [容器](containers/README.md) | 9 |
| [列表、表格与树](items/README.md) | 6 |
| [主窗口](windows/README.md) | 6 |
| [对话框](dialogs/README.md) | 7 |

```bash
cmake --preset qt6-desktop
cmake --build build/qt6 --target widget_examples --parallel 4
./build/qt6/examples/widget_examples
```

源码清单显式写在 `CMakeLists.txt`；`catalog.json` 保存用途、常用 API 和练习说明，不在运行时加载。`exampleswindow.cpp` 注册页面，`main.cpp` 启动浏览器。

文档代码直接读取实际文件。修改代码或目录说明后运行：

```bash
python3 examples/tools/render_docs.py
python3 examples/tools/render_docs.py --check
```

已有 demo 保留在 `demos/`。✅ 表示已有示例可参考，不表示已经学完；建议依次操作、修改并独立复写。
