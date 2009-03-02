#ifndef DCPAPPLETDB_H
#define DCPAPPLETDB_H
#include <QList>
class DcpAppletMetadata;
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
