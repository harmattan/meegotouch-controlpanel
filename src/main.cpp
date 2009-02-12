#include <DuiApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    DuiApplication a(argc, argv);

    MainWindow win;
    win.show();

    return a.exec();
}
