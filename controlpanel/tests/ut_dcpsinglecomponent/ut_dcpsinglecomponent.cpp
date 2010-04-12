#include <QObject>

#include <QGraphicsSceneMouseEvent>

#include <dcpsinglecomponent.h>


#include "ut_dcpsinglecomponent.h"

void Ut_DcpSingleComponent::init()
{
    m_subject = new DcpSingleComponent(0, "Logical ID", "title1", "title2");
}

void Ut_DcpSingleComponent::cleanup()
{
    delete m_subject;
    m_subject = 0;
}

void Ut_DcpSingleComponent::initTestCase()
{
}

void Ut_DcpSingleComponent::cleanupTestCase()
{
}

void Ut_DcpSingleComponent::testCreation()
{
//    QVERIFY(m_subject);
}

void Ut_DcpSingleComponent::testTitle()
{
    QVERIFY(m_subject->title() == "title1");
    m_subject->setTitle("another title");
    QVERIFY(m_subject->title() == "another title");
}

void Ut_DcpSingleComponent::testSubtitle()
{
    QSKIP("incomplete", SkipSingle);   // remove this when you've finished
}

void Ut_DcpSingleComponent::testActivate()
{
    QSKIP("incomplete", SkipSingle);   // remove this when you've finished
}


QTEST_APPLESS_MAIN(Ut_DcpSingleComponent)
