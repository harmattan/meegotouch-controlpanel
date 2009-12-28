#ifndef PAGEFACTORY_H
#define PAGEFACTORY_H

#include "pages.h"
#include <QObject>

class DcpPage;
class DcpAppletMetadata;
class DcpMainPage;
class DcpAppletPage;
class DcpAppletCategoryPage;

class PageFactory : public QObject
{
    Q_OBJECT
public:
    static PageFactory *instance();
    DcpPage* create (const PageHandle &handle);
    DcpPage* currentPage() {return m_CurrentPage;}
    void initPage(DcpPage* page);

public slots:
    void appletWantsToStart ();
    void appletWantsToStartWithReferer (const QString &, int);
    
    void changePage (PageHandle handle);
    void changePageWithReferer (
		    const PageHandle &handle, 
		    const QString       &refererName,
		    int                  refererWidgetId);

protected:
    PageFactory ();
    DcpPage* createMainPage ();	
    DcpPage* createAppletPage (DcpAppletMetadata *metadata);
    DcpPage* createAppletCategoryPage (PageHandle::PageTypeId pageId);

private:
    static PageFactory  *sm_Instance;
    DcpPage             *m_CurrentPage;
    DcpMainPage         *m_MainPage;
    DcpAppletPage       *m_AppletPage;
    DcpAppletCategoryPage *m_AppletCategoryPage;
};

#endif
