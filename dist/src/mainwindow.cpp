#include "mainwindow.h"
#include <PageFactory>
#include <DcpAppletDb>

MainWindow::MainWindow()
{
   Pages::Handle handle = {Pages::MAIN, ""};
   PageFactory::instance()->changePage(handle);
}

MainWindow::~MainWindow()
{
	DcpAppletDb::instance()->destroy();
}
