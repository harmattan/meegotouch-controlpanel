#include "mainwindow.h"
#include "pagefactory.h"
#include "dcppage.h"
#include <duideviceprofile.h>
#include <QtDebug>
#include "dcpappletpage.h"

MainWindow::MainWindow():m_CurrentPage(NULL)
{
   connect(PageFactory::instance(), SIGNAL(changePage(DcpPage*)), 
        this, SLOT(appletChangePage(DcpPage*))); 
   Pages::Handle handle = {Pages::MAIN, ""};
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
    Q_ASSERT(m_CurrentPage);
    bool change = true;
    if (m_CurrentPage->handle().id == Pages::APPLET
        || m_CurrentPage->handle().id == Pages::APPLETFROMMOSTUSED)
         change = PageFactory::instance()->backFromApplet();
    if (change)
        changePage(m_CurrentPage->referer());
}

MainWindow::~MainWindow()
{
}

void
MainWindow::changePage(Pages::Handle handle)
{
    if (handle.id == Pages::NOPAGE)
        return;

    DcpPage* page = PageFactory::instance()->create(handle.id, handle.param);
    qDebug() << "XXXX changePage" << (void*) page;
    connect (page, SIGNAL(openSubPage(Pages::Handle)), this,
        SLOT(changePage(Pages::Handle)));
    connect(page, SIGNAL(backButtonClicked()), this, SLOT(backClicked()));
//    page->appearNow(DuiSceneWindow::DestroyWhenDone); TODO
    page->appearNow(DuiSceneWindow::KeepWhenDone);
    if (m_CurrentPage) {
        if (page->referer().id == Pages::NOPAGE)
            page->setReferer(m_CurrentPage->handle());
    }

    m_CurrentPage = page;
}


void MainWindow::onRotateClicked()
{
    DuiDeviceProfile *profile = DuiDeviceProfile::instance();

    if ( profile->orientation() == Dui::Portrait ) {
        qDebug() << "mode changes to Angle0";
        profile->setOrientationAngle (DuiDeviceProfile::Angle0);
    } else {
        qDebug() << "mode changes to Angle90";
        profile->setOrientationAngle (DuiDeviceProfile::Angle90);
    }
}


void
MainWindow::appletChangePage(DcpPage *page)
{
    Q_ASSERT(page);
    m_CurrentPage = page;
    qDebug() << "XXXX appletChangePage" << (void*) page;
    connect(page, SIGNAL(backButtonClicked()), this, SLOT(backClicked()));
//    page->appearNow(DuiSceneWindow::DestroyWhenDone); TODO
    page->appearNow(DuiSceneWindow::KeepWhenDone);
}

