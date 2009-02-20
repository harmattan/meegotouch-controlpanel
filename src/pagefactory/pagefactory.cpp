#include "pagefactory.h"
#include "duisettingsmainpage.h"
#include "duisettingsaccountspage.h"
#include "duisettingsappletpage.h"
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

Pages::Id
PageFactory::idOf(DuiApplicationPage *page)
{
    return qobject_cast<DuiSettingsPage*>(page)->pageId();
}
DuiSettingsPage* 
PageFactory::create(Pages::Id pageId)
{
    DuiSettingsPage *page=0;
    switch (pageId)
      {
	case Pages::MAIN:
            page = createMainPage();
            break;
        case Pages::ACCOUNTS:
            page = createAccountsPage();
            break;
        case Pages::APPLET:
            page = createAppletPage();
            break;
	default:
            qWarning() << "Bad page ID: " << pageId;
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

DuiSettingsPage* 
PageFactory::createAppletPage()
{
    return new DuiSettingsAppletPage();
}
