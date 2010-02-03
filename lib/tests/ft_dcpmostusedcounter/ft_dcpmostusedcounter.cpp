#include <QString>

#include <dcpmostusedcounter.h>


#include "ft_dcpmostusedcounter.h"
#include <DuiGConfItem>


void Ft_DcpMostUsedCounter::init()
{
    printf("\n" MOSTUSEDCOUNTER_GCONFKEY "/foo\n");
    DuiGConfItem foo(MOSTUSEDCOUNTER_GCONFKEY "/foo");
    DuiGConfItem bar(MOSTUSEDCOUNTER_GCONFKEY "/bar");
    foo.set(0);
    bar.set(0);
    m_subject = MostUsedCounter::instance();
}

void Ft_DcpMostUsedCounter::cleanup()
{
    MostUsedCounter::destroy();
    m_subject = 0;
}

void Ft_DcpMostUsedCounter::initTestCase()
{
}

void Ft_DcpMostUsedCounter::cleanupTestCase()
{
}

void Ft_DcpMostUsedCounter::testAddToEmpty()
{
    const QString key("foo");
    QCOMPARE(m_subject->getUsageCount(key), 0);
    m_subject->incrementUsageCount(key);
    QCOMPARE(m_subject->getUsageCount(key), 1);
}

void Ft_DcpMostUsedCounter::testAddMultipleTimes()
{
    const QString key("foo");
    const int n = 100;
    QCOMPARE(m_subject->getUsageCount(key), 0);

    for (int i = 1; i < n; ++i) {
        m_subject->incrementUsageCount(key);
        QCOMPARE(m_subject->getUsageCount(key), i);
    }
}

void Ft_DcpMostUsedCounter::testClearNonAdded()
{
    const QString key1("foo");
    const QString key2("bar");

    m_subject->dropKey (key1);
    QCOMPARE(m_subject->getUsageCount(key1), 0);

    m_subject->incrementUsageCount(key2);
    m_subject->dropKey (key1);
    QCOMPARE(m_subject->getUsageCount(key1), 0);
    QCOMPARE(m_subject->getUsageCount(key2), 1);
}

void Ft_DcpMostUsedCounter::testClearAdded()
{
    const QString key1("foo");
    const QString key2("bar");

    m_subject->incrementUsageCount(key1);
    m_subject->dropKey (key1);
    QCOMPARE(m_subject->getUsageCount(key1), 0);

    m_subject->incrementUsageCount(key1);
    m_subject->incrementUsageCount(key2);
    m_subject->dropKey (key1);
    QCOMPARE(m_subject->getUsageCount(key1), 0);
    QCOMPARE(m_subject->getUsageCount(key2), 1);
}

QTEST_MAIN(Ft_DcpMostUsedCounter)

