#ifndef DCPAPPLETPLUGINPRIVATE_H
#define DCPAPPLETPLUGINPRIVATE_H
#include <QString>
class DcpAppletMetadata;
class DcpAppletIf;
class DcpAppletPluginPrivate {
public:
    DcpAppletPluginPrivate(DcpAppletMetadata* metadata);
    ~DcpAppletPluginPrivate();
    DcpAppletMetadata* appletMetadata;
    DcpAppletIf* appletInstance;
    QString errorMsg;
};
#endif // DCPAPPLETPLUGINPRIVATE_H
