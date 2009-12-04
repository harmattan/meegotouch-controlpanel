#include <QString>

#include <dcpmostusedcounter.h>


#include "ut_dcpmostusedcounter.h"
#include "duigconfitem-fake.h"


void Ut_DcpMostUsedCounter::init()
{
    m_subject = MostUsedCounter::instance();
}

void Ut_DcpMostUsedCounter::cleanup()
{
    MostUsedCounter::destroy();
    m_subject = 0;
}

void Ut_DcpMostUsedCounter::initTestCase()
{
}

void Ut_DcpMostUsedCounter::cleanupTestCase()
{
}

void Ut_DcpMostUsedCounter::testAddToEmpty()
{
    const QString key("/foo");
    QCOMPARE(m_subject->get(key), 0);
    m_subject->add(key);
    QCOMPARE(m_subject->get(key), 1);
}

void Ut_DcpMostUsedCounter::testAddMultipleTimes()
{
    const QString key("/foo");
    const int n = 100;
    for (int i = 0; i < n; ++i) {
        m_subject->add(key);
        QCOMPARE(m_subject->get(key), i + 1);
    }
}

void Ut_DcpMostUsedCounter::testClearNonAdded()
{
    const QString key1("/foo");
    const QString key2("/bar");

    m_subject->clear(key1);
    QCOMPARE(m_subject->get(key1), 0);

    m_subject->add(key2);
    m_subject->clear(key1);
    QCOMPARE(m_subject->get(key1), 0);
    QCOMPARE(m_subject->get(key2), 1);
}

void Ut_DcpMostUsedCounter::testClearAdded()
{
    const QString key1("/foo");
    const QString key2("/bar");

    m_subject->add(key1);
    m_subject->clear(key1);
    QCOMPARE(m_subject->get(key1), 0);

    m_subject->add(key1);
    m_subject->add(key2);
    m_subject->clear(key1);
    QCOMPARE(m_subject->get(key1), 0);
    QCOMPARE(m_subject->get(key2), 1);
}

QTEST_MAIN(Ut_DcpMostUsedCounter)
