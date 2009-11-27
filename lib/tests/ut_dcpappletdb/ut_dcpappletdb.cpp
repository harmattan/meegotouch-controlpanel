#include <QObject>
#include <QGraphicsSceneMouseEvent>
#include <QDir>

#include "dcpappletdb.h"

#include "ut_dcpappletdb.h"

void Ut_DcpAppletDb::initTestCase()
{
    emptyDesktopDir = DATADIR "/emptyDesktopDir/";
    testDesktopDir = DATADIR "/desktops/";
    testDesktopDir2 = DATADIR "/desktops2/";
    testDesktopDir3 = DATADIR "/desktops3/";
    desktopTestFile = testDesktopDir+"test.desktop";
    desktopTestFile2 = testDesktopDir+"test2.desktop";
    desktopDateTimeFile = testDesktopDir2+"datetime.desktop";
    desktopDisplayFile = testDesktopDir2+"display.desktop";
    browserEntryName="Browser";
    datetimeEntryName="Date & Time";
    displayEntryName="Display";
}

void Ut_DcpAppletDb::cleanupTestCase()
{
}

void Ut_DcpAppletDb::init()
{
    QVERIFY((m_subject=DcpAppletDb::initInstance(emptyDesktopDir)));
}

void Ut_DcpAppletDb::cleanup()
{
    DcpAppletDb::destroy();
}

void Ut_DcpAppletDb::testCreateAndDestroy()
{
    if (QTest::currentTestFailed()) return;
}

void Ut_DcpAppletDb::testInstance()
{
    if (QTest::currentTestFailed()) return;

    QVERIFY((m_subject==DcpAppletDb::initInstance(emptyDesktopDir)));
}

void Ut_DcpAppletDb::testAddContainNameFile()
{
    if (QTest::currentTestFailed()) return;

    QVERIFY(!m_subject->containsFile(desktopTestFile));

    QVERIFY(m_subject->addFile(desktopTestFile));
    QVERIFY(m_subject->containsFile(desktopTestFile));

    QVERIFY(!m_subject->addFile(desktopTestFile));
    /* this test was commented out because current implementation
     * requires that two applets with same name can be loaded.
     * eg. display language for controlpanel and for suw */
//    QVERIFY(!m_subject->addFile(desktopTestFile2));

    QVERIFY(m_subject->containsName(browserEntryName));
    QVERIFY(!m_subject->containsName(browserEntryName)+"x");
}

void Ut_DcpAppletDb::testAddPath()
{
    if (QTest::currentTestFailed()) return;

    QWARN("!!!! lgal is going to do better addPath [addPath!=constructor] !!!!");

    QVERIFY(m_subject->addPath(testDesktopDir2));
    QVERIFY(m_subject->containsFile(desktopDateTimeFile));
    QVERIFY(m_subject->containsFile(desktopDisplayFile));
}

void Ut_DcpAppletDb::testAppletNames()
{
    if (QTest::currentTestFailed()) return;

    QVERIFY(m_subject->addPath(testDesktopDir2));

    QVERIFY(m_subject->appletNames().length()==2);
    QVERIFY(m_subject->appletNames().contains(datetimeEntryName));
    QVERIFY(m_subject->appletNames().contains(displayEntryName));
}

void Ut_DcpAppletDb::testApplet()
{
    if (QTest::currentTestFailed()) return;

    QVERIFY(m_subject->addPath(testDesktopDir2));

    QWARN("\n\t ---- Expected QWARN : No such applet: 'xxx' ----");
    QVERIFY(m_subject->applet(displayEntryName));
    QVERIFY(m_subject->applet(datetimeEntryName));
    QVERIFY(!m_subject->applet("xxx"));
}

void Ut_DcpAppletDb::testEraseEntry()
{
    if (QTest::currentTestFailed()) return;

    DcpAppletMetadata *metadata;

    QVERIFY(m_subject->addPath(testDesktopDir2));
    QVERIFY(m_subject->appletNames().length()==2);
    QVERIFY((metadata=m_subject->applet(datetimeEntryName)));
    m_subject->eraseEntry(metadata);
    QVERIFY(m_subject->appletNames().length()==1);
}

void Ut_DcpAppletDb::testListByCategory()
{
    if (QTest::currentTestFailed()) return;

    QVERIFY(m_subject->addPath(testDesktopDir3));
    QVERIFY(m_subject->listByCategory("Application").length()==1);
    QVERIFY(m_subject->listByCategory("Connectivity").length()==1);
    QVERIFY(m_subject->listByCategory("Device utilities").length()==1);
    QVERIFY(m_subject->listByCategory("Look & Feel").length()==3);
    QVERIFY(m_subject->listByCategory("Regional settings").length()==3);
    QVERIFY(m_subject->listByCategory("Sound").length()==2);
    QVERIFY(m_subject->listByCategory("Startup").length()==4);
}

void Ut_DcpAppletDb::testListMostUsed()
{
    if (QTest::currentTestFailed()) return;

    QSKIP("ListMostUsed can't be tested",SkipSingle);
}

void Ut_DcpAppletDb::testRefresh()
{
    if (QTest::currentTestFailed()) return;

    QSKIP("!!!! Some things are missing, waiting for Lgal !!!!",SkipSingle);
}

QTEST_APPLESS_MAIN(Ut_DcpAppletDb)
