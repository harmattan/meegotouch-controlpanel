#include "mainwindow.h"
#include "pagefactory.h"
#include "dcppage.h"
#include <duinavigationbar.h>
#include <duideviceprofile.h>
#include <QtDebug>

MainWindow::MainWindow():m_CurrentPage(NULL)
{
   connect(navigationBar(), SIGNAL(homeClicked()), this, SLOT(homeClicked())); 
   connect(navigationBar(), SIGNAL(backClicked()), this, SLOT(backClicked())); 
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
    DcpPage* page = PageFactory::page(currentPage());
    changePage(page->referer());
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
    connect (page, SIGNAL(openSubPage(Pages::Handle)), this,
        SLOT(changePage(Pages::Handle)));
    qDebug() << "XXX" << Q_FUNC_INFO << (void*)m_CurrentPage << "->" << (void*)page;
    page->appearNow(DuiSceneWindow::KeepWhenDone);
    if (m_CurrentPage) {
        if (page->referer().id == Pages::NOPAGE)
            page->setReferer(m_CurrentPage->handle());
        m_CurrentPage->disappear();
    }
/*
    page->handle().id == Pages::MAIN ?
       navigationBar()->showCloseButton()
    :
       navigationBar()->showBackButton();

    navigationBar()->setViewMenuButtonText(page->title());
*/
    m_CurrentPage = page;
}


void MainWindow::onRotateClicked()
{
    DuiDeviceProfile *profile = DuiDeviceProfile::instance();
   // m_Category->onOrientationChange(profile->orientation());

    if ( profile->orientation() == Dui::Portrait ) {
        qDebug() << "mode changes to Angle0";
        profile->setOrientationAngle (DuiDeviceProfile::Angle0);
    } else {
        qDebug() << "mode changes to Angle90";
        profile->setOrientationAngle (DuiDeviceProfile::Angle90);
    }
}
