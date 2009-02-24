#include "dcpappletpage.h"
#include "exampleappletinterface.h"
#include <QDebug>
#include "duipannableviewport.h"
#include <QPluginLoader>
DcpAppletPage::DcpAppletPage(const QString &appletBinary) : DcpPage() 
{
    m_PageId = Pages::APPLET;
    m_Referer = Pages::NOPAGE;
    createContent();
    init(appletBinary);
}

DcpAppletPage::~DcpAppletPage()
{
    if (m_View)
        delete m_View;
} 
void DcpAppletPage::createContent()
{
    DcpPage::createContent();
}

void DcpAppletPage::organizeContent(Dui::Orientation ori)
{
    Q_UNUSED(ori);
}

void DcpAppletPage::init(const QString &appletBinary, 
				 const QString &appletMetaData,
				 const QString &appletId)
{
	Q_UNUSED(appletMetaData);
	Q_UNUSED(appletId);
    
    QPluginLoader loader(appletBinary);
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
			m_DesktopViewport->setWidget(m_View);
            m_View->setGeometry(QRectF(0, 0,
		 					   DuiDeviceProfile::instance()->width(),
								   DuiDeviceProfile::instance()->height()));

//					scene()->setBackgroundBrush(QColor(0, 0, 0, 255));
				} else {
					qWarning() << "applet->constructWidget() failed.";
				}
				
			} else {
				qWarning() << "Can't convert object to ExampleAppletInterface.";
			}

//	delete applet;
//	applet = NULL;

 
}
