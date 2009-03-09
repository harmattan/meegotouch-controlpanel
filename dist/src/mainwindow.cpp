#include "mainwindow.h"
#include "pagefactory.h"
#include "dcppage.h"
#include <duinavigationbar.h>
#include <duideviceprofile.h>

MainWindow::MainWindow() : m_Referer(Pages::NOPAGE)
{
   connect(navigationBar(), SIGNAL(homeClicked()), this, SLOT(homeClicked())); 
   connect(navigationBar(), SIGNAL(backClicked()), this, SLOT(backClicked())); 
   changePage(Pages::MAIN);
}

void MainWindow::homeClicked()
{
//   changePage(Pages::MAIN);
   onRotateClicked();
}

void MainWindow::backClicked()
{
   changePage(PageFactory::refererOf(currentPage()));
}

MainWindow::~MainWindow()
{
}

void
MainWindow::changePage(Pages::Id pageId)
{

  if (pageId == Pages::NOPAGE)
        return;
    DcpPage* page = PageFactory::instance()->create(pageId);
    addPage(page);
    connect (page, SIGNAL(openSubPage(Pages::Id)), this, 
		SLOT(changePage(Pages::Id)));
    qDebug() << Q_FUNC_INFO;
    DcpPage* oldPage = qobject_cast<DcpPage*>(currentPage());
    if (oldPage)
      {
	if (page->referer() == Pages::NOPAGE)
	    page->setReferer(oldPage->pageId());      
	removePage(oldPage);
      }
    page->pageId() == Pages::MAIN ?
       navigationBar()->showCloseButton()
    :
       navigationBar()->showBackButton();
    showPage(page);
    
}
void MainWindow::onRotateClicked()
{
    DuiDeviceProfile *profile = DuiDeviceProfile::instance();
   // m_Category->onOrientationChange(profile->orientation());

    if ( profile->orientation() == Dui::Portrait ) {
        qDebug() << "XXX mode changes to Angle0";
        profile->setOrientationAngle (DuiDeviceProfile::Angle0);
    } else {
        qDebug() << "XXX mode changes to Angle90";
        profile->setOrientationAngle (DuiDeviceProfile::Angle90);
    }
}
