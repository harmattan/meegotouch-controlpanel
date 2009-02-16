#ifndef PAGEFACTORY_H
#define PAGEFACTORY_H

#include "duisettingspage.h"


typedef
enum {
   MAINPAGE = 0,
   ACCOUNTSPAGE=1 
} PageID;

class DuiSettingsPage;

class PageFactory
{
public:
    static PageFactory *instance();
    DuiSettingsPage* create (PageID pageID);
protected:
    PageFactory();
    DuiSettingsPage* createMainPage();	
    DuiSettingsPage* createAccountsPage();	
private:
    static PageFactory* sm_Instance;
};

#endif // PAGEFACTORY_H
