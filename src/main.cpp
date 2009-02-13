#include "mainwindow.h"

#include <DuiApplication>
#include <duitheme.h>


int main(int argc, char *argv[])
{
    DuiApplication a(argc, argv);

    DuiTheme::loadCSS("duicontrolpanel.css");
    MainWindow win;
    win.show();

    return a.exec();
}
