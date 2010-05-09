#include <QObject>
#include <QGraphicsSceneMouseEvent>
#include <QSignalSpy>

#include <dcpbrief.h>


#include "ut_dcpbrief.h"
#include "dcpwidgettypes.h"

void Ut_DcpBrief::init()
{
    m_subject = new DcpBrief();
}

void Ut_DcpBrief::cleanup()
{
    delete m_subject;
    m_subject = 0;
}

void Ut_DcpBrief::initTestCase()
{
}

void Ut_DcpBrief::cleanupTestCase()
{
}

void Ut_DcpBrief::testCreation()
{
    QVERIFY(m_subject);
}

void Ut_DcpBrief::testWidgetTypeID()
{
    QVERIFY(m_subject->widgetTypeID() == DcpWidgetType::BriefInvalid);
}

void Ut_DcpBrief::testValueText()
{
    QCOMPARE(m_subject->valueText(), QString());
}

void Ut_DcpBrief::testIcon()
{
    QCOMPARE(m_subject->icon(), QString());
}

void Ut_DcpBrief::testToggleIconId()
{
    QCOMPARE(m_subject->toggleIconId(), QString());
}

void Ut_DcpBrief::testAlign()
{
    QCOMPARE(m_subject->align(), Qt::AlignLeft);
}

void Ut_DcpBrief::testToggle()
{
    QVERIFY(!m_subject->toggle());
}

void Ut_DcpBrief::testImage()
{
    QCOMPARE(m_subject->image(), QString());
}

void Ut_DcpBrief::testActivate()
{
    QSignalSpy spy(m_subject, SIGNAL(activateSignal()));
    QCOMPARE(spy.count(), 0);
    m_subject->activate();
    QCOMPARE(spy.count(), 1);
    m_subject->activate();
    QCOMPARE(spy.count(), 2);

}

void Ut_DcpBrief::testTitleText()
{
    QCOMPARE(m_subject->titleText(), QString());
}


QTEST_APPLESS_MAIN(Ut_DcpBrief)
