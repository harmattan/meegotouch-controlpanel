#include <QObject>
#include <QGraphicsSceneMouseEvent>

#include <pages.h>


#include "ut_pages.h"

void Ut_PageHandle::init()
{
}

void Ut_PageHandle::cleanup()
{
}

void Ut_PageHandle::initTestCase()
{
}

void Ut_PageHandle::cleanupTestCase()
{
}

void Ut_PageHandle::testCreation()
{
    PageHandle h1(PageHandle::MAIN);
    QVERIFY(h1.id == PageHandle::MAIN);
    QVERIFY(h1.param == "");
    QVERIFY(h1.widgetId == -1);
    QVERIFY(!h1.isStandalone);
    
    PageHandle h2(PageHandle::MAIN, "param");
    QVERIFY(h2.id == PageHandle::MAIN);
    QVERIFY(h2.param == "param");
    QVERIFY(h2.widgetId == -1);
    QVERIFY(!h2.isStandalone);
    
    PageHandle h3(PageHandle::MAIN, "param", 1);
    QVERIFY(h3.id == PageHandle::MAIN);
    QVERIFY(h3.param == "param");
    QVERIFY(h3.widgetId == 1);
    QVERIFY(!h3.isStandalone);

    PageHandle h4(PageHandle::MAIN, "param", 1, true);
    QVERIFY(h4.id == PageHandle::MAIN);
    QVERIFY(h4.param == "param");
    QVERIFY(h4.widgetId == 1);
    QVERIFY(h4.isStandalone);
}
void Ut_PageHandle::testGetStringVariant()
{
    PageHandle h1(PageHandle::MAIN);
    QVERIFY(h1.getStringVariant() == "MAIN:///-1");
    PageHandle h3(PageHandle::APPLET, "datetime", 1);
    QVERIFY(h3.getStringVariant() == "APPLET://datetime/1");
    PageHandle h4(PageHandle::NOPAGE);
    QVERIFY(h4.getStringVariant() == "NOPAGE:///-1");
}

QTEST_APPLESS_MAIN(Ut_PageHandle)

