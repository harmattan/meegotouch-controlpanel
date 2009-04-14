#include "pagefactory.h"
#include "dcpmainpage.h"
#include "dcpappletpage.h"
#include "dcpappletdb.h"
#include "dcpappletif.h"
#include "dcpappletmetadata.h"
#include "dcpappletcategorypage.h"
#include "dcpwidget.h"
#include "dcpappletloader.h"
#include <QtDebug>
#include <DuiLabel>
#include <duilocale.h>

PageFactory *PageFactory::sm_Instance =0;

PageFactory::PageFactory()
{
    m_CurrentPage = 0;
}

PageFactory*
PageFactory::instance()
{
    if (!sm_Instance)
        sm_Instance = new PageFactory();
    return sm_Instance;
}

DcpPage*
PageFactory::page(DuiApplicationPage *page)
{
    return qobject_cast<DcpPage*>(page);
}


DcpPage* 
PageFactory::create(Pages::Handle &handle)
{
    DcpPage *page=0;
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
    if (page && m_CurrentPage) {
        if (page->referer().id == Pages::NOPAGE)
            page->setReferer(m_CurrentPage->handle());
    }
    m_CurrentPage = page;
    return page;
}

DcpPage* 
PageFactory::createMainPage()
{
    return new DcpMainPage();
}

DcpPage*
PageFactory::createAppletPageFromCategory(DcpAppletMetadata *metadata)
{
    DcpPage *page = createAppletPage(metadata);
    page->setReferer(Pages::APPLETCATEGORY, metadata->category());
    return page;
}


DcpPage* 
PageFactory::createAppletPageFromMostUsed(DcpAppletMetadata *metadata)
{
    DcpPage *page = createAppletPage(metadata);
    page->setReferer(Pages::MAIN);
    return page;
}

DcpPage*
PageFactory::createAppletPage(DcpAppletMetadata *metadata)
{
    DcpPage *page = new DcpAppletPage(metadata);
    return page;
}

DcpPage* 
PageFactory::createAppletCategoryPage(const QString& appletCategory)
{
    return new DcpAppletCategoryPage(appletCategory);
}


