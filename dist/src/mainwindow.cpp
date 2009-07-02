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

    // --- temporary to test rotating the device ---
    DuiAction* rotateAction = new DuiAction("ROT", page);
    rotateAction->setLocation(DuiAction::ToolBar);
    connect (rotateAction, SIGNAL (triggered()), this, SLOT(onRotateClicked()));
    // ---
    // closeAction
    DuiAction *quitAction = new DuiAction(DcpMain::quitMenuItemText, this);
    quitAction->setLocation(DuiAction::ViewMenu);
    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(closeAllWindows()));

    // Add actions to page
    if (handle.id != Pages::MAIN)
        page->addAction(quitAction);
    page->addAction(rotateAction);

//    page->appear(DuiSceneWindow::DestroyWhenDone); 
    page->appear(DuiSceneWindow::KeepWhenDone); // FIXME
}

/*
 *  only for testing the orientation changei without a device,
 *  not meant to be in final app */
void MainWindow::onRotateClicked()
{
    DuiSceneManager *manager = DuiSceneManager::instance();
    Dui::OrientationAngle angle = manager->orientationAngle();
    if (angle == Dui::Angle270) {
	    angle = Dui::Angle0;
    } else if (angle == Dui::Angle0) {
	    angle = Dui::Angle90;
    } else if (angle == Dui::Angle90) {
	    angle = Dui::Angle180;
    } else if (angle == Dui::Angle180) {
	    angle = Dui::Angle270;
    }
    manager->setOrientationAngle (angle);
}


