#include "mainwindow.h"
#include <DcpAppletDb>

MainWindow::MainWindow()
{
}

MainWindow::~MainWindow()
{
    DcpAppletDb::instance()->destroy();
}
