#include <QObject>
#include <QGraphicsSceneMouseEvent>
#include <DuiApplication>
#include <dcppage.h>

#include "ft_dcppage.h"

void Ft_DcpPage::init()
{
    m_subject = new DcpPage();
}

void Ft_DcpPage::cleanup()
{
    delete m_subject;
    m_subject = 0;
}

void Ft_DcpPage::initTestCase()
{
}


void Ft_DcpPage::cleanupTestCase()
{
}
void Ft_DcpPage::testCreateContents()
{
    m_subject->createContent();
    QVERIFY(m_subject->objectName() == "DcpPage");
    
}
void Ft_DcpPage::testHandle()
{
    PageHandle handle(PageHandle::MAIN, "param", 1, true);
    m_subject->setHandle(handle); 
    PageHandle result = m_subject->handle();
    QVERIFY(result.id == PageHandle::MAIN);
    QVERIFY(result.param == "param");
    QVERIFY(result.widgetId == 1);
    QVERIFY(result.isStandalone == true);
    
    m_subject->setHandle(PageHandle::APPLET, "test"); 
    PageHandle result1 = m_subject->handle();
    QVERIFY(result1.id == PageHandle::APPLET);
    QVERIFY(result1.param == "test");
    QVERIFY(result1.widgetId == -1);
    QVERIFY(result1.isStandalone == false);

}
void Ft_DcpPage::testReferer()
{
    PageHandle handle(PageHandle::MAIN, "param", 1, true);
    m_subject->setReferer(handle); 
    PageHandle result = m_subject->referer();
    QVERIFY(result.id == PageHandle::MAIN);
    QVERIFY(result.param == "param");
    QVERIFY(result.widgetId == 1);
    QVERIFY(result.isStandalone == true);
    
    m_subject->setReferer(PageHandle::APPLET, "test"); 
    PageHandle result1 = m_subject->referer();
    QVERIFY(result1.id == PageHandle::APPLET);
    QVERIFY(result1.param == "test");
    QVERIFY(result1.widgetId == -1);
    QVERIFY(result1.isStandalone == false);

}
void Ft_DcpPage::testMainLayout()
{
    QVERIFY(m_subject->mainLayout() == 
        (QGraphicsLinearLayout*)(m_subject->centralWidget()->layout()));
}

QTEST_MAIN(Ft_DcpPage)
