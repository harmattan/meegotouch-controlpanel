#ifndef DCPAPPLETDB_H
#define DCPAPPLETDB_H
#include <QList>
class DcpAppletMetaData;
class DcpAppletDb
{
public:
    DcpAppletDb(const QString &pathName);
    void addPath(const QString &pathName);
    virtual ~DcpAppletDb();
    QList<DcpAppletMetaData*> listByCategory(const QString& name);
private:
    QList<DcpAppletMetaData*> m_Applets;  
};
#endif // DCPAPPLETDB_H
