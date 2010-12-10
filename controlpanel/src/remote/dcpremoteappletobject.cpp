#include "dcpremoteappletobject.h"

#include "dcpremotebrief.h"
#include "pagefactory.h"

#include <DcpAppletMetadata>
#include <DcpAppletDb>

DcpRemoteAppletObject::DcpRemoteAppletObject (DcpAppletMetadata* metadata,
                                              QObject* parent)
    : DcpAppletObject (metadata, false)
{
    setParent (parent);

    // We will not have an applet, only a brief:
    DcpRemoteBrief* brief = new DcpRemoteBrief (metadata->name());
    setBrief (brief);
    PageFactory::instance()->onAppletLoaded (this);
}


bool DcpRemoteAppletObject::loadPluginFile (const QString &binaryPath)
{
    Q_UNUSED (binaryPath);
    // this empty function disables accidentally loading the plugin
    // after the constructor run
    return false;
}

