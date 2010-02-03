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
    PageHandle handle(PageHandle::MAIN, "param", 0, true);
    m_subject->setSubPage(handle);
    QCOMPARE(m_subject->subPage().id, handle.id);
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
}

void Ft_DcpComponent::testLogicalId()    
{
    QCOMPARE(m_subject->logicalId(), m_LogicalId);
    QString logicalId("logicalId");
    m_subject->setLogicalId(logicalId); 
    QCOMPARE(m_subject->logicalId(), logicalId);
}

QTEST_MAIN(Ft_DcpComponent)
