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
DcpAppletLoader *PageFactory::sm_AppletLoader = 0;


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
            page = createAppletPageFromCategory(DcpAppletDb::instance()->applet(param));
            break;
        case Pages::APPLETFROMMOSTUSED:
            page = createAppletPageFromMostUsed(DcpAppletDb::instance()->applet(param));
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
    QString title;
    DuiWidget *widget;
     if (loadApplet(metadata))
       {
          m_AppletWidget = sm_AppletLoader->applet()->constructWidget(0);
          title = sm_AppletLoader->applet()->title();
          connect(m_AppletWidget,
                  SIGNAL(changeWidget(int)), 
                  this, SLOT(changeAppletWidget(int)));
          widget = m_AppletWidget;
       }
     else
      {
          DuiLabel *missingLabel = new DuiLabel(trid("dcp_no_applet_name",
                                     "Plugin not available"));
          missingLabel->setAlignment(Qt::AlignCenter);
          widget = missingLabel;
          title = trid("dcp_no_applet_title", "Missing plugin");
      }
    DcpPage *page = new DcpAppletPage(widget);
    page->setTitle(title);
    return page;
}

DcpPage* 
PageFactory::createAppletCategoryPage(const QString& appletCategory)
{
    return new DcpAppletCategoryPage(appletCategory);
}

bool 
PageFactory::loadApplet(DcpAppletMetadata *metadata)
{
    if (sm_AppletLoader)
        delete sm_AppletLoader;
    sm_AppletLoader = new DcpAppletLoader(metadata);
    bool result = true;
    if (!sm_AppletLoader->applet())
    {
        qWarning() << sm_AppletLoader->errorMsg();
        result = false;
    }
    return result;
}
    
void PageFactory::changeAppletWidget(int widgetId)
{
    m_AppletWidget = sm_AppletLoader->applet()->constructWidget(widgetId);
    connect(m_AppletWidget, SIGNAL(changeWidget(int)), this, 
                           SLOT(changeAppletWidget(int)));
    DcpPage *page = new DcpAppletPage(m_AppletWidget);
    page->setTitle(sm_AppletLoader->applet()->title());
    page->setReferer(Pages::APPLETCATEGORY, 
        sm_AppletLoader->metadata()->category());
    emit changePage(page);
}

bool 
PageFactory::backFromApplet()
{
     if (!sm_AppletLoader->applet())
        return true;
     if (m_AppletWidget->referer() == -1)
        return true;
     else
      {
         qDebug() << "XXX applet referer is" << m_AppletWidget->referer();
          changeAppletWidget(m_AppletWidget->referer());
          return false;
      };
}
