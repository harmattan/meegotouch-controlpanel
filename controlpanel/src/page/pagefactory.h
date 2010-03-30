#ifndef PAGEFACTORY_H
#define PAGEFACTORY_H

#include "pages.h"
#include <QObject>
#include <QList>

class DuiApplicationPage;
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
    static void destroy();
    DcpPage* createPage (const PageHandle &handle);
    DcpPage* currentPage ();

public slots:
    void appletWantsToStart (int widgetId = -1);

    void changePage (const PageHandle &handle);

protected:
    PageFactory ();
    DcpPage* createMainPage ();
    DcpPage* createAppletPage(PageHandle& applet);
    DcpPage* createAppletCategoryPage (PageHandle::PageTypeId pageId);

private slots:
    void mainPageFirstShown (void);
    void pageChanged (DuiApplicationPage *page);

private:
    bool tryOpenPageBackward (const PageHandle &handle);
    void registerPage (DcpPage *page);

    static PageFactory     *sm_Instance;
    DcpMainPage            *m_MainPage;
    DcpAppletCategoryPage  *m_AppletCategoryPage;
    QList<DuiApplicationPage *> m_Pages;
    // for testability
    friend class Ut_PageFactory;
};

#endif

