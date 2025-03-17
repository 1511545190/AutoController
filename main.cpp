#include "mainwindow.h"
#include <windows.h>
#include <QApplication>
#include <memory>
#include "overlaywidget.h"
// 声明全局指针为智能指针（避免内存泄漏，对象生命周期持续到程序退出
std::unique_ptr<OverlayWidget> looker_overlay;
// 通过std::unique_ptr自动管理内存，无需手动delete
int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    OverlayWidget overlay;
    looker_overlay = std::make_unique<OverlayWidget>(); // 堆上创建
    looker_overlay->show();

    MainWindow w;
    w.show();
    return a.exec();
}
