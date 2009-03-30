#include <QDebug>
#include <QPluginLoader>
#include <duilabel.h>
#include <duilocale.h>
#include "dcpwidget.h"

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
    DcpPage::createContent();
    initApplet();
}

void DcpAppletPage::initApplet()
{
    qDebug() << "DCP: " <<  m_Metadata->fullBinary();
    DuiWidget *view;
    QPluginLoader loader(m_Metadata->fullBinary());
    if (!loader.load())
    {
        qDebug() << "Loading applet failed: " << loader.errorString();

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
        view = missingLabel;
        
        setTitle(DuiLocale::trid("dcp_no_applet_title", "Missing plugin"));
    }
    else
        view = m_View;

    append(view);
    this->setContentsMargins(25.0, 10.0, 25.0, 10.0);

    view->setMaximumWidth(DuiDeviceProfile::instance()->width() - 50);
    view->setMinimumWidth(DuiDeviceProfile::instance()->width() - 50);
    view->setMinimumHeight(DuiDeviceProfile::instance()->height() - 100);
}


void DcpAppletPage::setReferer(Pages::Id id, const QString &param)
{
    m_Referer.id = id;
    m_Referer.param = param;//m_Metadata->category();
    qDebug() << "DCP" << m_Referer.param;
}
