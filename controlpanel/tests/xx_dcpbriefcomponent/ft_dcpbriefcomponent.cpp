#include <QObject>
#include <QGraphicsSceneMouseEvent>
#include <QSignalSpy>

#include "dcpbriefcomponent.h"
#include "dcpbriefwidget.h"


#include "ft_dcpbriefcomponent.h"
#include "dcpappletobject.h"
#include "dcpappletmetadata.h"
#include "dcppage.h"
#include "pagefactory.h"

void Ft_DcpBriefComponent::init()
{
    m_applet = new DcpAppletObject(new DcpAppletMetadata("fake"));
    m_subject = new DcpBriefComponent(m_applet,0,"");
    m_subject->setSubPage(PageHandle::APPLET, "fake");
}

void Ft_DcpBriefComponent::cleanup()
{
    delete m_subject;
    delete m_applet;
    m_subject = 0;
}

void Ft_DcpBriefComponent::initTestCase()
{
}

void Ft_DcpBriefComponent::cleanupTestCase()
{
}

void Ft_DcpBriefComponent::testCreation()
{
    QVERIFY(m_subject);
}

QTEST_APPLESS_MAIN(Ft_DcpBriefComponent)
