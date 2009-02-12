#include "mainwindow.h"

#include <DuiApplication>
#include <duitheme.h>


int main(int argc, char *argv[])
{
    DuiApplication a(argc, argv);

    DuiTheme::loadCSS("application.css");
    MainWindow win;
    win.show();

    return a.exec();
}
