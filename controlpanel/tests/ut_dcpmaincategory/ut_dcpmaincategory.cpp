#include <QObject>
#include <QGraphicsSceneMouseEvent>

#include <dcpmaincategory.h>


#include "ut_dcpmaincategory.h"

void Ut_DcpMainCategory::init()
{
    m_subject = new DcpMainCategory("Main");
}

void Ut_DcpMainCategory::cleanup()
{
    delete m_subject;
    m_subject = 0;
}

void Ut_DcpMainCategory::initTestCase()
{
    QSKIP("incomplete", SkipSingle);   // remove this when you've finished
}

void Ut_DcpMainCategory::cleanupTestCase()
{
}
void Ut_DcpMainCategory::testCreation()
{
    QSKIP("incomplete", SkipSingle);   // remove this when you've finished
}

void Ut_DcpMainCategory::testAppendWidget() 
{
    QSKIP("incomplete", SkipSingle);   // remove this when you've finished
}

void Ut_DcpMainCategory::testMaxColums() 
{
    QSKIP("incomplete", SkipSingle);   // remove this when you've finished
}

void Ut_DcpMainCategory::testGetItemCount() 
{
    QSKIP("incomplete", SkipSingle);   // remove this when you've finished
}

void Ut_DcpMainCategory::testDuiLayout() 
{
    QSKIP("incomplete", SkipSingle);   // remove this when you've finished
}

void Ut_DcpMainCategory::testHorizontalSpacing() 
{
    QSKIP("incomplete", SkipSingle);   // remove this when you've finished
}

void Ut_DcpMainCategory::testVerticalSpacing() 
{
    QSKIP("incomplete", SkipSingle);   // remove this when you've finished
}

void Ut_DcpMainCategory::testCreateSeparators() 
{
    QSKIP("incomplete", SkipSingle);   // remove this when you've finished
}

void Ut_DcpMainCategory::testDeleteItems() 
{
    QSKIP("incomplete", SkipSingle);   // remove this when you've finished
}

void Ut_DcpMainCategory::testCreateContents() 
{
    QSKIP("incomplete", SkipSingle);   // remove this when you've finished
}

void Ut_DcpMainCategory::testAppendSeparatorsIfNeeded() 
{
    QSKIP("incomplete", SkipSingle);   // remove this when you've finished
}

void Ut_DcpMainCategory::testIncrementRowAndCol() 
{
    QSKIP("incomplete", SkipSingle);   // remove this when you've finished
}

QTEST_APPLESS_MAIN(Ut_DcpMainCategory)
