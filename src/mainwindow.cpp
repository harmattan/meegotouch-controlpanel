#include "mainwindow.h"
#include "pagefactory.h"
#include <duinavigationbar.h>

MainWindow::MainWindow() : m_Referer(Pages::NOPAGE)
{
   connect(navigationBar(), SIGNAL(homeClicked()), this, SLOT(homeClicked())); 
   connect(navigationBar(), SIGNAL(backClicked()), this, SLOT(backClicked())); 
   changePage(Pages::MAIN);
}

void MainWindow::homeClicked()
{
   changePage(Pages::MAIN);
}

void MainWindow::backClicked()
{
  if (m_Referer == Pages::NOPAGE)
        return;
   changePage(m_Referer);
}

MainWindow::~MainWindow()
{
}

void
MainWindow::changePage(Pages::Id pageId)
{

  if (pageId == Pages::NOPAGE)
        return;
    DuiApplicationPage* page = PageFactory::instance()->create(pageId);
    addPage(page);
    connect (page, SIGNAL(openSubPage(Pages::Id)), this, 
		SLOT(changePage(Pages::Id)));
    qDebug() << Q_FUNC_INFO;
    DuiApplicationPage* oldPage = currentPage();
    if (oldPage)
      {
        m_Referer = PageFactory::idOf(oldPage);
      	removePage(oldPage);
      }
    PageFactory::idOf(page) == Pages::MAIN ?
       navigationBar()->showCloseButton()
    :
       navigationBar()->showBackButton();
    showPage(page);
    
}
