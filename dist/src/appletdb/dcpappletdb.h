#ifndef DCPAPPLETDB_H
#define DCPAPPLETDB_H
#include <QList>
#include <QString>
class DcpAppletMetadata;

namespace DcpApplet {
    const QString Dir = "/usr/lib/dcpcontrolpanel";
};

class DcpAppletDb
{
public:
    DcpAppletDb(const QString &pathName);
    void addPath(const QString &pathName);
    virtual ~DcpAppletDb();
    QList<DcpAppletMetadata*>* listByCategory(const QString& category);

private:
    QList<DcpAppletMetadata*> m_Applets;  
};
#endif // DCPAPPLETDB_H
