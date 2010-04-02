#include "dcpappletpage.h"

DcpAppletPage::DcpAppletPage (DcpAppletObject *applet, int widgetId) :
    DcpPage(),
    m_Applet (applet),
    m_WidgetId (widgetId),
    m_MainWidget (0),
    m_MissingLabel (0)
{
}


DcpAppletPage::~DcpAppletPage ()
{
}

void
DcpAppletPage::createContent ()
{
}

bool 
DcpAppletPage::hasWidget ()
{
    return true;
}

bool 
DcpAppletPage::hasError ()
{
    return false;
}

int 
DcpAppletPage::widgetId ()
{
    return m_WidgetId;
}

DcpAppletObject*
DcpAppletPage::applet()
{
    return m_Applet;
}


void
DcpAppletPage::load ()
{
}

void 
DcpAppletPage::back ()
{
}

void
DcpAppletPage::retranslateUi()
{
}

