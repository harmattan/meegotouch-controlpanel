#ifndef PAGEFACTORY_H
#define PAGEFACTORY_H

#include "duisettingspage.h"
#include "pages.h"
class DuiSettingsPage;

class PageFactory
{
public:
    static PageFactory *instance();
    static Pages::Id idOf(DuiApplicationPage *page);
    DuiSettingsPage* create (Pages::Id pageId);
protected:
    PageFactory();
    DuiSettingsPage* createMainPage();	
    DuiSettingsPage* createAccountsPage();	
private:
    static PageFactory* sm_Instance;
};

#endif // PAGEFACTORY_H
