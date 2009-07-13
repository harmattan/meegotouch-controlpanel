#include "mainwindow.h"
#include "pagefactory.h"
#include <duiscenemanager.h>
#include <QtDebug>
#include <duiaction.h>
#include <duiapplication.h>

#include "dcpappletdb.h"

MainWindow::MainWindow()
{
   Pages::Handle handle = {Pages::MAIN, ""};
//   Pages::Handle handle = {Pages::APPLET, "DateTime"};
   PageFactory::instance()->changePage(handle);
}

MainWindow::~MainWindow()
{
	DcpAppletDb::instance()->destroy();
}


