#include "dcpappletpage.h"
#include "exampleappletinterface.h"
#include <QDebug>
#include "duipannableviewport.h"
#include "dcpmaincategory.h"
#include "duilinearlayout.h"
#include <QPluginLoader>
#include "dcpappletmetadata.h"
DcpAppletPage::DcpAppletPage(DcpAppletMetadata *metadata):
    DcpCategoryPage(),
    m_Metadata(metadata) 
{
    setHandle(Pages::APPLET);
    setReferer(Pages::NOPAGE);
}

DcpAppletPage::~DcpAppletPage()
{
    if (m_View)
        delete m_View;
} 
void DcpAppletPage::createContent()
{
    DcpCategoryPage::createContent();
    initApplet();
}

void DcpAppletPage::organizeContent(Dui::Orientation ori)
{
    Q_UNUSED(ori);
}

void DcpAppletPage::initApplet()
{
    QPluginLoader loader(m_Metadata->fullBinary());
    if (!loader.load())
    {
	    qDebug() << "Loading applet is failed!";
	    return;
    }
    
    QObject *object = loader.instance();
    if (!object)
        return;    
    
    ExampleAppletInterface *applet = qobject_cast<ExampleAppletInterface*>(object);
    if (applet) 
    {
	m_View = applet->constructWidget();
	if (m_View) 
	{
		panLayout()->addItem(m_View);
		m_View->setMaximumWidth(DuiDeviceProfile::instance()->width() - 60);
        m_View->setMinimumWidth(DuiDeviceProfile::instance()->width() - 60);
        m_View->setMinimumHeight(DuiDeviceProfile::instance()->height());
	} else 
	{
		qWarning() << "applet->constructWidget() failed.";
	}
				
    } else 
    {
	qWarning() << "Can't convert object to ExampleAppletInterface.";
    }

    delete applet;
    applet = NULL;
}
void DcpAppletPage::setReferer(Pages::Id id, const QString &param)
{
    Q_UNUSED(param);
    m_Referer.id = id;
    m_Referer.param = m_Metadata->category();
    qDebug() << m_Referer.param;
}
