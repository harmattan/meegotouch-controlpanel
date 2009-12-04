#include <QObject>
#include <QByteArray>

#include <DcpApplet>
#include <DcpWidgetTypes>

#include <dcpappletmetadata.h>

#include "ut_dcpappletmetadata.h"
#include "duigconfitem-fake.h"

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

    appletDir="so.applet/";appletSo="testapplet.so";
}

void Ut_DcpAppletMetadata::cleanupTestCase()
{
    delete qap;
}

void Ut_DcpAppletMetadata::init()
{
    QVERIFY(m_subject=new DcpAppletMetadata(desktopTestFile));
}

void Ut_DcpAppletMetadata::cleanup()
{
    if (m_subject) {
       delete m_subject;
       m_subject=0;
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
    delete m_subject;m_subject=0;

    QWARN("\n\t ---- Expected QWARN : Mulitple definitions of group 'DUI' ----");
    QVERIFY((m_subject=new DcpAppletMetadata(desktopBadTestFile)));
    QVERIFY(!m_subject->isValid());
}

void Ut_DcpAppletMetadata::testIsModified()
{
    if (QTest::currentTestFailed()) return;

    QVERIFY((m_subject=new DcpAppletMetadata(desktopTestFile)));

    QVERIFY(m_subject->isModified());
    QVERIFY(!m_subject->isModified());
}

void Ut_DcpAppletMetadata::testName()
{
    if (QTest::currentTestFailed()) return;

    QVERIFY(m_subject->name()=="Browser");
}
void Ut_DcpAppletMetadata::testFileName()
{
    if (QTest::currentTestFailed()) return;

    QCOMPARE(m_subject->fileName(),desktopTestFile);
}

void Ut_DcpAppletMetadata::testCategory()
{
    if (QTest::currentTestFailed()) return;

    QCOMPARE(m_subject->category(),QString("Application"));
}

void Ut_DcpAppletMetadata::testGetSetBinaryDir()
{
    if (QTest::currentTestFailed()) return;

    m_subject->setBinaryDir(appletDir);

    QCOMPARE(m_subject->binaryDir(),appletDir);
}

void Ut_DcpAppletMetadata::testBinary()
{
    if (QTest::currentTestFailed()) return;

    QCOMPARE(m_subject->binary(),QString("testapplet.so"));
}

void Ut_DcpAppletMetadata::testFullBinary()
{
    if (QTest::currentTestFailed()) return;

    testGetSetBinaryDir();

    QCOMPARE(m_subject->fullBinary(),appletDir+appletSo);
}

void Ut_DcpAppletMetadata::testWidgetTypeID()
{
    if (QTest::currentTestFailed()) return;

    QCOMPARE(m_subject->widgetTypeID(),static_cast<int>(DCPLABEL2));
}

void Ut_DcpAppletMetadata::testAlign()
{
    if (QTest::currentTestFailed()) return;

    QCOMPARE(m_subject->align(),Qt::AlignRight);

}

void Ut_DcpAppletMetadata::testToggle()
{
    QSKIP("!!!! UnableToLoadAnyApplet bug under fixxing by Lgal !!!!",SkipSingle);

    if (QTest::currentTestFailed()) return;
}

void Ut_DcpAppletMetadata::testText2()
{
    QSKIP("!!!! UnableToLoadAnyApplet bug under fixxing by Lgal !!!!",SkipSingle);

    if (QTest::currentTestFailed()) return;
}

void Ut_DcpAppletMetadata::testImage()
{
    if (QTest::currentTestFailed()) return;

    QCOMPARE(m_subject->image(),QString("test.png"));
}

void Ut_DcpAppletMetadata::testOrder()
{
    if (QTest::currentTestFailed()) return;

    QCOMPARE(m_subject->order(),1);
}

void Ut_DcpAppletMetadata::testUsage()
{
    QSKIP("!!!! RelativePath bug under fixxing by Retsoft !!!!",SkipSingle);

    if (QTest::currentTestFailed()) return;

    qWarning() <<"\n@@" <<m_subject->usage() <<"@@\n";
}

void Ut_DcpAppletMetadata::testPart()
{
    if (QTest::currentTestFailed()) return;

    QCOMPARE(m_subject->part(),QString("RobiJonMegKutyaraDer"));
}

void Ut_DcpAppletMetadata::testApplet()
{
    QSKIP("!!!! UnableToLoadAnyApplet bug under fixxing by Lgal !!!!",SkipSingle);

    if (QTest::currentTestFailed()) return;

    testGetSetBinaryDir();

    QVERIFY(m_subject->applet());
}

void Ut_DcpAppletMetadata::testSetGetParent()
{
    if (QTest::currentTestFailed()) return;

    m_subject->setParent(m_subject);

    QCOMPARE(m_subject,m_subject->parent());

    m_subject->setParent(0);
}

void Ut_DcpAppletMetadata::testParentName()
{
    if (QTest::currentTestFailed()) return;

    QCOMPARE(m_subject->parentName(),QString("RobiJonMegKutyaraDer_II"));
}

void Ut_DcpAppletMetadata::testCleanup()
{
    if (QTest::currentTestFailed()) return;

    m_subject->cleanup(); //We're happy if there is no SegFault
}

void Ut_DcpAppletMetadata::testBriefChanged()
{
    QSKIP("!!!! UnableToLoadAnyApplet bug under fixxing by Lgal !!!!",SkipSingle);

    if (QTest::currentTestFailed()) return;
}

QTEST_APPLESS_MAIN(Ut_DcpAppletMetadata)
