#include "mainwindow.h"

#include "duisettingspage.h"

#include <duinavigationbar.h>


MainWindow::MainWindow()
{
    DuiApplicationPage* mainPage = new DuiSettingsPage();
    addPage(mainPage);

    showPage(mainPage);
}

