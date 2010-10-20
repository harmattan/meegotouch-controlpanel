#include "dcpremoteappletobject.h"

#include "dcpremotebrief.h"

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
    connect (this, SIGNAL (activate (int)), this, SLOT (onActivated(int)));
}


bool DcpRemoteAppletObject::loadPluginFile (const QString &binaryPath)
{
    Q_UNUSED (binaryPath);
    // this empty function disables accidentally loading the plugin
    // after the constructor run
    return false;
}

void DcpRemoteAppletObject::onActivated (int pageId)
{
    // this is the point where the applet gets loaded:
    DcpAppletObject* myrealApplet =
        DcpAppletDb::instance()->applet (metadata ()->name());
    if (myrealApplet) {
        myrealApplet->activateSlot (pageId);
    }
}

