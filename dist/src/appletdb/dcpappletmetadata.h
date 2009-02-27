#ifndef DCPAPPLETMETADATA_H
#define DCPAPPLETMETADATA_H
#include <duidesktopentry.h>

class DcpAppletMetadata : public DuiDesktopEntry
{
public:
    DcpAppletMetadata(const QString& filename);
    virtual ~DcpAppletMetadata();
    bool isValid();
    QString category() const;
    QString icon() const;
    QString appletBinary() const;
};
#endif // DCPAPPLETMETADATA_H
