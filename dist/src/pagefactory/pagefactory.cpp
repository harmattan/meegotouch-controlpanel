// TODO XXX is this all needed??
#include "pagefactory.h"
#include "dcppage.h"
#include "dcpmainpage.h"
#include "dcpappletpage.h"
#include "dcpappletdb.h"
#include "dcpappletif.h"
#include "dcpappletmetadata.h"
#include "dcpappletcategorypage.h"
#include "dcpwidget.h"
#include "dcpappletloader.h"
#include "maintranslations.h"
#include <QtDebug>
#include <DuiLabel>
#include <duilocale.h>

#include <DuiApplication>
#include <DuiAction>

// TODO XXX remove this dependency, it is only because of quit text
#include "maintranslations.h"

PageFactory *PageFactory::sm_Instance = 0;

PageFactory::PageFactory(): QObject(),
    m_CurrentPage(0), m_MainPage(0), m_AppletPage(0), m_AppletCategoryPage(0)
{
}

PageFactory*
PageFactory::instance()
{
    if (!sm_Instance)
        sm_Instance = new PageFactory();
    return sm_Instance;
}

DcpPage*
PageFactory::create(Pages::Handle &handle)
{
    DcpPage *page=0;
    qDebug() << "XXX pagefactory page request" << handle.id << handle.param;
    switch (handle.id)
      {
	case Pages::MAIN:
            page = createMainPage();
            break;
        case Pages::ACCOUNTS:
            page = createAppletCategoryPage("Account");
            break;
        case Pages::REGIONALSETTING:
            page = createAppletCategoryPage("Regional settings");
            break;
        case Pages::CONNECTIVITY:
            page = createAppletCategoryPage("Connectivity");
            break;
        case Pages::SEEINGTOUCHING:
            page = createAppletCategoryPage("Seeing & Touching");
            break;
        case Pages::APPLICATION:
            page = createAppletCategoryPage("Application");
            break;
        case Pages::SOUND:
            page = createAppletCategoryPage("Sound");
            break;
        case Pages::DEVICESYSTEM:
            page = createAppletCategoryPage("Device system");
            break;
        case Pages::APPLETCATEGORY:
            page = createAppletCategoryPage(handle.param);
            break;
        case Pages::APPLET:
            page = createAppletPageFromCategory(DcpAppletDb::instance()->applet(handle.param));
            break;
        case Pages::APPLETFROMMOSTUSED:
            page = createAppletPageFromMostUsed(DcpAppletDb::instance()->applet(handle.param));
            break;
        case Pages::RESETSETTINGS:
            qWarning ("Reset settings page is not implemented yet.");
            page = createAppletCategoryPage("not implemented");
            break;
    default:
            qWarning() << "DCP" << "Bad page ID: " << handle.id;
    }
    if (page) {
        if (page->isContentCreated()) {
            page->reload();
        }
        if (m_CurrentPage && page->referer().id == Pages::NOPAGE) {
                page->setReferer(m_CurrentPage->handle());
        }
    }
    m_CurrentPage = page;
    return page;
}

DcpPage*
PageFactory::createMainPage()
{
    if (!m_MainPage) {
        m_MainPage = new DcpMainPage();
        initPage(m_MainPage);
    }
    return m_MainPage;
}

DcpPage*
PageFactory::createAppletPageFromCategory(DcpAppletMetadata *metadata)
{
    createAppletPage(metadata);
    Q_ASSERT(m_AppletPage);
    m_AppletPage->setReferer(Pages::APPLETCATEGORY, metadata->category());
    return m_AppletPage;
}


DcpPage*
PageFactory::createAppletPageFromMostUsed(DcpAppletMetadata *metadata)
{
    createAppletPage(metadata);
    Q_ASSERT(m_AppletPage);
    m_AppletPage->setReferer(Pages::MAIN);
    return m_AppletPage;
}

DcpPage*
PageFactory::createAppletPage(DcpAppletMetadata *metadata)
{
    if (!m_AppletPage) {
        m_AppletPage = new DcpAppletPage(metadata);
        initPage(m_AppletPage);
    } else {
        m_AppletPage->setMetadata(metadata);
    }
    return m_AppletPage;
}

DcpPage*
PageFactory::createAppletCategoryPage(const QString& appletCategory)
{
    if (!m_AppletCategoryPage){
        m_AppletCategoryPage = new DcpAppletCategoryPage(appletCategory);
        initPage(m_AppletCategoryPage);
    } else {
        m_AppletCategoryPage->setAppletCategory(appletCategory);
    }
    return m_AppletCategoryPage;
}

void PageFactory::changePage(Pages::Handle handle)
{
    DcpPage *page = create(handle);
    page->appear(DuiSceneWindow::KeepWhenDone);
}

void PageFactory::initPage(DcpPage* page) {
    connect(page, SIGNAL(openSubPage(Pages::Handle)), this, SLOT(changePage(Pages::Handle)));

    // closeAction
    DuiAction *quitAction = new DuiAction(DcpMain::quitMenuItemText, this);
    quitAction->setLocation(DuiAction::ViewMenu);
    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(closeAllWindows()));

    // Add actions to page
    if (page != m_MainPage)
        page->addAction(quitAction);
}

