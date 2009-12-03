#include <QObject>
#include <QGraphicsSceneMouseEvent>
#include <QDir>
#include <QMap>

#include "dcpappletdb.h"
#include "dcpappletmetadata.h"

#include "ut_dcpappletdb.h"

// mocking DcpAppletMetadata functions
static QMap<const DcpAppletMetadata *, int> appletStat;

void DcpAppletMetadata::slotClicked()
{
    ++appletStat[this];
}

int DcpAppletMetadata::usage() const
{
    return appletStat.value(this);
}

///////////////////////////////////////////////////////////////

void Ut_DcpAppletDb::initTestCase()
{
    static int c = 0;
    static QByteArray arg("dummyarg");
    char *argp = arg.data();
    qap = new QCoreApplication(c, &argp);
    QString dataDir(qApp->applicationDirPath() + 
                       "/ut_dcpappletdb-data/");

    emptyDesktopDir = dataDir + "emptyDesktopDir/"; // a non-existent dir
    testDesktopDir = dataDir + "desktops/";
    testDesktopDir2 = dataDir + "desktops2/";
    testDesktopDir3 = dataDir + "desktops3/";
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
    delete qap;
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

    QVERIFY((m_subject==DcpAppletDb::instance()));
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
    m_subject->addPath(testDesktopDir3);
    DcpAppletMetadataList applets = m_subject->list();
    const int maxN = 10;
    int n = 0;
    for (DcpAppletMetadataList::iterator iter = applets.begin();
         iter != applets.end() && n < maxN; ++iter) {
        // "activate" applet n times
        for (int i = 0; i < n; ++i) {
            (*iter)->slotClicked();
        }
        ++n;
    }

    // most used list shall reverse the first n applets in the list
    DcpAppletMetadataList mostUsed = m_subject->listMostUsed();
    DcpAppletMetadataList::iterator orig = applets.begin() + n - 1;
    for (DcpAppletMetadataList::iterator iter = mostUsed.begin();
         iter != mostUsed.end() && orig != applets.end(); ++iter) {
        QCOMPARE(*iter, *orig);
        --orig;
    }
}

void Ut_DcpAppletDb::testRefresh()
{
    if (QTest::currentTestFailed()) return;

    QSKIP("!!!! Some things are missing, waiting for Lgal !!!!",SkipSingle);
}

QTEST_APPLESS_MAIN(Ut_DcpAppletDb)
