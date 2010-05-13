#include "dcpwrongapplets.h"

#include "ut_dcpwrongapplets.h"
#include "dcpwrongapplets.h"

// this is because we test internal functions also which are not exported:
#include "dcpwrongapplets.cpp"

void Ut_DcpWrongApplets::init()
{
}

void Ut_DcpWrongApplets::cleanup()
{
}

void Ut_DcpWrongApplets::initTestCase()
{
}

void Ut_DcpWrongApplets::cleanupTestCase()
{
}

void Ut_DcpWrongApplets::testBacktraceLineIsAnApplet()
{
    // a matching line:
    const char* line = "065 /manni/usr/lib/duicontrolpanel/applets/libss.so.4"
                        "(_ZN12QApplication15x11ProcessEventEP7_XEvent+0x1311)"
                        " [0xf69ec481]";
    const char* start;
    const char* end;
    bool result = backtrace_line_is_an_applet(line, &start, &end);
    QCOMPARE (result, true);
    QCOMPARE ((int)((start-line)/sizeof(char)), 10);
    QCOMPARE ((int)((end-line)/sizeof(char)), 53);

    // a non matching line:
    line = "065 /usr/lib/libQtGui.so.4(_ZN12QApplication15x"
           "11ProcessEventEP7_XEvent+0x1311) [0xf69ec481]";
    result = backtrace_line_is_an_applet(line, &start, &end);
    QCOMPARE (result, false);
    QCOMPARE (start, (char*)0);
}


void Ut_DcpWrongApplets::testMarkAppletAsBad()
{
    const char* path = "/usr/lib/duicontrolpanel/applets/libtralalal.so";
    mark_applet_as_bad (path);
    QString date = MGConfItem(keyPath + path + KEY_SEPARATOR +
                              "CrashDateTime").value().toString();
    QVERIFY (!date.isEmpty());
}



void Ut_DcpWrongApplets::testSomeCrashHappened()
{
    bool result = some_crash_happened();

    // it found the applet:
    QCOMPARE (result, true);

    // the applet was marked bad:
    const char* path = "/usr/lib/duicontrolpanel/applets/libss.so.4";
    QString date = MGConfItem(keyPath + path + KEY_SEPARATOR +
                              "CrashDateTime").value().toString();
    QVERIFY (!date.isEmpty());

    // TODO: test with a crash which does not contain an applet reference
}


void Ut_DcpWrongApplets::testTerminationSignalHandler()
{
    QSKIP("Not implemented.", SkipAll);
}


void Ut_DcpWrongApplets::testQueryBadApplets()
{
    QSKIP("Not implemented.", SkipAll);
}


void Ut_DcpWrongApplets::testConstructor()
{
    QSKIP("Not implemented.", SkipAll);
}


void Ut_DcpWrongApplets::testInstanceNDestroy()
{
    QSKIP("Not implemented.", SkipAll);
}


void Ut_DcpWrongApplets::testIsAppletRecentlyCrashed()
{
    QSKIP("Not implemented.", SkipAll);
}


void Ut_DcpWrongApplets::testDisable()
{
    QSKIP("Not implemented.", SkipAll);
}


void Ut_DcpWrongApplets::testGConfRecursiveRemove()
{
    QSKIP("Not implemented.", SkipAll);
}


void Ut_DcpWrongApplets::testRemoveBadsOnDcpTimeStampChange()
{
    QSKIP("Not implemented.", SkipAll);
}

QTEST_MAIN(Ut_DcpWrongApplets)

