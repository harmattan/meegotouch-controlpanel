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
    QCOMPARE(m_subject->getUsageCounter(key), 0);
    m_subject->incrementUsageCounter(key);
    QCOMPARE(m_subject->getUsageCounter(key), 1);
}

void Ut_DcpMostUsedCounter::testAddMultipleTimes()
{
    const QString key("/foo");
    const int n = 100;
    for (int i = 0; i < n; ++i) {
        m_subject->incrementUsageCounter(key);
        QCOMPARE(m_subject->getUsageCounter(key), i + 1);
    }
}

void Ut_DcpMostUsedCounter::testClearNonAdded()
{
    const QString key1("/foo");
    const QString key2("/bar");

    m_subject->dropKey (key1);
    QCOMPARE(m_subject->getUsageCounter(key1), 0);

    m_subject->incrementUsageCounter(key2);
    m_subject->dropKey (key1);
    QCOMPARE(m_subject->getUsageCounter(key1), 0);
    QCOMPARE(m_subject->getUsageCounter(key2), 1);
}

void Ut_DcpMostUsedCounter::testClearAdded()
{
    const QString key1("/foo");
    const QString key2("/bar");

    m_subject->incrementUsageCounter(key1);
    m_subject->dropKey (key1);
    QCOMPARE(m_subject->getUsageCounter(key1), 0);

    m_subject->incrementUsageCounter(key1);
    m_subject->incrementUsageCounter(key2);
    m_subject->dropKey (key1);
    QCOMPARE(m_subject->getUsageCounter(key1), 0);
    QCOMPARE(m_subject->getUsageCounter(key2), 1);
}

QTEST_MAIN(Ut_DcpMostUsedCounter)
