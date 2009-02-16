#include "pagefactory.h"
#include "duisettingsmainpage.h"

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
PageFactory::create(PageID pageID)
{
    DuiSettingsPage *page=0;
    switch (pageID)
      {
        case MAINPAGE:
            page = createMainPage();
            break;
        case ACCOUNTSPAGE:
            page = createAccountsPage();
            break;
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
    return 0; // new DuiSettingsAccountsPage();
}
