#include <QDebug>
#include <QPluginLoader>
#include <duilabel.h>
#include <duilocale.h>

#include "dcpappletpage.h"
#include "dcpappletif.h"
#include "dcpappletmetadata.h"


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
    initApplet();
}

void DcpAppletPage::initApplet()
{
    QPluginLoader loader(m_Metadata->fullBinary());
    if (!loader.load())
    {
        qDebug() << "Loading applet failed!";

    } else {
        QObject *object = loader.instance();

        DcpAppletIf *applet = qobject_cast<DcpAppletIf*>(object);
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

    append(m_View);
    this->setContentsMargins(25.0, 10.0, 25.0, 10.0);

    m_View->setMaximumWidth(DuiDeviceProfile::instance()->width() - 50);
    m_View->setMinimumWidth(DuiDeviceProfile::instance()->width() - 50);
    m_View->setMinimumHeight(DuiDeviceProfile::instance()->height() - 100);
}


void DcpAppletPage::setReferer(Pages::Id id, const QString &param)
{
    m_Referer.id = id;
    m_Referer.param = param;//m_Metadata->category();
    qDebug() << "DCP" << m_Referer.param;
}
