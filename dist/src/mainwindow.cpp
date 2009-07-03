#include "mainwindow.h"
#include "pagefactory.h"
#include "dcppage.h"
#include "maintranslations.h"
#include <duiscenemanager.h>
#include <QtDebug>
#include <duiaction.h>
#include <duiapplication.h>

#include "dcpappletdb.h"

MainWindow::MainWindow()
{
   Pages::Handle handle = {Pages::MAIN, ""};
//   Pages::Handle handle = {Pages::APPLET, "DateTime"};
   changePage(handle);
}

void MainWindow::backClicked()
{
    PageFactory::instance()->back();
}

MainWindow::~MainWindow()
{
	DcpAppletDb::instance()->destroy();
}

void MainWindow::changePage(Pages::Handle handle)
{

    DcpPage *page = PageFactory::instance()->create(handle);
    connect (page, SIGNAL(openSubPage(Pages::Handle)), this, SLOT(changePage(Pages::Handle)));
    connect(page, SIGNAL(backButtonClicked()), this, SLOT(backClicked()));

    // closeAction
    DuiAction *quitAction = new DuiAction(DcpMain::quitMenuItemText, this);
    quitAction->setLocation(DuiAction::ViewMenu);
    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(closeAllWindows()));

    // Add actions to page
    if (handle.id != Pages::MAIN)
        page->addAction(quitAction);

//    page->appear(DuiSceneWindow::DestroyWhenDone); 
    page->appear(DuiSceneWindow::KeepWhenDone); // FIXME
}

