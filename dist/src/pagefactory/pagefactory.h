#ifndef PAGEFACTORY_H
#define PAGEFACTORY_H

#include "dcppage.h"
#include "pages.h"
class DcpPage;

class PageFactory
{
public:
    static PageFactory *instance();
    static Pages::Id idOf(DuiApplicationPage *page);
    static Pages::Id refererOf(DuiApplicationPage *page);
    DcpPage* create (Pages::Id pageId);
protected:
    PageFactory();
    DcpPage* createMainPage();	
    DcpPage* createAccountsPage();	
    DcpPage* createAppletPage();	
private:
    static PageFactory* sm_Instance;
};

#endif // PAGEFACTORY_H
