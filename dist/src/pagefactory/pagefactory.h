#ifndef PAGEFACTORY_H
#define PAGEFACTORY_H

#include "pages.h"
#include <QObject>

class DcpPage;
class DcpAppletMetadata;
class DcpAppletLoader;
class DcpWidget;
class DcpMainPage;
class DcpAppletPage;
class DcpAppletCategoryPage;

class PageFactory : public QObject
{
    Q_OBJECT
public:
    static PageFactory *instance();
    DcpPage* create (Pages::Handle &handle);
    DcpPage* currentPage(){return m_CurrentPage;}
    void initPage(DcpPage* page);

public slots:
    void changePage(Pages::Handle handle);

protected:
    PageFactory();
    DcpPage* createMainPage();	
    DcpPage* createAppletPage(DcpAppletMetadata *metadata);
    DcpPage* createAppletPageFromCategory(DcpAppletMetadata *metadata);
    DcpPage* createAppletPageFromMostUsed(DcpAppletMetadata *metadata);
    DcpPage* createAppletCategoryPage(const QString& appletCategory);

private:
    static PageFactory* sm_Instance;

    DcpPage *m_CurrentPage;

    DcpMainPage *m_MainPage;
    DcpAppletPage *m_AppletPage;
    DcpAppletCategoryPage *m_AppletCategoryPage;
};

#endif // PAGEFACTORY_H

