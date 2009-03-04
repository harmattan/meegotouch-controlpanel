#ifndef DCPAPPLETDB_H
#define DCPAPPLETDB_H
#include <QList>
#include <QMap>
#include <QString>
class DcpAppletMetadata;

namespace DcpApplet {
    const QString DefaultPath = "/usr/lib/dcpcontrolpanel";
};

class DcpAppletDb
{
public:
    static DcpAppletDb *instance(const QString &pathName=DcpApplet::DefaultPath);
    void addPath(const QString &pathName);
    virtual ~DcpAppletDb();
    QList<DcpAppletMetadata*>* listByCategory(const QString& category);
    DcpAppletMetadata *applet(const QString& name);
protected:
    DcpAppletDb(const QString &pathName);
private:
    QMap<QString, DcpAppletMetadata*> m_Applets;  
    static DcpAppletDb *sm_Instance;
};
#endif // DCPAPPLETDB_H
