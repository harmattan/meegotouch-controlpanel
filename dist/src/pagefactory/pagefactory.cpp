#include "pagefactory.h"
#include "dcpmainpage.h"
#include "dcpaccountspage.h"
#include "dcpappletpage.h"
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
PageFactory::create(Pages::Id pageId)
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
        case Pages::APPLET:
            page = createAppletPage();
            break;
	default:
            qWarning() << "Bad page ID: " << pageId;
	    page=0;
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
    return new DcpAppletPage("/home/lac/work/duicontrolpanel/addons/appletexample/lib/libexampleapplet.so");
}
