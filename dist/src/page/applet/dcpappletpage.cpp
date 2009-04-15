//#include <duilinearlayoutpolicy.h>
#include "dcpwidget.h"
#include "dcpappletpage.h"
#include "dcpappletif.h"
#include "dcpappletmetadata.h"
#include "dcpappletloader.h"
#include "duilabel.h"
#include "duilocale.h"

DcpAppletPage::DcpAppletPage(DcpAppletMetadata *metadata):
    DcpPage(), m_Metadata(metadata)
{
    setHandle(Pages::APPLET);
}

DcpAppletPage::~DcpAppletPage()
{
    delete m_AppletLoader;
} 

void DcpAppletPage::createContent()
{
    DcpPage::createContent();
    if (loadApplet())
       {
          changeWidget(0);
       }
     else
      {
          DuiLabel *missingLabel = new DuiLabel(trid("dcp_no_applet_name",
                                     "Plugin not available"));
          missingLabel->setAlignment(Qt::AlignCenter);
          setCentralWidget(missingLabel);
          setTitle(trid("dcp_no_applet_title", "Missing plugin"));
      }
}

bool 
DcpAppletPage::loadApplet()
{
    m_AppletLoader = new DcpAppletLoader(m_Metadata);
    bool result = true;
    if (!m_AppletLoader->applet())
    {
        qWarning() << m_AppletLoader->errorMsg();
        result = false;
    }
    return result;
}

void DcpAppletPage::back()
{
    if (m_MainWidget->back())
        DcpPage::back();
}

void 
DcpAppletPage::changeWidget(int widgetId)
{
    m_MainWidget = m_AppletLoader->applet()->constructWidget(widgetId);
    connect(m_MainWidget, SIGNAL(changeWidget(int)), this, SLOT(changeWidget(int)));
    setCentralWidget(m_MainWidget);
  
    setTitle(m_AppletLoader->applet()->title());
    this->setContentsMargins(120.0, 12.0, 12.0, 18.0);

    m_MainWidget->setMaximumWidth(DuiDeviceProfile::instance()->width() - 30);
    m_MainWidget->setMinimumWidth(DuiDeviceProfile::instance()->width() - 30);
    m_MainWidget->setMinimumHeight(DuiDeviceProfile::instance()->height() - 100);

}
