#include <QObject>
#include <QGraphicsSceneMouseEvent>

#include "dcpappletobject.h"
#include "dcpappletmetadata.h"


#include "ft_dcpappletobject.h"

#define DESKTOPFILE DATADIR "/testplugin.desktop"

void Ft_DcpAppletObject::init()
{
    
    DcpAppletMetadata *metadata = new DcpAppletMetadata(DESKTOPFILE);
    m_subject = new DcpAppletObject(metadata);
    delete metadata;
}

void Ft_DcpAppletObject::cleanup()
{
    delete m_subject;
    m_subject = 0;
}

void Ft_DcpAppletObject::initTestCase()
{
}

void Ft_DcpAppletObject::cleanupTestCase()
{
}

void Ft_DcpAppletObject::testLoad()
{
}

void Ft_DcpAppletObject::testLoadManyTimes()
{
    delete m_subject;
    DcpAppletMetadata *metadata = new DcpAppletMetadata(DESKTOPFILE);
    m_subject = new DcpAppletObject(metadata);
}

QTEST_MAIN(Ft_DcpAppletObject)
