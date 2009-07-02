#ifndef DCPAPPLETDB_H
#define DCPAPPLETDB_H
#include <QList>
#include <QMap>
#include <QString>
#include "dcpapplet.h"
class DcpAppletMetadata;

typedef QList<DcpAppletMetadata*> DcpAppletMetadataList;
typedef QMap<QString, DcpAppletMetadata*> DcpAppletMetadataMap;


class DcpAppletDb
{
public:
    static DcpAppletDb *instance(const QString &pathName=DcpApplet::DefaultPath);
    void addPath(const QString &pathName);
    virtual ~DcpAppletDb();
    DcpAppletMetadataList listByCategory(const QString& category);
    DcpAppletMetadataList listMostUsed();
    DcpAppletMetadata *applet(const QString& name);
    void addFile(const QString& filename);
    void eraseEntry(DcpAppletMetadata *metadata);
    void refresh();

	void destroy(void);
protected:
    DcpAppletDb(const QString &pathName);
    void refreshPath(const QString &pathName);
private:
    DcpAppletMetadataMap m_AppletsByName;  
    DcpAppletMetadataMap m_AppletsByFile; 
    QList<QString> m_Paths; 
    static DcpAppletDb *sm_Instance;
};
#endif // DCPAPPLETDB_H
