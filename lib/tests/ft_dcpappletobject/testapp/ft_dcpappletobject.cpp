#include <QObject>
#include <QGraphicsSceneMouseEvent>

#include "dcpappletobject.h"
#include "dcpappletmetadata.h"
#include "dcpappletif.h"


#include "ft_dcpappletobject.h"

#define DESKTOPFILE DATADIR "/testapplet.desktop"
#define DESKTOPFILE2 DATADIR "/testapplet2.desktop"

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
    m_app = new DuiApplication(argc, &appname);
}

void Ft_DcpAppletObject::cleanupTestCase()
{
    delete m_app;
}

void Ft_DcpAppletObject::testLoad()
{
//    testApplet(DESKTOPFILE);
}

void Ft_DcpAppletObject::testLoadManyTimes()
{    
    for (int i = 0; i < 1; ++i) {
        qDebug() << "round " << i;
        testApplet(DESKTOPFILE);
        testApplet(DESKTOPFILE2);
    }
}

void Ft_DcpAppletObject::testApplet(const char *desktopfile)
{
    DcpAppletMetadata *metadata = new DcpAppletMetadata(desktopfile);
    DcpAppletObject *appletObj = new DcpAppletObject(metadata);
    delete metadata;
    QVERIFY2(appletObj->isAppletLoaded(), "applet not loaded");

    DcpAppletIf *applet = appletObj->applet();
    QVERIFY2(applet, "DcpAppletObject::applet() gave NULL");

    applet->constructBrief();
    applet->constructWidget(0);

    delete appletObj;
}




QTEST_APPLESS_MAIN(Ft_DcpAppletObject)
