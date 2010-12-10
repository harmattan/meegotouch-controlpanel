#include "dcpremoteappletobject.h"

#include <DcpAppletMetadata>
#include <DcpAppletDb>

DcpRemoteAppletObject::DcpRemoteAppletObject (DcpAppletMetadata* metadata,
                                              QObject* parent)
    : DcpAppletObject (metadata, false)
{
    setParent (parent);
}


bool DcpRemoteAppletObject::loadPluginFile (const QString &binaryPath)
{
    Q_UNUSED (binaryPath);
    return false;
}


