#ifndef UT_DCPWRONGAPPLETS_H
#define UT_DCPWRONGAPPLETS_H

#include <QtTest/QtTest>
#include <QObject>

class Ut_DcpWrongApplets : public QObject
{
    Q_OBJECT

private slots:
    void init();
    void cleanup();
    void initTestCase();
    void cleanupTestCase();

    void testBacktraceLineIsAnApplet();
    void testMarkAppletAsBad();
    void testSomeCrashHappened();
//    void testTerminationSignalHandler();
    void testQueryBadApplets();
    void testDisabled();
    void testInstanceNDestroy();
    void testIsAppletRecentlyCrashed();
    void testGConfRecursiveRemove();
    void testRemoveBadsOnDcpTimeStampChange();
};

#endif
