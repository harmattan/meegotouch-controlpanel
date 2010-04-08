#include <QObject>
#include <QGraphicsSceneMouseEvent>

#include <dcpappletbuttons.h>

#include "ut_dcpappletbuttons.h"
#include "maintranslations-fake.h"


void Ut_DcpAppletButtons::init()
{
}

void Ut_DcpAppletButtons::cleanup()
{
}

void Ut_DcpAppletButtons::initTestCase()
{
}

void Ut_DcpAppletButtons::cleanupTestCase()
{
}

void Ut_DcpAppletButtons::testCreation()
{
    DcpAppletButtons buttons1(&fakeInfo, "fake category");
    QCOMPARE (&fakeInfo, buttons1.m_CategoryInfo);

    // ...
}

void Ut_DcpAppletButtons::testAddComponent()
{
    QSKIP("incomplete", SkipSingle);   // remove this when you've finished
}

void Ut_DcpAppletButtons::testReload()
{
    QSKIP("incomplete", SkipSingle);   // remove this when you've finished
}

void Ut_DcpAppletButtons::testCreateContents()
{
    QSKIP("incomplete", SkipSingle);   // remove this when you've finished
}

QTEST_APPLESS_MAIN(Ut_DcpAppletButtons)

