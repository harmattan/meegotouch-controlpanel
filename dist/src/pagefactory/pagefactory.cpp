#include "pagefactory.h"

#include "dcppage.h"
#include "dcpmainpage.h"
#include "dcpappletpage.h"
#include <DcpAppletDb>
#include <DcpAppletIf>
#include <DcpAppletMetadata>
#include "dcpappletcategorypage.h"
#include "maintranslations.h"

#include <DuiApplication>
#include <DuiAction>


// TODO handle if language changes

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

    return m_CurrentPage;
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
    return m_AppletPage;
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
    m_AppletCategoryPage->setTitle(info.title);

    return m_AppletCategoryPage;
}

void PageFactory::changePage(Pages::Handle handle)
{
    DcpPage *page = create(handle);
    page->appear(DuiSceneWindow::KeepWhenDone);
}

void PageFactory::initPage(DcpPage* page)
{
    connect(page, SIGNAL(openSubPage(Pages::Handle)), this, SLOT(changePage(Pages::Handle)));

    if (page != m_MainPage) {
        // closeAction
        DuiAction *quitAction = new DuiAction(DcpMain::quitMenuItemText, page);
        quitAction->setLocation(DuiAction::ViewMenu);
        connect(quitAction, SIGNAL(triggered()), qApp, SLOT(closeAllWindows()));

        // Add actions to page
        page->addAction(quitAction);
    }
}


