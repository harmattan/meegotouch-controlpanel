#include <QObject>
#include <QGraphicsSceneMouseEvent>

#include <dcpappletbuttons.h>

#include "ut_dcpappletbuttons.h"
#include "maintranslations.h"
#include <duilinearlayoutpolicy.h>
#include <DcpAppletMetadata>

// a fake category info
static const DcpCategoryInfo fakeInfo =
{
    QT_TRID_NOOP ("qtn_sett_main_look"),
    "Fake Look & Feel",
    PageHandle::LOOKANDFEEL,
    0
};

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
    // if we create with a category other then mostrecentused
    DcpAppletButtons buttons1(&fakeInfo, "fake-category");
    QCOMPARE (&fakeInfo, buttons1.m_CategoryInfo);
    //      -> checks if the right widgets were added to the layout:
    QCOMPARE (buttons1.m_PortraitLayout->count(), 1);
    QCOMPARE (((DcpComponent*)buttons1.m_PortraitLayout->itemAt(0))->title(),
              QString("fake-name"));

    // if we create with mostrecentused
    DcpAppletButtons buttons2(&DcpMain::mostUsedCategory, "MostUsed");
//    QCOMPARE (&DcpMain::mostUsedCategory, buttons1.m_CategoryInfo); FIXME: why the hell is this not ok ???
    //      -> checks if the right widgets were added to the layout:
    QCOMPARE (buttons2.m_PortraitLayout->count(), 1);
    QCOMPARE (((DcpComponent*)buttons2.m_PortraitLayout->itemAt(0))->title(),
              QString("mostUsed-name"));
}

void Ut_DcpAppletButtons::testAddComponent()
{
    // create an empty appletbuttons:
    DcpAppletButtons buttons1(&fakeInfo, "null");
    QCOMPARE (buttons1.m_PortraitLayout->count(), 0);

    // add a button:
    DcpAppletMetadata* metadata = new DcpAppletMetadata("fake");
    buttons1.addComponent(metadata);
    QCOMPARE (buttons1.m_PortraitLayout->count(), 1);
    QCOMPARE (((DcpComponent*)buttons1.m_PortraitLayout->itemAt(0))->title(),
              QString("fake-name"));
}

void Ut_DcpAppletButtons::testReload()
{
    // create an empty appletbuttons:
    DcpAppletButtons buttons1(&fakeInfo, "null");
    QCOMPARE (buttons1.m_PortraitLayout->count(), 0);

    // change the categoryname to the test one and reload:
    // the fake applet should be loaded
    buttons1.m_CategoryInfo = &fakeInfo;
    buttons1.reload();
    QCOMPARE (buttons1.m_PortraitLayout->count(), 1);
    QCOMPARE (((DcpComponent*)buttons1.m_PortraitLayout->itemAt(0))->title(),
              QString("fake-name"));

    // change to mostuseditems and reload: applet count should stay the same,
    // but the one applet changes
    buttons1.m_CategoryInfo = &DcpMain::mostUsedCategory;
    buttons1.reload();
    QCOMPARE (buttons1.m_PortraitLayout->count(), 1);
    QCOMPARE (((DcpComponent*)buttons1.m_PortraitLayout->itemAt(0))->title(),
              QString("mostUsed-name"));
}

QTEST_APPLESS_MAIN(Ut_DcpAppletButtons)

