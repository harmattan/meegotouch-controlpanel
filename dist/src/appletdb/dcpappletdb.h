#ifndef DCPAPPLETDB_H
#define DCPAPPLETDB_H
#include <QList>
#include <QMap>
#include <QString>
class DcpAppletMetadata;

typedef QList<DcpAppletMetadata*> DcpAppletMetadataList;
typedef QMap<QString, DcpAppletMetadata*> DcpAppletMetadataMap;

namespace DcpApplet {
    const QString DefaultPath = "desktop";
};

class DcpAppletDb
{
public:
    static DcpAppletDb *instance(const QString &pathName=DcpApplet::DefaultPath);
    void addPath(const QString &pathName);
    virtual ~DcpAppletDb();
    DcpAppletMetadataList listByCategory(const QString& category);
    DcpAppletMetadata *applet(const QString& name);
protected:
    DcpAppletDb(const QString &pathName);
private:
    DcpAppletMetadataMap m_Applets;  
    static DcpAppletDb *sm_Instance;
};
#endif // DCPAPPLETDB_H
