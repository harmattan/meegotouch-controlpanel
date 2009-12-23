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
                this, SLOT (appletWantsToStartWithReferer (const QString &, int)));
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
PageFactory::create (
        const PageHandle &handle)
{
    DcpPage *page = 0;

    DCP_DEBUG ("Creating page %s", DCP_STR (handle.getStringVariant()));
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
            if (page)
                page->setHandle (handle);
    }

    if (page) {
        page->setHandle (handle);

        if (m_CurrentPage)
            m_CurrentPage->disconnectSignals ();

        page->connectSignals ();

		if (page->isContentCreated())
            page->reload();
        
        m_CurrentPage = page;
    }

    return page;
}

DcpPage* PageFactory::createMainPage ()
{
    if (!m_MainPage) {
        m_MainPage = new DcpMainPage ();
        initPage (m_MainPage);
    }

    return m_MainPage;
}

DcpPage *
PageFactory::createAppletPage (
		DcpAppletMetadata *metadata)
{
    if (!m_AppletPage) {
        m_AppletPage = new DcpAppletPage(metadata);
        initPage (m_AppletPage);
    } else {
        m_AppletPage->setMetadata (metadata);
    }

    // page has to be loaded to know if the applet provides page or not
    if (m_AppletPage->isContentCreated ()) {
        m_AppletPage->reload ();
    } else {
        m_AppletPage->createContent ();
    }

    if (!m_AppletPage->hasWidget() && !m_AppletPage->hasError()) {
        // the applet does not provide a page (eg. just a dialog)
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

    for (n = 0; ; ++n) {
        info = & DcpMain::CategoryInfos[n];

        if (info->titleId == 0) {
            DCP_DEBUG ("Category info for page type %d not found.", (int) id);
            return 0;
        }

        if (info->subPageId == id)
            break;
    }

    if (!m_AppletCategoryPage){
        m_AppletCategoryPage = new DcpAppletCategoryPage (info->appletCategory);
        initPage (m_AppletCategoryPage);
    } else {
        m_AppletCategoryPage->setAppletCategory (info->appletCategory);
    }

    m_AppletCategoryPage->setTitle (qtTrId (info->titleId));
    
    return m_AppletCategoryPage;
}

void 
PageFactory::changePage (
        PageHandle handle)
{
    DcpPage *page = create (handle);

    DCP_DEBUG ("*** handle = %s", DCP_STR (handle.getStringVariant ()));
    if (page) {
        page->appear (DuiSceneWindow::KeepWhenDone);
    }
}

void 
PageFactory::changePageWithReferer (
        const PageHandle     &handle,
        const QString        &refererName,
        int                   refererWidgetId)
{
    DCP_DEBUG ("Creating page '%s'/%d for referer '%s'/%d",
            DCP_STR (handle.param), handle.id,
            DCP_STR (refererName), refererWidgetId);

    DcpPage *page = create (handle);

    if (page) {
        PageHandle referer (PageHandle::APPLET, 
                refererName, refererWidgetId);

        page->setReferer (referer);
        page->appearNow (DuiSceneWindow::KeepWhenDone);
    }
}

/*
 * FIXME: the PageFactory::appletWantsToStart and the 
 * PageFactory::appletWantsToStartWithReferer could be implemented with default
 * parameters or something.
 */
void
PageFactory::appletWantsToStart ()
{
    DcpAppletMetadata *metadata = qobject_cast<DcpAppletMetadata *> (sender());

    Q_ASSERT (metadata != 0);
    DCP_DEBUG ("Applet '%s' wants to start.", DCP_STR(metadata->name()));
    PageHandle handle (
            PageHandle::APPLET,
            metadata->name(),
            metadata->getMainWidgetId ());

    changePage (handle);
}

void
PageFactory::appletWantsToStartWithReferer (
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

    changePageWithReferer (handle, refererName, refererWidgetId);
}

void 
PageFactory::initPage (
        DcpPage* page)
{
    connect (page, SIGNAL(openSubPage (PageHandle)), 
            this, SLOT(changePage(PageHandle)));

    connect (
            page, 
            SIGNAL (openSubPageWithReferer(const PageHandle &, const QString &, int)), 
            this, 
            SLOT (changePageWithReferer(const PageHandle &, const QString &, int)));

    if (page != m_MainPage) {
        // closeAction TODO XXX on language change, move into to the page?
        DuiAction *quitAction = new DuiAction(qtTrId(DcpMain::quitMenuItemTextId), page);
        quitAction->setLocation((DuiAction::Location)4 /* FIXME DuiAction::ApplicationMenu */);
        
        connect(quitAction, SIGNAL(triggered()), qApp, SLOT(closeAllWindows()));

        // Add actions to page
        page->addAction(quitAction);
    }
}


