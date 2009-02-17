#include "mainwindow.h"
#include "pagefactory.h"
#include <duinavigationbar.h>

MainWindow::MainWindow()
{
    changePage(Pages::MAIN);
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
    if (currentPage())
    	removePage(currentPage());
    showPage(page);
    
}
