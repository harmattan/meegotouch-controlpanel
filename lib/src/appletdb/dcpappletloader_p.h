#ifndef DCPAPPLETLOADERPRIVATE_H
#define DCPAPPLETLOADERPRIVATE_H
#include <QString>
class DcpAppletMetadata;
class DcpAppletIf;
class DcpAppletLoaderPrivate {
public:
    DcpAppletLoaderPrivate(const DcpAppletMetadata* metadata);
    ~DcpAppletLoaderPrivate();
    const DcpAppletMetadata* metadata;
    DcpAppletIf* applet;
    QString errorMsg;
};
#endif // DCPAPPLETLOADERPRIVATE_H
