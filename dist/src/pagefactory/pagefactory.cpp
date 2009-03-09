#include "pagefactory.h"
#include "dcpmainpage.h"
#include "dcpaccountspage.h"
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

Pages::Id
PageFactory::idOf(DuiApplicationPage *page)
{
    return qobject_cast<DcpPage*>(page)->pageId();
}

Pages::Id
PageFactory::refererOf(DuiApplicationPage *page)
{
    return qobject_cast<DcpPage*>(page)->referer();
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
            page = createAccountsPage();
            break;
        case Pages::PERSONALIZATION:
            page = createAppletCategoryPage("Personalization");
            break;
        case Pages::CONNECTIVITY:
            page = createAppletCategoryPage("Connectivity");
            break;
        case Pages::DISPLAY:
            page = createAppletCategoryPage("Display");
            break;
        case Pages::SOUND:
            page = createAppletCategoryPage("Sound");
            break;
        case Pages::CALL:
            page = createAppletCategoryPage("Call");
            break;
        case Pages::DATETIME:
            page = createAppletCategoryPage("Datetime");
            break;
        case Pages::SECURITY:
            page = createAppletCategoryPage("Security");
            break;
        case Pages::APPLET:
            page = createAppletPage(DcpAppletDb::instance()->applet(param));
            break;
	default:
            qWarning() << "Bad page ID: " << pageId;
            // page=0;
            page = createAppletCategoryPage("Personalization");
      }  
    return page;
}

DcpPage* 
PageFactory::createMainPage()
{
    return new DcpMainPage();
}

DcpPage* 
PageFactory::createAccountsPage()
{
    return new DcpAccountPage();
}

DcpPage* 
PageFactory::createAppletPage(DcpAppletMetadata *metadata)
{
    QString lib =DcpApplet::Lib + metadata->appletBinary();
    qDebug() << "APPLET SO: " << lib;    
    return new DcpAppletPage(lib);
}

DcpPage* 
PageFactory::createAppletCategoryPage(const QString& appletCategory)
{
    return new DcpAppletCategoryPage(appletCategory);
}
