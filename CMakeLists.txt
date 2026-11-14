cmake_minimum_required(VERSION 3.19)
project(learn LANGUAGES CXX)

# 同时支持 Qt 6 / Qt 5（桌面）与嵌入式交叉编译：
#   Qt6 桌面 : cmake -S . -B build/qt6 -G Ninja -DCMAKE_PREFIX_PATH=/home/yangcan/program/Qt/6.11.1/gcc_64
#   Qt5 桌面 : cmake -S . -B build/qt5 -G Ninja -DCMAKE_PREFIX_PATH=/home/yangcan/program/Qt/5.15.2/gcc_64
#   i.MX6ULL : cmake -S . -B build/imx6ull -G Ninja -DCMAKE_TOOLCHAIN_FILE=cmake/toolchain-imx6ull.cmake
#
# Qt5 的 CMake 配置若不在标准位置，也可以直接用 -DQt5_DIR=.../lib/cmake/Qt5 指定。

# 桌面工具链用 C++17；部分老嵌入式工具链（如 Linaro GCC 4.9）不支持 C++17，
# 自动降级到能支持的最高标准
if("cxx_std_17" IN_LIST CMAKE_CXX_COMPILE_FEATURES)
    set(CMAKE_CXX_STANDARD 17)
elseif("cxx_std_14" IN_LIST CMAKE_CXX_COMPILE_FEATURES)
    message(STATUS "当前编译器不支持 C++17，降级使用 C++14")
    set(CMAKE_CXX_STANDARD 14)
else()
    message(STATUS "当前编译器不支持 C++14，降级使用 C++11")
    set(CMAKE_CXX_STANDARD 11)
endif()
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(GNUInstallDirs)

# 先找不带版本号的 QT，再按实际主版本号找 Qt5 或 Qt6，这是官方推荐的兼容写法
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Widgets)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_standard_project_setup()   # 自动开启 AUTOMOC / AUTOUIC（不包含 AUTORCC）
    set(CMAKE_AUTORCC ON)         # 没有这一行，res.qrc 不会被编译进程序
else()
    # Qt5 没有 qt_standard_project_setup()，手动开这几项
    set(CMAKE_AUTOMOC ON)
    set(CMAKE_AUTOUIC ON)
    set(CMAKE_AUTORCC ON)
endif()

add_executable(learn
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    # 每个控件的练习各占一对 .h/.cpp，新增示例时在这里追加
    demos/pushbuttondemo.cpp
    demos/pushbuttondemo.h
    demos/radiobuttondemo.cpp
    demos/radiobuttondemo.h
    demos/checkboxdemo.cpp
    demos/checkboxdemo.h
    res.qrc
    style.qss
)

target_link_libraries(learn
    PRIVATE
        Qt${QT_VERSION_MAJOR}::Core
        Qt${QT_VERSION_MAJOR}::Widgets
)

install(TARGETS learn
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

# 部署脚本只对桌面版 Qt6 有意义，交叉编译出来的程序由 buildroot 的 rootfs 提供运行库
if(QT_VERSION_MAJOR EQUAL 6 AND NOT CMAKE_CROSSCOMPILING)
    # Qt 6.4 起参数名是 OUTPUT_SCRIPT，更老的 6.x 用 FILENAME_VARIABLE
    if(QT_VERSION VERSION_LESS 6.4)
        qt_generate_deploy_app_script(
            TARGET learn
            FILENAME_VARIABLE deploy_script
            NO_UNSUPPORTED_PLATFORM_ERROR
        )
    else()
        qt_generate_deploy_app_script(
            TARGET learn
            OUTPUT_SCRIPT deploy_script
            NO_UNSUPPORTED_PLATFORM_ERROR
        )
    endif()
    install(SCRIPT ${deploy_script})
endif()
