#ifndef DCPAPPLETMETADATA_P_H
#define DCPAPPLETMETADATA_P_H

#include <QFileInfo>
class DcpBrief;
class DcpAppletLoader;
class DuiDesktopEntry;
class DcpAppletMetadata;
class QString;

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
    QString m_FileName;
    QString m_BinaryDir;
    QString m_GconfKeyUsage;
};

#endif // DCPAPPLETMETADATA_P_H
