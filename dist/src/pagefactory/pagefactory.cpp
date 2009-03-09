#include "pagefactory.h"
#include "dcpmainpage.h"
#include "dcpaccountspage.h"
#include "dcpappletpage.h"
#include "dcpappletcategorypage.h"
#include <QtDebug>

#include "dcpmostusedcategorypage.h"

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
PageFactory::create(Pages::Id pageId)
{
    DcpPage *page=0;
    switch (pageId)
      {
	case Pages::MAIN:
            //page = new DcpMostUsedCategoryPage("dsadsa");
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
            page = createAppletPage();
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
PageFactory::createAppletPage()
{
    return new DcpAppletPage("/usr/lib/duicontrolpanel/applets/libexampleapplet.so");
}

DcpPage* 
PageFactory::createAppletCategoryPage(const QString& appletCategory)
{
    return new DcpAppletCategoryPage(appletCategory);
}
