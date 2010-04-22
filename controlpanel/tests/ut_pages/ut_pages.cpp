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
    PageHandle h5(PageHandle::CATEGORY_PAGEID_START);
    QVERIFY(h5.getStringVariant() == "CATEGORY_PAGEID_START:///-1");
    PageHandle h6(PageHandle::LOOKANDFEEL);
    QVERIFY(h6.getStringVariant() == "LOOKANDFEEL:///-1");
    PageHandle h7(PageHandle::CONNECTIVITY);
    QVERIFY(h7.getStringVariant() == "CONNECTIVITY:///-1");
    PageHandle h8(PageHandle::REGIONALSETTING);
    QVERIFY(h8.getStringVariant() == "REGIONALSETTING:///-1");
    PageHandle h9(PageHandle::DEVICESYSTEM);
    QVERIFY(h9.getStringVariant() == "DEVICESYSTEM:///-1");
    PageHandle h10(PageHandle::ServiceAccounts);
    QVERIFY(h10.getStringVariant() == "ServiceAccounts:///-1");
    PageHandle h11(PageHandle::Applications);
    QVERIFY(h11.getStringVariant() == "Applications:///-1");
    PageHandle h12(PageHandle::CATEGORY_PAGEID_END);
    QVERIFY(h12.getStringVariant() == "CATEGORY_PAGEID_END:///-1");
    PageHandle h13(PageHandle::APPLET);
    QVERIFY(h13.getStringVariant() == "APPLET:///-1");
    PageHandle h14(PageHandle::PAGEID_COUNT);
    QVERIFY(h14.getStringVariant() == "PAGEID_COUNT:///-1");
};

void Ut_PageHandle::testEquality()
{
    PageHandle h1(PageHandle::MAIN, "param1", 1);
    PageHandle h2(PageHandle::NOPAGE, "param2", 2);
    QVERIFY(!(h1 == h2));
    h2.id = PageHandle::MAIN;
    h2.param = "param1";
    h2.widgetId = 1;
    QVERIFY(h1 == h2);

};

QTEST_APPLESS_MAIN(Ut_PageHandle)

