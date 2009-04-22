#ifndef PAGEFACTORY_H
#define PAGEFACTORY_H

#include "dcppage.h"
#include "pages.h"
class DcpPage;
class DcpAppletMetadata;
class DcpAppletLoader;
class DcpWidget;
class PageFactory : public QObject
{
    Q_OBJECT
public:
    static PageFactory *instance();
    static DcpPage* page(DuiApplicationPage *page);
    DcpPage* create (Pages::Handle &handle);
    DcpPage* currentPage(){return m_CurrentPage;}
    void back();
protected:
    PageFactory();
    DcpPage* createMainPage();	
    DcpPage* createAppletPage(DcpAppletMetadata *metadata);
    DcpPage* createAppletPageFromCategory(DcpAppletMetadata *metadata);
    DcpPage* createAppletPageFromMostUsed(DcpAppletMetadata *metadata);
    DcpPage* createAppletCategoryPage(const QString& appletCategory);
private:
    DcpPage *m_CurrentPage;
    static PageFactory* sm_Instance;
};

#endif // PAGEFACTORY_H
