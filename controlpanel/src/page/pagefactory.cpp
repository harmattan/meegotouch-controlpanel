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

DcpPage* PageFactory::create(Pages::Handle &handle)
{
//    qDebug() << "create page: " << handle.id << handle.param;
    DcpPage *page=0;

    switch (handle.id) {
	    case Pages::MAIN:
            page = createMainPage();
            break;

        case Pages::APPLETCATEGORY: // when coming back
            Q_ASSERT(m_AppletCategoryPage);
            page = m_AppletCategoryPage;
            break;

        case Pages::APPLET:
            page = createAppletPage(DcpAppletDb::instance()->applet(handle.param));
            break;

        default:
        {
            Q_ASSERT(handle.id > Pages::CATEGORY_PAGEID_START
                     && handle.id < Pages::CATEGORY_PAGEID_END);
            page = createAppletCategoryPage(handle.id);
        }
    }

    if (page) {
        if (m_CurrentPage)
            m_CurrentPage->disconnectSignals();

        page->connectSignals();

		if (page->isContentCreated())
            page->reload();

        if (m_CurrentPage && page->referer().id == Pages::NOPAGE)
                page->setReferer(m_CurrentPage->handle());

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

DcpPage* PageFactory::createAppletPage(DcpAppletMetadata *metadata)
{
    if (!m_AppletPage) {
        m_AppletPage = new DcpAppletPage(metadata);
        initPage(m_AppletPage);
    } else {
        m_AppletPage->setMetadata(metadata);
    }

    // page has to be loaded to know if the applet provides page or not
    if (m_AppletPage->isContentCreated()){
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

void PageFactory::changePage(Pages::Handle handle)
{
    DcpPage *page = create(handle);
    if (page) {
        page->appear(DuiSceneWindow::KeepWhenDone);
    }
}

void PageFactory::initPage(DcpPage* page)
{
    connect(page, SIGNAL(openSubPage(Pages::Handle)), this, SLOT(changePage(Pages::Handle)));

    if (page != m_MainPage) {
        // closeAction TODO XXX on language change, move into to the page?
        DuiAction *quitAction = new DuiAction(qtTrId(DcpMain::quitMenuItemTextId), page);
        quitAction->setLocation((DuiAction::Location)4 /* FIXME DuiAction::ApplicationMenu */);
        connect(quitAction, SIGNAL(triggered()), qApp, SLOT(closeAllWindows()));

        // Add actions to page
        page->addAction(quitAction);
    }
}


