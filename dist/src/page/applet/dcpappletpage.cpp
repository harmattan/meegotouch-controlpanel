#include "dcpappletpage.h"
#include "exampleappletinterface.h"
#include <QDebug>
#include "duipannableviewport.h"
#include "dcpmaincategory.h"
#include "duilinearlayout.h"
#include <QPluginLoader>
#include "dcpappletmetadata.h"
#include <duilabel.h>
#include <duilocale.h>

DcpAppletPage::DcpAppletPage(DcpAppletMetadata *metadata):
    DcpPage(), m_View(NULL),
    m_Metadata(metadata)
{
    setHandle(Pages::APPLET);
}

DcpAppletPage::~DcpAppletPage()
{
    if (m_View)
        delete m_View;
} 

void DcpAppletPage::createContent()
{
    DcpPage::createContent();
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
        qDebug() << "Loading applet failed!";

    } else {
        QObject *object = loader.instance();

        ExampleAppletInterface *applet = qobject_cast<ExampleAppletInterface*>(object);
        if (applet)
        {
            m_View = applet->constructWidget();
            setTitle(applet->title());

            if (!m_View)
            {
                qWarning() << "applet->constructWidget() failed.";
            }

            delete applet;

        } else
        {
            qWarning() << "Can't convert object to ExampleAppletInterface.";
        }
    }


    if (!m_View) {
        DuiLabel* missingLabel = new DuiLabel(
                DuiLocale::trid("dcp_no_applet_name", "Plugin not available"));
        missingLabel->setAlignment(Qt::AlignCenter);
        m_View = missingLabel;
        setTitle(DuiLocale::trid("dcp_no_applet_title", "Missing plugin"));
    }

    mainLayout()->addItem(m_View);
    mainLayout()->setAlignment(m_View, Qt::AlignCenter);
    mainLayout()->setContentsMargins(25.0, 10.0, 25.0, 10.0);
    m_View->setMaximumWidth(DuiDeviceProfile::instance()->width() - 50);
    m_View->setMinimumWidth(DuiDeviceProfile::instance()->width() - 50);
    m_View->setMinimumHeight(DuiDeviceProfile::instance()->height() - 50);
}


void DcpAppletPage::setReferer(Pages::Id id, const QString &param)
{
    m_Referer.id = id;
    m_Referer.param = param;//m_Metadata->category();
    qDebug() << "DCP" << m_Referer.param;
}
