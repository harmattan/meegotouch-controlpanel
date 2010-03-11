#ifndef DCPAPPLETPLUGINPRIVATE_H
#define DCPAPPLETPLUGINPRIVATE_H

#include <QString>
#include <QPluginLoader>

class DcpAppletMetadata;
class DcpAppletIf;

class DcpAppletPluginPrivate {
public:
    DcpAppletPluginPrivate(DcpAppletMetadata* metadata);
    ~DcpAppletPluginPrivate();
    DcpAppletMetadata* appletMetadata;
    DcpAppletIf* appletInstance;
    QString errorMsg;
    QPluginLoader loader;
};
#endif // DCPAPPLETPLUGINPRIVATE_H
