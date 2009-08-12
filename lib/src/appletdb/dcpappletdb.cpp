#include "dcpappletdb.h"
#include "dcpappletmetadata.h"
#include <QDir>
#include <QDebug>
const QString APPLETFILTER = "*.desktop";
const int MAXMOSTUSED = 6;
DcpAppletDb *DcpAppletDb::sm_Instance=0;

static bool orderLessThan(DcpAppletMetadata *meta1, DcpAppletMetadata *meta2)
{
    return meta1->order() < meta2->order();
}

static bool usageGreatherThan(DcpAppletMetadata *meta1, DcpAppletMetadata *meta2)
{
    return meta1->usage() > meta2->usage();
}
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
    sm_Instance = 0;
}

void 
DcpAppletDb::addFile(const QString& filename)
{
  DcpAppletMetadata *metadata = new DcpAppletMetadata(filename);
  m_AppletsByName[metadata->name()] = metadata;
  m_AppletsByFile[filename] = metadata;
}

void
DcpAppletDb::addPath(const QString &pathName)
{
    QDir appDir(pathName); 
    foreach(QString appFile, appDir.entryList(QStringList("*.desktop")))
    {
        addFile(appDir.absoluteFilePath(appFile));
    }
    m_Paths.append(pathName);
}

DcpAppletMetadataList 
DcpAppletDb::listByCategory(const QString& category)
{
    QList<DcpAppletMetadata*> filtered;

    foreach (DcpAppletMetadata *item, m_AppletsByFile)
    {
        if (category.compare(item->category(),Qt::CaseInsensitive) == 0)
            filtered.append(item);
        QString parentName = item->parentName();
        if (parentName == "" && !item->parent())
          {
            item->setParent(applet(parentName));  
            qDebug() << "IIII parent of" << item->name() << "is" << parentName; 
          }
        
    }
    qSort(filtered.begin(), filtered.end(), orderLessThan);
    return filtered;
}

DcpAppletMetadataList
DcpAppletDb::listMostUsed()
{
   DcpAppletMetadataList mostUsed = m_AppletsByName.values();
   qSort(mostUsed.begin(), mostUsed.end(), usageGreatherThan); 
   return mostUsed.mid(0, MAXMOSTUSED);
}

DcpAppletMetadata*
DcpAppletDb::applet(const QString& name)
{
    DcpAppletMetadata *metadata = m_AppletsByName.value(name, 0);
    if (!metadata)
        qWarning() << "No such applet:" << name;
    return metadata;
};
void 
DcpAppletDb::refresh()
{
    foreach(QString pathName, m_Paths)
        refreshPath(pathName);
}

void DcpAppletDb::refreshPath(const QString &pathName)
{

    QDir appDir(pathName, APPLETFILTER);
    if (!appDir.exists())
    {
        qWarning() << "Applet dir" << pathName << "does not exists";
        return;
    }
    
    int added = 0;
    int modified = 0;
    
    foreach(QString appFile, appDir.entryList())
    {
        QString fileName = appDir.absoluteFilePath(appFile);
        if (!m_AppletsByFile.contains(appFile))
          {
            addFile(fileName);
            added++;
          }
    }
    foreach(DcpAppletMetadata *metadata, m_AppletsByName)
      {
        if (!metadata->isValid())
            eraseEntry(metadata);
        else
        if (metadata->isModified())
         {
             QString fileName = metadata->fileName();
             eraseEntry(metadata);
             addFile(fileName);
             modified++;
         } 
      }
    qDebug() << added << "files added" << modified << "modified";
}

void DcpAppletDb::eraseEntry(DcpAppletMetadata *metadata)
{
    m_AppletsByName.remove(metadata->name());
    m_AppletsByFile.remove(metadata->fileName());
    metadata->deleteLater();
}

void DcpAppletDb::destroy()
{
	foreach(DcpAppletMetadata *metadata, m_AppletsByName) {
		delete metadata;
	}
}

