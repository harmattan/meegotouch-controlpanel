#include "mainwindow.h"
#include "pagefactory.h"
#include "dcppage.h"
#include "maintranslations.h"
#include <duideviceprofile.h>
#include <QtDebug>
#include <duinavigationbar.h>
#include <duiaction.h>
#include <duiapplication.h>

MainWindow::MainWindow()
{
   Pages::Handle handle = {Pages::MAIN, ""};
  // Pages::Handle handle = {Pages::APPLET, "Language"};
   changePage(handle);
}

void MainWindow::homeClicked()
{
    /*
   Pages::Handle handle = {Pages::MAIN, ""};
   changePage(handle);
*/
   onRotateClicked();
}

void MainWindow::backClicked()
{
    PageFactory::instance()->back();

    /* overrides dui behaviour that it changes to close when switching
       inside a page TODO remove */
    if (PageFactory::instance()->currentPage()->handle().id == Pages::APPLET) {
        navigationBar()->showBackButton();
    }
}

MainWindow::~MainWindow()
{
}

void
MainWindow::changePage(Pages::Handle handle)
{
    DcpPage *page = PageFactory::instance()->create(handle);
    connect (page, SIGNAL(openSubPage(Pages::Handle)), this,
        SLOT(changePage(Pages::Handle)));
    connect(page, SIGNAL(backButtonClicked()), this, SLOT(backClicked()));

    // --- temporary to test rotating the device ---
    DuiAction* rotateAction = new DuiAction("ROT", page);
    connect (rotateAction, SIGNAL (triggered()),
             this, SLOT(onRotateClicked()));
    // ---
    // closeAction
    DuiAction *quitAction = new DuiAction(DcpMain::quitMenuItemText, this);
    quitAction->setLocation(DuiAction::ViewMenu);
    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(closeAllWindows()));
    
    // Add actions to page
    if (handle.id != Pages::MAIN)
        page->addAction(quitAction);
    page->addAction(rotateAction);

    page->appear(DuiSceneWindow::KeepWhenDone); //TODO -> Destroy
    qDebug() << "XXX" << DuiDeviceProfile::instance()->resolution();
}


void MainWindow::onRotateClicked()
{
    DuiDeviceProfile *profile = DuiDeviceProfile::instance();
    static DuiDeviceProfile::DeviceOrientationAngle angle = DuiDeviceProfile::Angle0;
    if (angle == DuiDeviceProfile::Angle270) {
	angle = DuiDeviceProfile::Angle0;
    } else if (angle == DuiDeviceProfile::Angle0) {
	angle = DuiDeviceProfile::Angle90;
    } else if (angle == DuiDeviceProfile::Angle90) {
	angle = DuiDeviceProfile::Angle180;
    } else if (angle == DuiDeviceProfile::Angle180) {
	angle = DuiDeviceProfile::Angle270;
    }
    profile->setOrientationAngle (angle);
}
