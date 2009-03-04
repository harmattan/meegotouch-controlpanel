#include "dcpappletdb.h"
#include "dcpappletmetadata.h"
#include <QDir>
#include <QDebug>
const QString APPLETFILTER = "*.desktop";

DcpAppletDb *DcpAppletDb::sm_Instance=0;

DcpAppletDb*
DcpAppletDb::instance(const QString &pathName)
{
    if (!sm_Instance)
        sm_Instance = new DcpAppletDb(pathName);
    return sm_Instance;
}

DcpAppletDb::DcpAppletDb(const QString &pathName)
{
    addPath(pathName);
}

DcpAppletDb::~DcpAppletDb()
{
    m_Applets.clear();
}

void
DcpAppletDb::addPath(const QString &pathName)
{
    QDir appDir(pathName, APPLETFILTER);
    if (!appDir.exists())
    {
        qWarning() << "Applet dir" << pathName << "does not exists";
        return;
    }
    
    foreach(QString appFile, appDir.entryList())
    {
        DcpAppletMetadata *metadata = new DcpAppletMetadata(appDir.absoluteFilePath(appFile));
       m_Applets[metadata->name()] = metadata;
    }
}

QList<DcpAppletMetadata*>* 
DcpAppletDb::listByCategory(const QString& category)
{
    QList<DcpAppletMetadata*> *filtered = new QList<DcpAppletMetadata*>();
    foreach (DcpAppletMetadata *item, m_Applets)
    {
        qDebug() << item->category() << "==" << category;
        if (item->category() == category)
            filtered->append(item);
    }
    return filtered;
}

DcpAppletMetadata*
DcpAppletDb::applet(const QString& name)
{
    DcpAppletMetadata *metadata = m_Applets.value(name, 0);
    if (!metadata)
        qWarning() << "No such applet:" << name;
    return metadata;
};
