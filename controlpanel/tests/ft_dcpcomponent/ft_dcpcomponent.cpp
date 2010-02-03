#include <QObject>
#include <QGraphicsSceneMouseEvent>


#include <dcpcomponent.h>
#include "ft_dcpcomponent.h"
#include <Pages>

DcpSingleComponent::DcpSingleComponent(DcpCategory *category,
                                  const QString& title,
                                  QGraphicsWidget *parent,
                                  const QString& logicalId)
    : DcpComponent(category, title, parent, logicalId)
{}

void DcpSingleComponent::add(DcpComponent *component)
{
    
   Q_UNUSED(component);
}

void DcpSingleComponent::remove(DcpComponent *component)
{
   Q_UNUSED(component);
}

void DcpSingleComponent::createContents()
{
}

void Ft_DcpComponent::init()

{
    
    m_subject = new DcpSingleComponent(m_Category, m_Title, m_Parent,
                                       m_LogicalId);
}

void Ft_DcpComponent::cleanup()
{
    delete m_subject;
    m_subject = 0;
}

void Ft_DcpComponent::initTestCase()
{
    m_Category = 0;
    m_Title = QString("Some Title");
    m_Parent = 0;
    m_LogicalId = QString("Logical Id");
}

void Ft_DcpComponent::cleanupTestCase()
{
}

void Ft_DcpComponent::testSubPage()
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

void Ft_DcpComponent::testTitle()
{
    
    QCOMPARE(m_subject->title(), m_Title);
    QString title("Other title");
    m_subject->setTitle(title); 
    QCOMPARE(m_subject->title(), title);
}

void Ft_DcpComponent::testCategory()
{
    QCOMPARE(m_subject->category(), m_Category);
}

void Ft_DcpComponent::testChild()
{
    QVERIFY(m_subject->child(0) == 0);
    QVERIFY(m_subject->child(1) == 0);
    QVERIFY(m_subject->child(100) == 0);
}

void Ft_DcpComponent::testLogicalId()    
{
    QCOMPARE(m_subject->logicalId(), m_LogicalId);
    QString logicalId("logicalId");
    m_subject->setLogicalId(logicalId); 
    QCOMPARE(m_subject->logicalId(), logicalId);
}

QTEST_MAIN(Ft_DcpComponent)
