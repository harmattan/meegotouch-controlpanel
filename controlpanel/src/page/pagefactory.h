#ifndef PAGEFACTORY_H
#define PAGEFACTORY_H

#include "pages.h"
#include <QObject>

class DcpPage;
class DcpAppletMetadata;
class DcpAppletObject;
class DcpMainPage;
class DcpAppletPage;
class DcpAppletCategoryPage;

/*!
 * Implements methods to create new views (pages), show views and change between
 * views.
 */
class PageFactory : public QObject
{
Q_OBJECT

public:
    static PageFactory *instance ();
    DcpPage* createPage (const PageHandle &handle);
    DcpPage* currentPage() { return m_CurrentPage; }

public slots:
    void appletWantsToStart (
                    const QString &refererName = "", 
                    int            refererWidgetId = -1);
    
    void changePage (
                    const PageHandle &handle, 
                    const QString    &refererName      = "",
                    int               refererWidgetId  = -1);

protected:
    PageFactory ();
    DcpPage* createMainPage ();
    DcpPage* createAppletPage(DcpAppletObject *applet);
    DcpPage* createAppletCategoryPage (PageHandle::PageTypeId pageId);

private slots:
    void mainPageFirstShown (void);

private:
    void registerPage (DcpPage *page);

    static PageFactory     *sm_Instance;
    DcpPage                *m_CurrentPage;
    DcpMainPage            *m_MainPage;
    DcpAppletPage          *m_AppletPage;
    DcpAppletCategoryPage  *m_AppletCategoryPage;
};

#endif
