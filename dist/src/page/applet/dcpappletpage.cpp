#include "dcpappletpage.h"
#include "exampleappletinterface.h"
#include <QDebug>
#include "duipannableviewport.h"
#include "dcpmaincategory.h"
#include "duilinearlayout.h"
#include <QPluginLoader>
DcpAppletPage::DcpAppletPage(const QString &appletBinary) : DcpCategoryPage(),
    m_AppletBinary(appletBinary) 
{
    m_PageId = Pages::APPLET;
    m_Referer = Pages::NOPAGE;
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
    QPluginLoader loader(appletBinary());
    if (!loader.load())
      {
		qDebug() << "Loading applet is failed!";
        return;
      }
    QObject *object = loader.instance();
    if (!object)
        return;    
    ExampleAppletInterface *applet = qobject_cast<ExampleAppletInterface*>(object);
    if (applet) {
	    m_View = applet->constructWidget();
		if (m_View) {
			//scene()->addItem(m_View);
			viewport()->setWidget(m_View);
				} else {
					qWarning() << "applet->constructWidget() failed.";
				}
				
			} else {
				qWarning() << "Can't convert object to ExampleAppletInterface.";
			}

	delete applet;
	applet = NULL;

 
}
