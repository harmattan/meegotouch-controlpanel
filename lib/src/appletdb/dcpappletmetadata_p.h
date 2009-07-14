#ifndef DCPAPPLETMETADATA_P_H
#define DCPAPPLETMETADATA_P_H

#include <QFileInfo>
class DcpBrief;
class DcpAppletLoader;
class DuiDesktopEntry;
class DcpAppletMetadata;

class DcpAppletMetadataPrivate
{
public:
    DcpAppletMetadataPrivate();
    ~DcpAppletMetadataPrivate();

    QFileInfo m_FileInfo;

    DcpAppletLoader* m_AppletLoader;
    DcpBrief* m_Brief;
    DuiDesktopEntry* m_DesktopEntry;
    DcpAppletMetadata *m_Parent;
	int m_Counter;
};

#endif // DCPAPPLETMETADATA_P_H
