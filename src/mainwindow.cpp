#include "mainwindow.h"
#include "pagefactory.h"
#include <duinavigationbar.h>

MainWindow::MainWindow()
{
    DuiApplicationPage* mainPage = PageFactory::instance()->create(MAINPAGE);
    addPage(mainPage);
    showPage(mainPage);
}

MainWindow::~MainWindow()
{
}
