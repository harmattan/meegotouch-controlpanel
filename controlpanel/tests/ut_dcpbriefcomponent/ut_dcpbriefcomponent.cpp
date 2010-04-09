#include <QObject>
#include <QGraphicsSceneMouseEvent>
#include <QStringList>
#include <dcpbriefcomponent.h>


#include "ut_dcpbriefcomponent.h"
#include "dcpappletobject.h"
#include "dcpappletmetadata.h"
void Ut_DcpBriefComponent::init()
{
    m_applet = new DcpAppletObject(new DcpAppletMetadata("fake"));
    m_subject = new DcpBriefComponent(m_applet,0,"");
}

void Ut_DcpBriefComponent::cleanup()
{
    delete m_subject;
    delete m_applet;
    m_subject = 0;
}

void Ut_DcpBriefComponent::initTestCase()
{
    QSKIP("incomplete", SkipSingle);   // remove this when you've finished
}

void Ut_DcpBriefComponent::cleanupTestCase()
{
}

void Ut_DcpBriefComponent::testCreation()
{
    QSKIP("incomplete", SkipSingle);   // remove this when you've finished
}

void Ut_DcpBriefComponent::testApplet()
{
    QSKIP("incomplete", SkipSingle);   // remove this when you've finished
}

void Ut_DcpBriefComponent::testActivate()
{
    QSKIP("incomplete", SkipSingle);   // remove this when you've finished
}


QTEST_APPLESS_MAIN(Ut_DcpBriefComponent)
