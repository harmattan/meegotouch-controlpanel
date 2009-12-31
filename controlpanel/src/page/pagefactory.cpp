/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */

#include "pagefactory.h"

#include <DcpPage>
#include <DcpMainPage>
#include <DcpAppletPage>
#include <DcpAppletDb>
#include <DcpAppletIf>
#include <DcpAppletMetadata>
#include <DcpAppletCategoryPage>
#include <MainTranslations>

#include <DuiApplication>
#include <DuiAction>

#define DEBUG
#include "dcpdebug.h"


PageFactory *PageFactory::sm_Instance = 0;

PageFactory::PageFactory (): 
    QObject (),
    m_CurrentPage (0), 
    m_MainPage (0), 
    m_AppletPage (0), 
    m_AppletCategoryPage (0)
{
    DcpAppletMetadataList list;

    /*
     * Whenever someone wants an applet to be activated (started, shown on the
     * screen atc.) a signal is sent to the applet's metadata. Then the applets
     * metadata will send a signal, so the pagefactory can open a new page for
     * it.
     *
     * If an applet wants to start up an other applet we also got a signal here
     * so we can start up the applet. In this case we will have an external
     * referer for the applets main page.
     */
    list = DcpAppletDb::instance()->list();
    foreach (DcpAppletMetadata *item, list) {
        DCP_DEBUG ("*** applet '%s'", DCP_STR (item->name()));
        connect (item, SIGNAL (activate ()),
                this, SLOT (appletWantsToStart ()));
        connect (item, SIGNAL (activateWithReferer (const QString &, int)),
                this, SLOT (appletWantsToStart (const QString &, int)));
    }
}

PageFactory * 
PageFactory::instance ()
{
    if (!sm_Instance)
        sm_Instance = new PageFactory();
    return sm_Instance;
}

DcpPage* 
PageFactory::createPage (
        const PageHandle &handle)
{
    DcpPage *page = 0;

    DCP_DEBUG ("****************************");
    DCP_DEBUG ("*** handle = %s", DCP_STR (handle.getStringVariant()));
    DCP_DEBUG ("****************************");
    switch (handle.id) {
        case PageHandle::NOPAGE:
	    case PageHandle::MAIN:
            /*
             * Creating the main page. If the ID is is PageHandle::NOPAGE we
             * also create the main page, for which we can handle pages that has
             * no valid referer. These pages are going to open the main page
             * when closed.
             */
            DCP_DEBUG ("## MAIN ##");
            page = createMainPage();
            break;

        case PageHandle::APPLETCATEGORY: 
            // when coming back
            DCP_DEBUG ("## APPLETCATEGORY ##");
            Q_ASSERT (m_AppletCategoryPage);
            page = m_AppletCategoryPage;
            break;

        case PageHandle::APPLET:
            DCP_DEBUG ("## APPLET ##");
            page = createAppletPage (
			    DcpAppletDb::instance()->applet (handle.param));
            break;

        default:
            DCP_DEBUG ("## CATEGORY_PAGEID_XXX ##");
            Q_ASSERT(handle.id > PageHandle::CATEGORY_PAGEID_START
                     && handle.id < PageHandle::CATEGORY_PAGEID_END);
            page = createAppletCategoryPage (handle.id);
    }

    if (page) {
        page->setHandle (handle);

        if (m_CurrentPage)
            m_CurrentPage->disconnectSignals ();

        page->connectSignals ();

        /*
         * But we did this already in the createAppletPage() function! This
         * design should be better...
         */
        if (handle.id != PageHandle::APPLET)
    		if (page->isContentCreated ())
                page->reload ();
        
        m_CurrentPage = page;
    }

    return page;
}

DcpPage *
PageFactory::createMainPage ()
{
    if (!m_MainPage) {
        m_MainPage = new DcpMainPage ();
        registerPage (m_MainPage);
    }

    return m_MainPage;
}

/*!
 * Creates an applet page for the default widget of the applet variant
 * represented by the metadata. Also will try to re-use the already existing
 * applet page referenced by the m_AppletPage class member.
 */
