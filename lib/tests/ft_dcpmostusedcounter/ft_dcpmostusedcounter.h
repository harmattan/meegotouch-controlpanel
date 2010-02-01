#ifndef FT_DCPMOSTUSEDCOUNTER_H
#define FT_DCPMOSTUSEDCOUNTER_H

#include <QtTest/QtTest>
#include <QObject>

// the real unit/DcpMostUsedCounter class declaration
#include <dcpmostusedcounter.h>

Q_DECLARE_METATYPE(MostUsedCounter*);

class Ft_DcpMostUsedCounter : public QObject
{
    Q_OBJECT

private slots:
    void init();
    void cleanup();
    void initTestCase();
    void cleanupTestCase();

    void testAddToEmpty();
    void testAddMultipleTimes();
    void testClearNonAdded();
    void testClearAdded();

private:
    MostUsedCounter* m_subject;
};

#endif
