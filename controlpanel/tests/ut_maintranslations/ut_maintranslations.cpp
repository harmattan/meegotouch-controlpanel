#include <QObject>
#include <QGraphicsSceneMouseEvent>

#include <maintranslations.h>


#include "ut_maintranslations.h"

void Ut_maintranslations::init()
{
}

void Ut_maintranslations::cleanup()
{
}

void Ut_maintranslations::initTestCase()
{
}

void Ut_maintranslations::cleanupTestCase()
{
}

void Ut_maintranslations::testFindCategoyInfo()
{
    const DcpCategoryInfo otherInfos[] = {
    {                                                                           
        //% "Applications"                                                      
        QT_TRID_NOOP ("qtn_sett_main_applications"),                            
        "Applications",                                                         
        PageHandle::Applications,                                               
        NULL                                                                    
    },                                                                          
    {                                                                           
        // The last element must have the .titleId == 0                         
        0, 0, PageHandle::NOPAGE, NULL                                          
    }};
 
    QCOMPARE(DcpMain::findCategoryInfo(PageHandle::LOOKANDFEEL),
             &DcpMain::CategoryInfos[0]);
    
    QCOMPARE(DcpMain::findCategoryInfo(PageHandle::Applications, &otherInfos[0]),
             &otherInfos[0]);

    QVERIFY(!DcpMain::findCategoryInfo(PageHandle::LOOKANDFEEL, &otherInfos[0]));

    QCOMPARE(DcpMain::findCategoryInfo("qtn_sett_main_look"),
             &DcpMain::CategoryInfos[0]);
    QVERIFY(!DcpMain::findCategoryInfo("unknown"));
    
    QCOMPARE(DcpMain::findCategoryInfo("qtn_sett_main_applications", &otherInfos[0]),
             &otherInfos[0]);
    QVERIFY(!DcpMain::findCategoryInfo("unknown", &otherInfos[0]));
}

void Ut_maintranslations::testIsCategoryNameEnlisted()
{
    QVERIFY(DcpMain::isCategoryNameEnlisted("qtn_sett_main_look"));
    QVERIFY(!DcpMain::isCategoryNameEnlisted("qtn_sett_unknown"));
    
}

QTEST_APPLESS_MAIN(Ut_maintranslations)
