#ifndef DCPAPPLETMETADATA_P_H
#define DCPAPPLETMETADATA_P_H

#include <QFileInfo>
class DcpBrief;
class DcpAppletLoader;
class DuiDesktopEntry;

class DcpAppletMetadataPrivate
{
public:
    DcpAppletMetadataPrivate();
    ~DcpAppletMetadataPrivate();

    QFileInfo m_FileInfo;

    DcpAppletLoader* m_AppletLoader;
    DcpBrief* m_Brief;
    DuiDesktopEntry* m_DesktopEntry;
};

#endif // DCPAPPLETMETADATA_P_H
