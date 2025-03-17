#include "mainwindow.h"
#include <windows.h>
#include <QApplication>
#include "overlaywidget.h"
OverlayWidget *looker_overlay;
int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    OverlayWidget overlay;
    looker_overlay = &overlay;
    looker_overlay->show();
    MainWindow w;
    w.show();
    return a.exec();
}
