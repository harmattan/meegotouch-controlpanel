#include "pagefactory.h"
#include "dcpmainpage.h"
#include "dcpappletpage.h"
#include "dcpappletdb.h"
#include "dcpappletmetadata.h"
#include "dcpappletcategorypage.h"
#include <QtDebug>

PageFactory *PageFactory::sm_Instance =0;



PageFactory::PageFactory()
{}

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
PageFactory::create(Pages::Id pageId, const QString &param)
{
    DcpPage *page=0;
    switch (pageId)
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
            page = createAppletCategoryPage(param);
            break;
        case Pages::APPLET:
            page = createAppletPage(DcpAppletDb::instance()->applet(param));
            break;
        case Pages::RESETSETTINGS:
            qWarning ("Reset settings page is not implemented yet.");
            page = createAppletCategoryPage("not implemented");
            break;
    default:
            qWarning() << "DCP" << "Bad page ID: " << pageId;
            //page=0;
      }  
    return page;
}

DcpPage* 
PageFactory::createMainPage()
{
    return new DcpMainPage();
}

DcpPage* 
PageFactory::createAppletPage(DcpAppletMetadata *metadata)
{
    return new DcpAppletPage(metadata);
}

DcpPage* 
PageFactory::createAppletCategoryPage(const QString& appletCategory)
{
    return new DcpAppletCategoryPage(appletCategory);
}
