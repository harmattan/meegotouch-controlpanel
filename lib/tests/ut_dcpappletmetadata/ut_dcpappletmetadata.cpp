#include <QObject>
#include <QByteArray>

#include <DcpApplet>
#include <DcpWidgetTypes>

#include <dcpappletmetadata.h>

#include "ut_dcpappletmetadata.h"
#include "mgconfitem-fake.h"
#include "filedatas.h"

static StringMap testGood, testBad;
void Ut_DcpAppletMetadata::initTestCase()
{
    static int c = 0;
    static QByteArray arg("dummyarg");
    char *argp = arg.data();
    qap = new QCoreApplication(c, &argp);
    QString desktopDir(qApp->applicationDirPath() + 
                       "/ut_dcpappletmetadata-data/desktops/");
    desktopTestFile =  desktopDir + "test.desktop";
    desktopBadTestFile = desktopDir + "testBad.desktop";

    appletDir = "so.applet/";
    appletSo = "testapplet.so";
    testGood["Desktop Entry/Name"] = "Browser";
    testGood["Desktop Entry/Type"] = "DUIApplet";
    testGood["Desktop Entry/Icon"] = "";
    testGood["Desktop Entry/Exec"] = "";
    testGood["Desktop Entry/X-logical-id"] = "qtn_sett_main_browser";
    testGood["Desktop Entry/X-translation-catalog"] = "duisettings";
    testGood["DUI/X-DUIApplet-Applet"] = "testapplet.so";
    testGood["DUI/X-DUIApplet/ImageLandscape"] = "Widget_landscape_weather.png";
    testGood["DUI/X-DUIApplet-ImagePortrait"] = "Widget_portrait_weather.png";
    testGood["DCP/Category"] = "Application";
    testGood["DCP/Order"] = "1";
    testGood["DCP/WidgetType"] = "DcpLabel2";
    testGood["DCP/Text2"] = "firefox";
    testGood["DCP/Align"] = "RIGHT";
    testGood["DCP/Image"] = "test.png";
    testGood["DCP/Part"] = "RobiJonMegKutyaraDer";
    testGood["DCP/Parent"] = "RobiJonMegKutyaraDerII";
    fileDatas[desktopTestFile] = testGood;
    testBad["Desktop Entry/Name"] = "Browser";
    testBad["Desktop Entry/Type"] = "DUIApplet";
    testBad["Desktop Entry/Icon"] = "";
    testBad["Desktop Entry/Exec"] = "";
    testBad["Desktop Entry/X-logical-id"] = "qtn_sett_main_browser";
    testBad["Desktop Entry/X-translation-catalog"] = "duisettings";
    testBad["DUI/X-DUIApplet-Applet"] = "libexampleapplet.so";
    testBad["DUI/X-DUIApplet/ImageLandscape"] = "Widget_landscape_weather.png";
    testBad["DUI/X-DUIApplet-ImagePortrait"] = "Widget_portrait_weather.png";
    testBad["DCP/Category"] = "Application";
    testBad["DCP/Order"] = "1";
    testBad["DCP/WidgetType"] = "DcpLabel2";
    testBad["DCP/Text2"] = "firefox";
    fileDatas[desktopBadTestFile] = testBad;

}

void Ut_DcpAppletMetadata::cleanupTestCase()
{
    delete qap;
}

void Ut_DcpAppletMetadata::init()
{
    QVERIFY(m_subject = new DcpAppletMetadata(desktopTestFile));
}

void Ut_DcpAppletMetadata::cleanup()
{
    if (m_subject) {
       delete m_subject;
       m_subject = 0;
    }
}

void Ut_DcpAppletMetadata::testCreateAndDestroy()
{
    if (QTest::currentTestFailed()) return;
}

void Ut_DcpAppletMetadata::testIsValid()
{
    if (QTest::currentTestFailed()) return;

    QVERIFY(m_subject->isValid());
    delete m_subject;
    m_subject = 0;

    QWARN("\n\t----Expected QWARN: Multiple definitions of group 'M'----");
    QVERIFY((m_subject = new DcpAppletMetadata(desktopBadTestFile)));
    QVERIFY(!m_subject->isValid());
}

void Ut_DcpAppletMetadata::testIsModified()
{
    if (QTest::currentTestFailed()) return;

    QVERIFY((m_subject = new DcpAppletMetadata(desktopTestFile)));

    QVERIFY(!m_subject->isModified());

#if 0
    FIXME

    // touch the desktop file:
    QFile file(desktopTestFile);
    file.open(QIODevice::WriteOnly | QIODevice::Append);
    file.close();

    QVERIFY(m_subject->isModified());
#endif
}

void Ut_DcpAppletMetadata::testName()
{
    if (QTest::currentTestFailed()) return;

    QCOMPARE(m_subject->name(), QString("Browser"));
}
void Ut_DcpAppletMetadata::testFileName()
{
    if (QTest::currentTestFailed()) return;
    QVERIFY((m_subject = new DcpAppletMetadata(desktopTestFile)));

    QCOMPARE(m_subject->fileName(), desktopTestFile);
}

void Ut_DcpAppletMetadata::testCategory()
{
    if (QTest::currentTestFailed()) return;

    QCOMPARE(m_subject->category(), QString("Application"));
}

void Ut_DcpAppletMetadata::testBinary()
{
    if (QTest::currentTestFailed()) return;

    QCOMPARE(m_subject->binary(), QString("testapplet.so"));
}

void Ut_DcpAppletMetadata::testFullBinary()
{
    if (QTest::currentTestFailed()) return;

    QCOMPARE(m_subject->fullBinary(), appletDir + appletSo);
}

void Ut_DcpAppletMetadata::testWidgetTypeID()
{
    if (QTest::currentTestFailed()) return;

    QCOMPARE(m_subject->widgetTypeID(), static_cast<int>(DcpWidgetType::Label));
}  

void Ut_DcpAppletMetadata::testAlign()
{
    if (QTest::currentTestFailed()) return;

    QCOMPARE(m_subject->align(), Qt::AlignRight);

}

void Ut_DcpAppletMetadata::testToggle()
{
    QSKIP("!!!! UnableToLoadAnyApplet bug under fixxing by Lgal !!!!",
            SkipSingle);

    if (QTest::currentTestFailed()) return;
}

void Ut_DcpAppletMetadata::testImageName()
{
    if (QTest::currentTestFailed()) return;

    QCOMPARE(m_subject->imageName(), QString("test.png"));
}

void Ut_DcpAppletMetadata::testOrder()
{
    if (QTest::currentTestFailed()) return;

    QCOMPARE(m_subject->order(), 1);
}

void Ut_DcpAppletMetadata::testUsage()
{
    QSKIP("!!!! RelativePath bug under fixxing by Retsoft !!!!", SkipSingle);

    if (QTest::currentTestFailed()) return;

    qWarning() <<"\n@@" <<m_subject->usage() <<"@@\n";
}

void Ut_DcpAppletMetadata::testPart()
{
    if (QTest::currentTestFailed()) return;

    QCOMPARE(m_subject->part(), QString("RobiJonMegKutyaraDer"));
}


void Ut_DcpAppletMetadata::testSetGetParent()
{
    if (QTest::currentTestFailed()) return;

    m_subject->setParent(m_subject);

    QCOMPARE(m_subject, m_subject->parent());

    m_subject->setParent(0);
}

void Ut_DcpAppletMetadata::testParentName()
{
    if (QTest::currentTestFailed()) return;

    QCOMPARE(m_subject->parentName(), QString("RobiJonMegKutyaraDer_II"));
}

QTEST_APPLESS_MAIN(Ut_DcpAppletMetadata)
