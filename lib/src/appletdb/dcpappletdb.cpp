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
    m_HasUniqueMetadata = false;
    if (!pathName.isEmpty()){
        addPath(pathName);
    }
}

DcpAppletDb::~DcpAppletDb()
{
}

void DcpAppletDb::destroy()
{
     sm_Instance->destroyData();
     delete sm_Instance;
     sm_Instance = 0;
}

bool
DcpAppletDb::addFile(const QString& filename)
{
 if (containsFile(filename) || m_HasUniqueMetadata)
    return false;

  DcpAppletMetadata *metadata = new DcpAppletMetadata(filename);
  if (metadata->isValid())
    {
        if (metadata->isUnique())
        {
             m_AppletsByName.clear();   
             m_AppletsByFile.clear();   
             m_HasUniqueMetadata = true;

        }
        m_AppletsByName[metadata->name()] = metadata;
        m_AppletsByFile[filename] = metadata;
        return true;
    }
  else {
    metadata->deleteLater();
  }
  return false;
}

QStringList
DcpAppletDb::appletNames() const
{
    return m_AppletsByName.keys();
}

bool
DcpAppletDb::containsFile(const QString& fileName)
{
    return m_AppletsByFile.contains(fileName);
}

bool
DcpAppletDb::containsName(const QString& name)
{
    return m_AppletsByName.contains(name);
}

bool
DcpAppletDb::addPath(const QString &pathName)
{
    if (addFiles (pathName, "*.desktop")) {
        m_Paths.append(pathName);
        return true;
    } else {
        return false;
    }
}

bool
DcpAppletDb::addFiles(const QString& pathName, const QString& filter)
{
    QDir appDir(pathName); 
    foreach(QString appFile, appDir.entryList(QStringList(filter)))
    {
        if (!addFile(appDir.absoluteFilePath(appFile)))
              return false;
    }
    return true;
}

DcpAppletMetadataList DcpAppletDb::listByCategory(const QString& category)
{
    QList<DcpAppletMetadata*> filtered;

    foreach (DcpAppletMetadata *item, m_AppletsByFile) {
        if (category.compare(item->category(),Qt::CaseInsensitive) == 0)
            filtered.append(item);
        QString parentName = item->parentName();

        if (parentName != "" && !item->parent()) {
            item->setParent(applet(parentName));  
        }
    }
    qSort(filtered.begin(), filtered.end(), DcpAppletMetadata::orderLessThan);
    return filtered;
}

DcpAppletMetadataList DcpAppletDb::listMostUsed()
{
	DcpAppletMetadataList mostUsed;
	for (QMap<QString, DcpAppletMetadata*>::iterator iter = m_AppletsByName.begin(); iter != m_AppletsByName.end(); iter++)
		if (iter.value()->usage())
			mostUsed.push_back(iter.value());

   qSort(mostUsed.begin(), mostUsed.end(), DcpAppletMetadata::usageGreatherThan); 
   return mostUsed.mid(0, DcpApplet::MaxMostUsed);
}

DcpAppletMetadata* DcpAppletDb::applet(const QString& name)
{
    DcpAppletMetadata *metadata = m_AppletsByName.value(name, 0);
    if (!metadata)
        qWarning() << "No such applet:" << name;
    return metadata;
};

void DcpAppletDb::refresh()
{
    foreach(QString pathName, m_Paths)
        refreshPath(pathName);

    foreach(DcpAppletMetadata *metadata, m_AppletsByName) {
        if (!metadata->isValid()) {
            eraseEntry(metadata);
        } else if (metadata->isModified()) {
             QString fileName = metadata->fileName();
             eraseEntry(metadata);
             addFile(fileName);
        } 
    }
}

void DcpAppletDb::refreshPath(const QString &pathName)
{

    QDir appDir(pathName, APPLETFILTER);
    if (!appDir.exists()) {
        qWarning() << "Applet dir" << pathName << "does not exists";
        return;
    }
    
    foreach(QString appFile, appDir.entryList()) {
        QString fileName = appDir.absoluteFilePath(appFile);
        if (!m_AppletsByFile.contains(appFile)) {
            addFile(fileName);
        }
    }
}

void DcpAppletDb::eraseEntry(DcpAppletMetadata *metadata)
{
    m_AppletsByName.remove(metadata->name());
    m_AppletsByFile.remove(metadata->fileName());
    metadata->deleteLater();
}

void DcpAppletDb::destroyData()
{
	foreach(DcpAppletMetadata *metadata, m_AppletsByName) {
		metadata->deleteLater();
	}
}

