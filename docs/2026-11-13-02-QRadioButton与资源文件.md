# QRadioButton：用样式表换成开关图片

日期：2026-11-13

## 本次做了什么

在 `demos/radiobuttondemo` 里放了两个 QRadioButton，用 `style.qss` 把默认的小圆点换成 `switch_on.png` / `switch_off.png` 两张开关图片。

一开始图片不显示，排查后发现是资源文件没有打包进程序，修好了。

## 改动的文件

| 文件 | 改动 |
| --- | --- |
| `demos/radiobuttondemo.h / .cpp` | 两个 QRadioButton，读取 `:/style.qss` 并设置样式表 |
| `style.qss` | QRadioButton 的样式 |
| `res.qrc` | 加上 `<file>style.qss</file>` |
| `CMakeLists.txt` | Qt 6 分支加上 `set(CMAKE_AUTORCC ON)` |

## 知识点

### QRadioButton

- 同一个父控件下的 QRadioButton 自动互斥，选中一个，另一个自动取消。
- `setChecked(true)` 设置初始选中状态。

### 用 qss 定制外观

- `QRadioButton::indicator` 是前面那个指示器，可以设置宽高。
- `:unchecked` 和 `:checked` 两种状态分别指定一张图片：
  ```css
  QRadioButton::indicator:unchecked { image: url(:/images/switch_off.png); }
  QRadioButton::indicator:checked   { image: url(:/images/switch_on.png); }
  ```
- 样式表从资源里读出来再设置：
  ```cpp
  QFile file(":/style.qss");
  file.open(QFile::ReadOnly);
  this->setStyleSheet(QLatin1String(file.readAll()));
  ```

### 资源文件要生效的三个条件

图片、qss 要打包进可执行程序，三个条件缺一不可：

1. 文件在 `res.qrc` 里登记了一行 `<file>...</file>`。
2. `res.qrc` 写在 `CMakeLists.txt` 的 `add_executable()` 里。
3. CMake 开启了 `CMAKE_AUTORCC`。

满足之后，用冒号开头的路径访问，路径就是 `res.qrc` 里写的那个相对路径：

| `res.qrc` 里的写法 | 访问路径 |
| --- | --- |
| `<file>style.qss</file>` | `:/style.qss` |
| `<file>images/switch_on.png</file>` | `:/images/switch_on.png` |

## 遇到的问题

### 样式表没生效，图片不显示

现象：QRadioButton 还是默认的小圆点，没有任何报错。

原因有两个：

- `style.qss` 没有登记到 `res.qrc`，`:/style.qss` 这个路径不存在。代码里 `if (file.exists())` 判断为假，直接跳过了 `setStyleSheet()`。
- Qt 6 构建没有开启 `CMAKE_AUTORCC`。`qt_standard_project_setup()` 只开启 AUTOMOC 和 AUTOUIC，不包含 AUTORCC，所以整个 `res.qrc` 都没被编译进程序。Qt 5 的分支是手动开的，没有这个问题。

解决：在 `res.qrc` 里加上 `<file>style.qss</file>`；在 `CMakeLists.txt` 的 Qt 6 分支里加上 `set(CMAKE_AUTORCC ON)`。

排查方法：资源读不到时，先打印 `QFile::exists(":/style.qss")`，是 false 就按上面三个条件逐个检查。

## 验证

三套构建都编译通过。把 RadioButton 页面单独渲染成截图看过：选中的显示 `switch_on`，未选中的显示 `switch_off`。

## 遗留问题

- 文字是白色（`style.qss` 里 `color: white;`），页面背景是浅灰色，文字几乎看不见。可以改文字颜色，或者在 qss 里给页面加深色背景：`RadioButtonDemo { background-color: rgb(40, 44, 52); }`。
- `radiobuttondemo.cpp` 里 `file.open()` 的返回值没有检查，Qt 6 编译时有警告。可以改成 `if (file.open(QFile::ReadOnly)) { ... }`，同时去掉 `file.exists()`。
