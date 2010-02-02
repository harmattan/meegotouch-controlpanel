#include <QObject>
#include <QGraphicsSceneMouseEvent>

#include <dcpcategory.h>


#include "ut_dcpcategory.h"

void Ut_DcpCategory::init()
{
    m_subject = new DcpCategory();
}

void Ut_DcpCategory::cleanup()
{
    delete m_subject;
    m_subject = 0;
}

void Ut_DcpCategory::initTestCase()
{
    QSKIP("incomplete", SkipSingle);   // remove this when you've finished
}

void Ut_DcpCategory::cleanupTestCase()
{
}

void Ut_DcpCategory::testCreateAndDestroy(){}
void Ut_DcpCategory::testAdd(){}
void Ut_DcpCategory::testRemove(){}
void Ut_DcpCategory::testChildCount(){}  
void Ut_DcpCategory::testChild(){}  
void Ut_DcpCategory::testCategory(){}  
QTEST_MAIN(Ut_DcpCategory)
