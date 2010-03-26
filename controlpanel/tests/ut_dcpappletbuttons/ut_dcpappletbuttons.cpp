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
    static int argc = 1;
    static char *app_name[1] = { (char *) "./ut_dcpappletbuttons" };
    app = new DuiApplication(argc, app_name);
}

void Ut_DcpAppletButtons::cleanupTestCase()
{
    delete app;
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
    

QTEST_APPLESS_MAIN(Ut_DcpAppletButtons)
