#include "dcpappletdb.h"
#include "dcpappletmetadata.h"

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
    Q_UNUSED(pathName);
}

QList<DcpAppletMetaData*> 
DcpAppletDb::listByCategory(const QString& name)
{
    Q_UNUSED(name);
}