DcpPage *
PageFactory::createAppletPage (
		DcpAppletMetadata   *metadata)
{
    /*
     * If we have not created the applet page yet we do that, otherwise we set
     * the metadata for the existing page.
     */
    if (!m_AppletPage) {
        m_AppletPage = new DcpAppletPage (metadata);
        registerPage (m_AppletPage);
    } else {
        m_AppletPage->setMetadata (metadata);
    }

    m_AppletPage->refreshContent ();
    
    if (!m_AppletPage->hasWidget() && !m_AppletPage->hasError()) {
        // the applet does not provide a page (e.g. just a dialog)
        return 0;
    } else {
        return m_AppletPage;
    }
}

DcpPage *
PageFactory::createAppletCategoryPage (
        PageHandle::PageTypeId id)
{
    const DcpCategoryInfo *info;
    int                    n;

    DCP_DEBUG ("*** id = %d", (int) id);

    info = dcp_find_category_info (id);
    if (!info) {
        DCP_WARNING ("Category info for page type %d not found.", (int) id);
        return 0;
    }

    if (!m_AppletCategoryPage){
        m_AppletCategoryPage = new DcpAppletCategoryPage (info->appletCategory);
        registerPage (m_AppletCategoryPage);
    } else {
        m_AppletCategoryPage->setAppletCategory (info->appletCategory);
    }

    m_AppletCategoryPage->setTitle (qtTrId (info->titleId));
    
    return m_AppletCategoryPage;
}

/*!
 * Creates a new page and sets as the current page. If the refererName is not
 * empty the referer for the new page will be set.
 *
 * FIXME: This function assumes that the referer is an applet page.
 */
void 
PageFactory::changePage (
        const PageHandle     &handle,
        const QString        &refererName,
        int                   refererWidgetId)
{
    DcpPage  *page;

    DCP_DEBUG ("Creating page '%s'/%d for referer '%s'/%d",
            DCP_STR (handle.param), handle.id,
            DCP_STR (refererName), refererWidgetId);
    /*
     * Creating the page with the given handle.
     */
    page = createPage (handle);
    if (!page)
        return;

    /*
     * If we have a referer we set it now.
     */
    if (!refererName.isEmpty()) {
        PageHandle referer (PageHandle::APPLET, 
                refererName, refererWidgetId);

        page->setReferer (referer);
    }
    
    /*
     * Time to show the new page.
     */
    page->appearNow (DuiSceneWindow::KeepWhenDone);
}

void
PageFactory::appletWantsToStart (
        const QString &refererName, 
        int            refererWidgetId)
{
    DcpAppletMetadata *metadata = qobject_cast<DcpAppletMetadata *> (sender());

    Q_ASSERT (metadata != 0);
    DCP_DEBUG ("Applet '%s' wants to start.", DCP_STR(metadata->name()));
    PageHandle handle (
            PageHandle::APPLET,
            metadata->name(),
            metadata->getMainWidgetId ());

    if (refererName.isEmpty())
        changePage (handle);
    else
        changePage (handle, refererName, refererWidgetId);
}

/*!
 * This function does all the common stuff that is needed to be done when a new 
 * page is created. The function connects to signals and adds the 'Quit' action
 * to the menu of the page.
 */
void 
PageFactory::registerPage (
        DcpPage* page)
{
    connect (page, SIGNAL(openSubPage (const PageHandle &)), 
        this, SLOT(changePage(const PageHandle &)));

    connect (
        page, 
        SIGNAL (openSubPageWithReferer (const PageHandle &, const QString &, int)), 
        this, 
        SLOT (changePage (const PageHandle &, const QString &, int)));

    if (page != m_MainPage) {
        // closeAction TODO XXX on language change, move into to the page?
        DuiAction *quitAction = new DuiAction (
                qtTrId(DcpMain::quitMenuItemTextId), page);
        /* FIXME DuiAction::ApplicationMenu */
        quitAction->setLocation((DuiAction::Location) 4);
        
        connect(quitAction, SIGNAL(triggered()), qApp, SLOT(closeAllWindows()));

        // Add actions to page
        page->addAction(quitAction);
    }
}


