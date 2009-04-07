//#include <duilinearlayoutpolicy.h>
#include "dcpwidget.h"
#include "dcpappletpage.h"


DcpAppletPage::DcpAppletPage(DuiWidget *widget):
    DcpPage(), m_MainWidget(widget)
{
    setHandle(Pages::APPLET);
}

DcpAppletPage::~DcpAppletPage()
{
    if (m_MainWidget)
        m_MainWidget->deleteLater();
} 

void DcpAppletPage::createContent()
{
    DcpPage::createContent();
    append(m_MainWidget);
    
    this->setContentsMargins(12.0, 12.0, 12.0, 18.0);

    m_MainWidget->setMaximumWidth(DuiDeviceProfile::instance()->width() - 30);
    m_MainWidget->setMinimumWidth(DuiDeviceProfile::instance()->width() - 30);
    m_MainWidget->setMinimumHeight(DuiDeviceProfile::instance()->height() - 100);
}

