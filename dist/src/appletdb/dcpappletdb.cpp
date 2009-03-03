#include "dcpappletdb.h"
#include "dcpappletmetadata.h"
#include <QDir>
#include <QDebug>
const QString APPLETFILTER = "*.desktop";
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
        m_Applets.append(new DcpAppletMetadata(appDir.absoluteFilePath(appFile)));
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
