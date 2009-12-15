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

PageFactory::PageFactory(): QObject(),
    m_CurrentPage(0), m_MainPage(0), m_AppletPage(0), m_AppletCategoryPage(0)
{
}

PageFactory* PageFactory::instance()
{
    if (!sm_Instance)
        sm_Instance = new PageFactory();
    return sm_Instance;
}

DcpPage* 
PageFactory::create (
        const Pages::Handle &handle)
{
    DcpPage *page=0;

    DCP_DEBUG ("Creating page '%s'/%d", DCP_STR (handle.param), handle.id);
    switch (handle.id) {
        case Pages::NOPAGE:
	    case Pages::MAIN:
            /*
             * Creating the main page. If the ID is is Pages::NOPAGE we also
             * create the main page, for which we can handle pages that has no
             * valid referer. These pages are going to open the main page when
             * closed.
             */
            page = createMainPage();
            break;

        case Pages::APPLETCATEGORY: // when coming back
            Q_ASSERT(m_AppletCategoryPage);
            page = m_AppletCategoryPage;
            break;

        case Pages::APPLET:
            page = createAppletPage (
			    DcpAppletDb::instance()->applet (handle.param));
            if (page)
                page->setHandle (handle);
            break;

        default:
            Q_ASSERT(handle.id > Pages::CATEGORY_PAGEID_START
                     && handle.id < Pages::CATEGORY_PAGEID_END);
            page = createAppletCategoryPage(handle.id);
    }

    if (page) {
        if (m_CurrentPage)
            m_CurrentPage->disconnectSignals();

        page->connectSignals();

		if (page->isContentCreated())
            page->reload();
        
        #if 0
        if (m_CurrentPage && page->referer().id == Pages::NOPAGE)
                page->setReferer(m_CurrentPage->handle());
        #endif

        m_CurrentPage = page;
    }

    return page;
}

DcpPage* PageFactory::createMainPage()
{
    if (!m_MainPage) {
        m_MainPage = new DcpMainPage();
        initPage(m_MainPage);
    }
    return m_MainPage;
}

DcpPage *
PageFactory::createAppletPage (
		DcpAppletMetadata *metadata)
{
    if (!m_AppletPage) {
        m_AppletPage = new DcpAppletPage(metadata);
        initPage(m_AppletPage);
    } else {
        m_AppletPage->setMetadata(metadata);
    }

    // page has to be loaded to know if the applet provides page or not
    if (m_AppletPage->isContentCreated()) {
        m_AppletPage->reload();
    } else {
        m_AppletPage->createContent();
    }

    if (!m_AppletPage->hasWidget() && !m_AppletPage->hasError()) {
        // the applet does not provide a page (eg. just a dialog)
        return 0;
    } else {
        return m_AppletPage;
    }
}

DcpPage* PageFactory::createAppletCategoryPage(Pages::Id id)
{
    const DcpCategoryInfo& info = DcpMain::CategoryInfos[
                                id - Pages::CATEGORY_PAGEID_START - 1];
    Q_ASSERT(info.subPageId == id);

    if (!m_AppletCategoryPage){
        m_AppletCategoryPage = new DcpAppletCategoryPage(info.appletCategory);
        initPage(m_AppletCategoryPage);
    } else {
        m_AppletCategoryPage->setAppletCategory(info.appletCategory);
    }

    return m_AppletCategoryPage;
}

void 
PageFactory::changePage (
        Pages::Handle handle)
{
    DcpPage *page = create (handle);

    DCP_DEBUG ("Destination");
    if (page) {
        page->appear (DuiSceneWindow::KeepWhenDone);
    }
}

void 
PageFactory::changePageWithReferer (
        const Pages::Handle  &handle,
        const QString        &refererName,
        int                   refererId)
{
    DCP_DEBUG ("Creating page '%s'/%d for referer '%s'/%d",
            DCP_STR (handle.param), handle.id,
            DCP_STR (refererName), refererId);

    DcpPage *page = create (handle);

    if (page) {
        if (refererId != -1) {
            page->setReferer ((Pages::Id) refererId, refererName);
        }
        page->appearNow (DuiSceneWindow::KeepWhenDone);
    }
}

void 
PageFactory::initPage (
        DcpPage* page)
{
    connect (page, SIGNAL(openSubPage (Pages::Handle)), 
            this, SLOT(changePage(Pages::Handle)));

    connect (
            page, 
            SIGNAL (openSubPageWithReferer(const Pages::Handle &, const QString &, int)), 
            this, 
            SLOT (changePageWithReferer(const Pages::Handle &, const QString &, int)));

    if (page != m_MainPage) {
        // closeAction TODO XXX on language change, move into to the page?
        DuiAction *quitAction = new DuiAction(qtTrId(DcpMain::quitMenuItemTextId), page);
        quitAction->setLocation((DuiAction::Location)4 /* FIXME DuiAction::ApplicationMenu */);
        
        connect(quitAction, SIGNAL(triggered()), qApp, SLOT(closeAllWindows()));

        // Add actions to page
        page->addAction(quitAction);
    }
}


