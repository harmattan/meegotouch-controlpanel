#include <QObject>
#include <QGraphicsSceneMouseEvent>


#include <dcpcomponent.h>
#include "ut_dcpcomponent.h"
#include <Pages>


void Ut_DcpComponent::init()

{
    
    m_subject = new DcpComponent(0, "Some Title", 0, "Logical Id");
}

void Ut_DcpComponent::cleanup()
{
    delete m_subject;
    m_subject = 0;
}

void Ut_DcpComponent::initTestCase()
{
}

void Ut_DcpComponent::cleanupTestCase()
{
}

void Ut_DcpComponent::testSubPage()
{
    PageHandle handle(PageHandle::MAIN, "param", 3, true);
    m_subject->setSubPage(handle);
    QVERIFY(m_subject->subPage().id == handle.id);
    QVERIFY(m_subject->subPage().param == handle.param);
    QVERIFY(m_subject->subPage().widgetId == handle.widgetId);
    QVERIFY(m_subject->subPage().isStandalone == handle.isStandalone);
    
    m_subject->setSubPage(PageHandle::MAIN);
    QVERIFY(m_subject->subPage().id == PageHandle::MAIN);
    QVERIFY(m_subject->subPage().param == "");
    QVERIFY(m_subject->subPage().widgetId == -1);
    QVERIFY(!m_subject->subPage().isStandalone);
    
    m_subject->setSubPage(PageHandle::MAIN, "param");
    QVERIFY(m_subject->subPage().id == PageHandle::MAIN);
    QVERIFY(m_subject->subPage().param == "param");
    QVERIFY(m_subject->subPage().widgetId == -1);
    QVERIFY(!m_subject->subPage().isStandalone);
    
    m_subject->setSubPage(PageHandle::MAIN, "param", 1);
    QVERIFY(m_subject->subPage().id == PageHandle::MAIN);
    QVERIFY(m_subject->subPage().param == "param");
    QVERIFY(m_subject->subPage().widgetId == 1);
    QVERIFY(!m_subject->subPage().isStandalone);

    m_subject->setSubPage(PageHandle::MAIN, "param", 1, true);
    QVERIFY(m_subject->subPage().id == PageHandle::MAIN);
    QVERIFY(m_subject->subPage().param == "param");
    QVERIFY(m_subject->subPage().widgetId == 1);
    QVERIFY(m_subject->subPage().isStandalone);
}

void Ut_DcpComponent::testTitle()
{
    
    QCOMPARE(m_subject->title(), QString("Some Title"));
    QString title("Other title");
    m_subject->setTitle(title); 
    QCOMPARE(m_subject->title(), title);
}

void Ut_DcpComponent::testCategory()
{
    QVERIFY(m_subject->category() == 0);
}

void Ut_DcpComponent::testLogicalId()    
{
    QCOMPARE(m_subject->logicalId(), QString("Logical Id"));
    QString logicalId("logicalId");
    m_subject->setLogicalId(logicalId); 
    QCOMPARE(m_subject->logicalId(), logicalId);
}

void Ut_DcpComponent::testMattiID()    
{
    m_subject->setMattiID("matti id"); 
    QCOMPARE(m_subject->mattiID(), QString("matti id"));
}

QTEST_APPLESS_MAIN(Ut_DcpComponent)
