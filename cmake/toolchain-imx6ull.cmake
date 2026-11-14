# i.MX6ULL（ARMv7 hard-float）交叉编译工具链
#
# 用法：
#   cmake -S . -B build/imx6ull -G Ninja -DCMAKE_TOOLCHAIN_FILE=cmake/toolchain-imx6ull.cmake
#   cmake --build build/imx6ull
#
# 若 buildroot 输出目录换了位置，覆盖下面这个变量即可：
#   -DBUILDROOT_OUTPUT=/path/to/buildroot/output

set(BUILDROOT_OUTPUT
    "/home/yangcan/Workspaces/imx6ull/buildroot/buildroot-2019.02.6/output"
    CACHE PATH "buildroot 的 output 目录")

set(BUILDROOT_HOST "${BUILDROOT_OUTPUT}/host" CACHE PATH "buildroot 的 host 目录（含交叉编译器）")
set(BUILDROOT_SYSROOT "${BUILDROOT_HOST}/arm-buildroot-linux-gnueabihf/sysroot"
    CACHE PATH "buildroot 的 target sysroot（含 ARM 版 Qt5 头文件与库）")

if(NOT EXISTS "${BUILDROOT_HOST}/bin/arm-linux-gnueabihf-g++")
    message(FATAL_ERROR
        "找不到交叉编译器：${BUILDROOT_HOST}/bin/arm-linux-gnueabihf-g++\n"
        "请用 -DBUILDROOT_OUTPUT=... 指定 buildroot 的 output 目录。")
endif()

set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR arm)

set(CMAKE_SYSROOT "${BUILDROOT_SYSROOT}")

set(CMAKE_C_COMPILER   "${BUILDROOT_HOST}/bin/arm-linux-gnueabihf-gcc")
set(CMAKE_CXX_COMPILER "${BUILDROOT_HOST}/bin/arm-linux-gnueabihf-g++")

# buildroot 编译 Qt 时用的就是这组参数，保持一致可避免 ABI / 宏差异
set(CMAKE_C_FLAGS_INIT   "-D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64 -Os")
set(CMAKE_CXX_FLAGS_INIT "-D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64 -Os")

# 让 find_package(Qt5) 能搜到 sysroot 里的 Qt5 CMake 配置
set(CMAKE_FIND_ROOT_PATH "${BUILDROOT_SYSROOT}")
set(CMAKE_PREFIX_PATH "${BUILDROOT_SYSROOT}/usr")

# 程序（cmake、ninja、moc 等宿主工具）用本机的，库/头文件/包配置只在 sysroot 里找
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

# Qt5 的 moc/uic/rcc 需要宿主版（buildroot 已经编好了）
set(QT_HOST_PATH "${BUILDROOT_HOST}" CACHE PATH "宿主版 Qt 工具链目录（moc/uic/rcc）")

set(PKG_CONFIG_SYSROOT_DIR "${BUILDROOT_SYSROOT}")
set(ENV{PKG_CONFIG_SYSROOT_DIR} "${BUILDROOT_SYSROOT}")
set(ENV{PKG_CONFIG_PATH} "${BUILDROOT_SYSROOT}/usr/lib/pkgconfig:${BUILDROOT_SYSROOT}/usr/share/pkgconfig")
