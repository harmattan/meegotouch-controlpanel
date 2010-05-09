#include <QObject>
#include <QGraphicsSceneMouseEvent>

#include <dcpwidget.h>
#include <dcpwidget_p.h>


#include "ut_dcpwidget.h"

void Ut_DcpWidget::init()
{
    m_subject = new DcpWidget();
}

void Ut_DcpWidget::cleanup()
{
    delete m_subject;
    m_subject = 0;
}

void Ut_DcpWidget::initTestCase()
{
}

void Ut_DcpWidget::cleanupTestCase()
{
}

void Ut_DcpWidget::testCreation()
{
    QVERIFY(m_subject);
}

void Ut_DcpWidget::testWidgetId()
{
    QCOMPARE(m_subject->d_ptr->m_WidgetId, -1);
    QVERIFY(m_subject->setWidgetId(1));
    QCOMPARE(m_subject->d_ptr->m_WidgetId, 1);
    QCOMPARE(m_subject->getWidgetId(), 1);
    QVERIFY(!m_subject->setWidgetId(10)); // already set
}

void Ut_DcpWidget::testBack()
{
    QVERIFY(m_subject->back()); // default behaviour
}

void Ut_DcpWidget::testPagePans()
{
    QVERIFY(m_subject->pagePans()); // default behaviour
}


QTEST_MAIN(Ut_DcpWidget)
