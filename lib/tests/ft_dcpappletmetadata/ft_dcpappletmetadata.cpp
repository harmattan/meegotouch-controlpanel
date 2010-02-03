#include <QObject>
#include <QByteArray>

#include <DcpApplet>
#include <DcpWidgetTypes>

#include <DcpAppletMetadata>

#include "ft_dcpappletmetadata.h"
#include <DuiGConfItem>

void Ft_DcpAppletMetadata::initTestCase()
{
    static int c = 0;
    static QByteArray arg("dummyarg");
    char *argp = arg.data();
    qap = new QCoreApplication(c, &argp);
    QString desktopDir(qApp->applicationDirPath() + 
                       "/ft_dcpappletmetadata-data/desktops/");
    desktopTestFile =  desktopDir + "test.desktop";
    desktopBadTestFile = desktopDir + "testBad.desktop";

    appletDir = "so.applet/";
    appletSo = "testapplet.so";
}

void Ft_DcpAppletMetadata::cleanupTestCase()
{
    delete qap;
}

void Ft_DcpAppletMetadata::init()
{
    QVERIFY(m_subject = new DcpAppletMetadata(desktopTestFile));
}

void Ft_DcpAppletMetadata::cleanup()
{
    if (m_subject) {
       delete m_subject;
       m_subject = 0;
    }
}

void Ft_DcpAppletMetadata::testCreateAndDestroy()
{
    if (QTest::currentTestFailed()) return;
}

void Ft_DcpAppletMetadata::testIsValid()
{
    if (QTest::currentTestFailed()) return;

    QVERIFY(m_subject->isValid());
    delete m_subject;
    m_subject = 0;

    QWARN("\n\t----Expected QWARN: Multiple definitions of group 'DUI'----");
    QVERIFY((m_subject = new DcpAppletMetadata(desktopBadTestFile)));
    QVERIFY(!m_subject->isValid());
}

void Ft_DcpAppletMetadata::testIsModified()
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

void Ft_DcpAppletMetadata::testName()
{
    if (QTest::currentTestFailed()) return;

    QCOMPARE(m_subject->name(), QString("Browser"));
}
void Ft_DcpAppletMetadata::testFileName()
{
    if (QTest::currentTestFailed()) return;

    QCOMPARE(m_subject->fileName(), desktopTestFile);
}

void Ft_DcpAppletMetadata::testCategory()
{
    if (QTest::currentTestFailed()) return;

    QCOMPARE(m_subject->category(), QString("Application"));
}

void Ft_DcpAppletMetadata::testBinary()
{
    if (QTest::currentTestFailed()) return;

    QCOMPARE(m_subject->binary(), QString("testapplet.so"));
}

void Ft_DcpAppletMetadata::testFullBinary()
{
    if (QTest::currentTestFailed()) return;

    QCOMPARE(m_subject->fullBinary(), appletDir + appletSo);
}

void Ft_DcpAppletMetadata::testWidgetTypeID()
{
    if (QTest::currentTestFailed()) return;

    QCOMPARE(m_subject->widgetTypeID(), static_cast<int>(DcpWidgetType::Label));
}  

void Ft_DcpAppletMetadata::testAlign()
{
    if (QTest::currentTestFailed()) return;

    QCOMPARE(m_subject->align(), Qt::AlignRight);

}

void Ft_DcpAppletMetadata::testToggle()
{
    QSKIP("!!!! UnableToLoadAnyApplet bug under fixxing by Lgal !!!!",
            SkipSingle);

    if (QTest::currentTestFailed()) return;
}

void Ft_DcpAppletMetadata::testText2()
{
    QSKIP("!!!! UnableToLoadAnyApplet bug under fixxing by Lgal !!!!",
            SkipSingle);

    if (QTest::currentTestFailed()) return;
}

void Ft_DcpAppletMetadata::testImage()
{
    if (QTest::currentTestFailed()) return;

    QCOMPARE(m_subject->image(), QString("test.png"));
}

void Ft_DcpAppletMetadata::testOrder()
{
    if (QTest::currentTestFailed()) return;

    QCOMPARE(m_subject->order(), 1);
}

void Ft_DcpAppletMetadata::testUsage()
{
    QSKIP("!!!! RelativePath bug under fixxing by Retsoft !!!!", SkipSingle);

    if (QTest::currentTestFailed()) return;

    qWarning() <<"\n@@" <<m_subject->usage() <<"@@\n";
}

void Ft_DcpAppletMetadata::testPart()
{
    if (QTest::currentTestFailed()) return;

    QCOMPARE(m_subject->part(), QString("RobiJonMegKutyaraDer"));
}

void Ft_DcpAppletMetadata::testApplet()
{
    QSKIP("!!!! UnableToLoadAnyApplet bug under fixxing by Lgal !!!!",
            SkipSingle);

    if (QTest::currentTestFailed()) return;

    QVERIFY(m_subject->applet());
}

void Ft_DcpAppletMetadata::testSetGetParent()
{
    if (QTest::currentTestFailed()) return;

    m_subject->setParent(m_subject);

    QCOMPARE(m_subject, m_subject->parent());

    m_subject->setParent(0);
}

void Ft_DcpAppletMetadata::testParentName()
{
    if (QTest::currentTestFailed()) return;

    QCOMPARE(m_subject->parentName(), QString("RobiJonMegKutyaraDer_II"));
}

void Ft_DcpAppletMetadata::testCleanup()
{
    if (QTest::currentTestFailed()) return;

    m_subject->cleanup(); //We're happy if there is no SegFault
}

void Ft_DcpAppletMetadata::testBriefChanged()
{
    QSKIP("!!!! UnableToLoadAnyApplet bug under fixxing by Lgal !!!!",
          SkipSingle);

    if (QTest::currentTestFailed()) return;
}

QTEST_APPLESS_MAIN(Ft_DcpAppletMetadata)
