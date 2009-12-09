#include "dcpappletloader.h"
#include "dcpappletif.h"
#include "dcpappletmetadata.h"
#include <QPluginLoader>
#include "dcpwrongapplets.h"

DcpAppletLoader::DcpAppletLoader(const DcpAppletMetadata *metadata):
    m_Metadata(metadata)
{
    load();
}

DcpAppletLoader::~DcpAppletLoader()
{
    if (m_Applet)
        delete m_Applet;
    m_Applet = 0;
}

void DcpAppletLoader::load()
{
    QString binaryPath = m_Metadata->fullBinary();

    // skip applets which are considered as "bad"
    if (DcpWrongApplets::instance()->isBad(binaryPath)) {
        m_ErrorMsg = "Backlisted applet";
        m_Applet = 0;
        return;
    }

    QPluginLoader loader(binaryPath);
    if (!loader.load())
    {
        m_ErrorMsg = "Loading applet failed: " + loader.errorString();
        m_Applet = 0;
    } else
    {
        QObject *object = loader.instance();
        m_Applet = qobject_cast<DcpAppletIf*>(object);
        if (!m_Applet)
            m_ErrorMsg = "Can't convert object to ExampleAppletInterface.";
        else
            m_Applet->init();
    }
}

