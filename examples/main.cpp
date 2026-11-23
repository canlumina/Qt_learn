#include "exampleswindow.h"

#include <QApplication>

/**
 * @brief 启动独立的控件示例浏览器
 * @param argc 命令行参数数量
 * @param argv 命令行参数数组，由运行时提供
 * @return QApplication 事件循环的退出码
 * @note QApplication 必须先于 QWidget 创建；窗口销毁时自动释放子对象。
 */
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    ExamplesWindow window;
    window.show();
    return app.exec();
}
