#!/usr/bin/env python3
"""从控件目录元数据和实际源码生成带完整代码的 Markdown 教程。"""

import argparse
import json
from pathlib import Path


def render(root):
    """生成文档内容映射。root 为工程根目录，返回路径到正文的字典；只读源码。"""
    examples = root / "examples"
    entries = json.loads((examples / "catalog.json").read_text(encoding="utf-8"))
    categories = {
        "buttons": "按钮", "inputs": "输入控件", "display": "显示控件", "layouts": "布局",
        "containers": "容器", "items": "列表、表格与树", "windows": "主窗口", "dialogs": "对话框",
    }
    files = {}
    contents = []
    category_links = []
    overview = ["# Qt Widgets 剩余控件学习路线与示例\n",
                "本教程覆盖原速查中未打勾的 52 个不同类。每个类对应 `examples/` 中独立的一对 `.h/.cpp`，"
                "同一行中的日期/时间、三种 View、菜单栏/菜单均拆为独立示例；QFrame 同时覆盖容器和分隔线。\n",
                "这些是可供阅读和运行的参考示例，不等同于你已经掌握了全部控件。"
                "建议每次只学习一页，完成操作、独立修改参数，再尝试脱离示例复写。\n",
                "## 编译和启动\n",
                "沿用项目已有 Qt 5/Qt 6 与 CMake 工具链，无新增第三方依赖。独立目标不会替换 `learn`。\n",
                "```bash\ncmake --preset qt6-desktop\ncmake --build build/qt6 --target widget_examples --parallel 4\n"
                "./build/qt6/examples/widget_examples\n```\n",
                "若 Qt 安装在其他位置，调整预设的 `CMAKE_PREFIX_PATH`。程序支持按控件名或分类筛选，"
                "按需创建页面并保留已创建页面的状态。原 `demos/` 练习及正在编写的 PlainTextEdit 保留。\n",
                "## 推荐学习顺序\n",
                "1. **布局与容器基础**：QVBoxLayout → QHBoxLayout → QGridLayout → QFormLayout → QSpacerItem → QWidget → QGroupBox。\n"
                "2. **输入与反馈**：QPlainTextEdit → QDoubleSpinBox → QSlider → 日期/时间输入 → QLabel → QProgressBar。\n"
                "3. **分页与区域**：QTabWidget → QStackedWidget → QStackedLayout → QScrollArea → QSplitter。\n"
                "4. **数据显示**：QListWidget → QTableWidget → QTreeWidget，再比较 QListView / QTableView / QTreeView。\n"
                "5. **对话框与窗口命令**：QMessageBox → QInputDialog → QDialog → QFileDialog → QAction → 菜单/工具栏/状态栏 → QMainWindow。\n"
                "6. **按需扩展**：颜色/字体选择、快捷键、日历、数码管、旋钮、QGraphicsView、QDockWidget、QMdiArea、QToolBox。\n",
                "每个示例先回答三个问题：谁保存状态？什么信号通知变化？变化后由谁更新界面？"
                "布局、所有权和信号槽比背下每一个 API 更重要。\n",
                "## 分类教程与完整源码\n",
                "每一节包含用途、适用场景、常用 API、操作步骤、注意事项以及完整头文件和实现。"
                "代码直接从实际文件嵌入，后续修改后运行 `python3 examples/tools/render_docs.py` 同步；"
                "加 `--check` 可只检查同步状态。\n",
                "| 分类 | 数量 | 阅读入口 |\n| --- | --- | --- |\n"]
    for category, title in categories.items():
        group = [entry for entry in entries if entry["category"] == category]
        overview[-1] += f"| {title} | {len(group)} | [{title}教程]({category}.md) |\n"
        category_links.append(f"| [{title}]({category}/README.md) | {len(group)} |\n")
        directory = [f"# {title}参考示例\n\n",
                     f"本目录包含 {len(group)} 个示例，每个类各有一对 `.h/.cpp`，由 `widget_examples` 统一运行。\n\n",
                     f"[用途、常用方式、操作步骤与完整代码](../../docs/examples/{category}.md) · "
                     "[返回示例目录](../README.md)\n\n",
                     "| 控件 | 头文件 | 实现文件 | 示例功能 |\n| --- | --- | --- | --- |\n"]
        for entry in group:
            header = Path(entry["header"]).name
            source = Path(entry["source"]).name
            directory.append(f"| {entry['control']} | [{header}]({header}) | "
                             f"[{source}]({source}) | {entry['demo']} |\n")
        files[examples / category / "README.md"] = "".join(directory)
        section = [f"# {title}示例与完整代码\n", "[返回学习路线](README.md)\n"]
        for entry in group:
            section += [f"## {entry['control']}\n",
                        f"**是什么**：{entry['purpose']}\n",
                        f"**用途**：{entry['uses']}\n",
                        f"**最常用的方式**：{entry['methods']}。下面的实现展示创建控件、配置初始值，再用信号槽处理变化。\n",
                        f"**本 demo**：{entry['demo']}\n",
                        f"**操作步骤**：{entry['steps']}\n"]
            if entry["notes"]:
                section.append(f"**注意事项**：{entry['notes']}\n")
            section.append("全部示例在 GUI 线程操作控件；QObject 子对象由父对象释放。"
                           "未出现显式资源释放代码时，仍应检查模型、场景、布局项和对话框的所有权。\n")
            for key, caption in (("header", "头文件"), ("source", "实现文件")):
                relative = entry[key]
                source = examples / relative
                code = source.read_text(encoding="utf-8")
                section.append(f"### {caption}：`examples/{relative}`\n")
                section.append(f"```cpp\n{code.rstrip()}\n```\n")
            contents.append(f"| {entry['control']} | {title} | `{entry['source']}` | {entry['demo']} |\n")
        files[root / "docs/examples" / f"{category}.md"] = "\n".join(section)
    overview += ["\n## 控件到代码的对照\n", "| 控件 | 分类 | examples/ 下的实现 | 示例功能 |\n"
                 "| --- | --- | --- | --- |\n", "".join(contents),
                 "\n## 通用边界\n",
                 "- 与采样、亮度、设备相关的数值仅为模拟，不控制真实硬件。\n"
                 "- 文件对话框只选择路径，不创建或覆盖文件；编辑框内的内容退出后不保存。\n"
                 "- 进度示例由 QTimer 驱动；真实耗时任务应放工作线程，通过信号回到 GUI。\n"
                 "- 对话框取消时检查返回值；菜单和快捷键存在平台差异。\n"
                 "- 目标板的字体、窗口管理、文件选择、浮动面板和剪贴板效果需要上板确认。\n",
                 "验证状态见 [开发记录](../2026-11-23-11-剩余控件分类示例.md)。\n"]
    files[root / "docs/examples/README.md"] = "\n".join(overview)
    files[examples / "README.md"] = ("# Qt Widgets 分类参考示例\n\n"
        "独立程序 `widget_examples`，覆盖原控件速查中未标记的 52 个类。每个示例各有一个 `.h` 和一个 `.cpp`，按类型放在本目录子文件夹。\n\n"
        "[学习路线、功能索引和完整代码教程](../docs/examples/README.md)\n\n"
        "| 分类目录 | 示例数量 |\n| --- | --- |\n" + "".join(category_links) + "\n"
        "```bash\ncmake --preset qt6-desktop\ncmake --build build/qt6 --target widget_examples --parallel 4\n./build/qt6/examples/widget_examples\n```\n\n"
        "源码清单显式写在 `CMakeLists.txt`；`catalog.json` 保存用途、常用 API 和练习说明，"
        "不在运行时加载。`exampleswindow.cpp` 注册页面，`main.cpp` 启动浏览器。\n\n"
        "文档代码直接读取实际文件。修改代码或目录说明后运行：\n\n"
        "```bash\npython3 examples/tools/render_docs.py\npython3 examples/tools/render_docs.py --check\n```\n\n"
        "已有 demo 保留在 `demos/`。✅ 表示已有示例可参考，不表示已经学完；建议依次操作、修改并独立复写。\n")
    return files


def main():
    """解析同步或检查模式；无输入参数，返回 0 成功或 1 表示文档不同步。"""
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--check", action="store_true", help="只检查，不写入文件")
    args = parser.parse_args()
    root = Path(__file__).resolve().parents[2]
    stale = []
    for path, text in render(root).items():
        if args.check:
            if not path.exists() or path.read_text(encoding="utf-8") != text:
                stale.append(str(path.relative_to(root)))
        else:
            path.parent.mkdir(parents=True, exist_ok=True)
            path.write_text(text, encoding="utf-8")
    if stale:
        print("文档需要同步：" + "、".join(stale))
        return 1
    print("示例文档与源码一致。" if args.check else "已同步学习路线、分类目录说明和 8 篇教程。")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
