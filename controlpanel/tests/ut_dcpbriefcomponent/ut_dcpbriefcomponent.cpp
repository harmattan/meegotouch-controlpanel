#include <QObject>
#include <QGraphicsSceneMouseEvent>
#include <dcpbriefcomponent.h>
#include <dcpbriefwidget.h>


#include "ut_dcpbriefcomponent.h"
#include "dcpappletobject.h"
#include "dcpappletmetadata.h"
#include "dcppage.h"
#include "pagefactory.h"

void Ut_DcpBriefComponent::init()
{
    m_applet = new DcpAppletObject(new DcpAppletMetadata("fake"));
    m_subject = new DcpBriefComponent(m_applet,0,"");
    m_subject->setSubPage(PageHandle::APPLET, "fake");
}

void Ut_DcpBriefComponent::cleanup()
{
    delete m_subject;
    delete m_applet;
    m_subject = 0;
}

void Ut_DcpBriefComponent::initTestCase()
{
}

void Ut_DcpBriefComponent::cleanupTestCase()
{
}

void Ut_DcpBriefComponent::testCreation()
{
    QVERIFY(m_subject);
    QVERIFY(m_subject->m_BriefWidget);
}

void Ut_DcpBriefComponent::testApplet()
{
    QVERIFY(m_subject);
    QCOMPARE((void*)(m_subject->m_BriefWidget->applet()), (void*)m_applet);
}

void Ut_DcpBriefComponent::testActivate()
{
    DcpPage *page = PageFactory::instance()->currentPage();
    QVERIFY(page == 0);
    m_subject->activate();
    page = PageFactory::instance()->currentPage();
    QVERIFY(page->handle().id == PageHandle::APPLET);
    QVERIFY(page->handle().param == "fake");
}


QTEST_APPLESS_MAIN(Ut_DcpBriefComponent)
