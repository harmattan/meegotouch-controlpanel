#include "mainwindow.h"
#include <DcpAppletDb>

MainWindow::MainWindow(): DuiApplicationWindow()
{
}

MainWindow::~MainWindow()
{
    DcpAppletDb::instance()->destroy();
}
