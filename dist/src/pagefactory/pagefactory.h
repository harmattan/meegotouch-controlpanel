#ifndef PAGEFACTORY_H
#define PAGEFACTORY_H

#include "dcppage.h"
#include "pages.h"
class DcpPage;
class DcpAppletMetadata;
class PageFactory
{
public:
    static PageFactory *instance();
    static Pages::Id idOf(DuiApplicationPage *page);
    static Pages::Id refererOf(DuiApplicationPage *page);
    DcpPage* create (Pages::Id pageId, const QString &param);
protected:
    PageFactory();
    DcpPage* createMainPage();	
    DcpPage* createAccountsPage();	
    DcpPage* createAppletPage(DcpAppletMetadata *metadata);	
    DcpPage* createAppletCategoryPage(const QString& appletCategory);
private:
    static PageFactory* sm_Instance;
};

#endif // PAGEFACTORY_H
