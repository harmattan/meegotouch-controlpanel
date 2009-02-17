#include "pagefactory.h"
#include "duisettingsmainpage.h"
#include "duisettingsaccountspage.h"
#include <QtDebug>
PageFactory *PageFactory::sm_Instance =0;

PageFactory::PageFactory()
{}

PageFactory*
PageFactory::instance()
{
    if (!sm_Instance)
        sm_Instance = new PageFactory();
    return sm_Instance;
}
DuiSettingsPage* 
PageFactory::create(Pages::Id pageID)
{
    DuiSettingsPage *page=0;
    switch (pageID)
      {
	case Pages::MAIN:
            page = createMainPage();
            break;
        case Pages::ACCOUNTS:
            page = createAccountsPage();
            break;
	default:
            qWarning() << "Bad page ID: " << pageID;
	    page=0;
      }  
    return page;
}

DuiSettingsPage* 
PageFactory::createMainPage()
{
    return new DuiSettingsMainPage();
}

DuiSettingsPage* 
PageFactory::createAccountsPage()
{
    return new DuiSettingsAccountPage();
}
