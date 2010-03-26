#include <QObject>
#include <QGraphicsSceneMouseEvent>

#include <dcpappletbuttons.h>
#include "duiapplication_stub.h"
#include "duitheme_stub.h"


#include "ut_dcpappletbuttons.h"
#include "maintranslations-fake.h"

// stubs
#include "dcpbriefcomponent-fake.h"
#include "dcpsinglecomponent-fake.h"

void Ut_DcpAppletButtons::init()
{
    m_subject = new DcpAppletButtons(&fakeInfo, "fake category");
}

void Ut_DcpAppletButtons::cleanup()
{
    delete m_subject;
    m_subject = 0;
}

void Ut_DcpAppletButtons::initTestCase()
{
}

void Ut_DcpAppletButtons::cleanupTestCase()
{
}

void Ut_DcpAppletButtons::testCreation()
{
    QSKIP("incomplete", SkipSingle);   // remove this when you've finished
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

int main (int argc, char** argv) {
    DuiApplication* app = new DuiApplication (argc, argv);
    Ut_DcpAppletButtons test;
    QTest::qExec(&test, argc, argv);
    delete app;
}

