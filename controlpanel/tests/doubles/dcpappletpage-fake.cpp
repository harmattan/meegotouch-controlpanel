#include "dcpappletpage.h"

DcpAppletPage::DcpAppletPage (DcpAppletObject *applet, int widgetId) :
    DcpPage(),
    m_MainWidget (0),
    m_MissingLabel (0)
{
    Q_UNUSED(applet);
    Q_UNUSED(widgetId);
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
    return 0;
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

