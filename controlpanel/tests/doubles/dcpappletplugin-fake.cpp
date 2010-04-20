#include "dcpappletplugin.h"
#include "dcpappletplugin_p.h"

DcpAppletPlugin::DcpAppletPlugin(DcpAppletMetadata *metadata):
   d_ptr(new DcpAppletPluginPrivate(metadata))
{
}

DcpAppletPluginPrivate::DcpAppletPluginPrivate(DcpAppletMetadata* metadata):
    appletMetadata(metadata),
    appletInstance(0)
{
}

DcpAppletPluginPrivate::~DcpAppletPluginPrivate ()
{}

DcpAppletPlugin::~DcpAppletPlugin()
{
}

DcpAppletIf *
DcpAppletPlugin::applet() const
{
    return d_ptr->appletInstance; 
}

bool
DcpAppletPlugin::isAppletLoaded() const
{
    return d_ptr->appletInstance != 0;
}

DcpAppletMetadata*
DcpAppletPlugin::metadata () const 
{ 
    return d_ptr->appletMetadata;
}

const QString 
DcpAppletPlugin::errorMsg () const
{ 
    return d_ptr->errorMsg; 
}

bool 
DcpAppletPlugin::loadPluginFile (
        const QString &)
{
    return false;
}

bool 
DcpAppletPlugin::loadDslFile (
        const QString &)
{
    return false;
}

void 
DcpAppletPlugin::load ()
{
}

int
DcpAppletPlugin::interfaceVersion()
{
    return 999999;
}

