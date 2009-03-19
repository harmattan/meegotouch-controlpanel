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
    static DcpPage* page(DuiApplicationPage *page);
    DcpPage* create (Pages::Id pageId, const QString &param);
protected:
    PageFactory();
    DcpPage* createMainPage();	
    DcpPage* createAppletPage(DcpAppletMetadata *metadata);
    DcpPage* createAppletPageFromMostUsed(DcpAppletMetadata *metadata);
    DcpPage* createAppletCategoryPage(const QString& appletCategory);
private:
    static PageFactory* sm_Instance;
};

#endif // PAGEFACTORY_H
