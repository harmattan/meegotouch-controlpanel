#include <QObject>
#include <QGraphicsSceneMouseEvent>

#include "dcpappletobject.h"
#include "dcpappletmetadata.h"
#include "dcpappletif.h"
#include "dcpwidgettypes.h"

#include "ft_dcpappletobject.h"

#define DESKTOPFILE DATADIR "/testapplet.desktop"
#define DESKTOPFILE2 DATADIR "/testapplet2.desktop"

/**
 * TODO
 * test meaningful data from brief/metadata in getters
 * test signals and slots
 */

void Ft_DcpAppletObject::init()
{
}

void Ft_DcpAppletObject::cleanup()
{
}

void Ft_DcpAppletObject::initTestCase()
{
    int argc = 1;
    char *appname = (char*) "./ft_dcpappletobject";
    m_app = new MApplication(argc, &appname);
}

void Ft_DcpAppletObject::cleanupTestCase()
{
    delete m_app;
}

void Ft_DcpAppletObject::testLoad()
{
    testApplet(DESKTOPFILE);
}

void Ft_DcpAppletObject::testLoadManyTimes()
{    
    for (int i = 0; i < 4; ++i) {
        qDebug() << "round " << i;
        testApplet(DESKTOPFILE);
        testApplet(DESKTOPFILE2);
    }
}

void Ft_DcpAppletObject::testApplet(const char *desktopfile)
{
    DcpAppletMetadata *metadata = new DcpAppletMetadata(desktopfile);
    DcpAppletObject *appletObj = new DcpAppletObject(metadata);
    QVERIFY2(appletObj->isAppletLoaded(), "applet not loaded");

    DcpAppletIf *applet = appletObj->applet();
    QVERIFY2(applet, "DcpAppletObject::applet() gave NULL");

    DcpBrief *brief = applet->constructBrief();
    DcpWidget *widget = applet->constructWidget(0);

    // FIXME deleting the widget causes crash in loadCSS!
    // delete widget;

    delete metadata;
    delete appletObj;

    // FIXME: test if the applet's destructor has been called
}


void Ft_DcpAppletObject::testGetters()
{
    DcpAppletMetadata *metadata = new DcpAppletMetadata(DESKTOPFILE);
    DcpAppletObject *appletObj = new DcpAppletObject(metadata);
    QCOMPARE(appletObj->widgetTypeID(), static_cast<int>(DcpWidgetType::Label));
    // string coming from testplugin/testapplet.cpp
    QCOMPARE(appletObj->text1(), QString("Test title 1"));


    // FIXME test these values too
    QCOMPARE(appletObj->text2(), QString("")); 
    QCOMPARE(appletObj->align(), Qt::AlignLeft);
    QCOMPARE(appletObj->toggle(), false);
    QCOMPARE(appletObj->imageName(), QString());
    QCOMPARE(appletObj->toggleIconId(), QString());


    delete metadata;
    delete appletObj;
}



QTEST_APPLESS_MAIN(Ft_DcpAppletObject)
