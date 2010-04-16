#include <QObject>
#include <QGraphicsSceneMouseEvent>

#include <dcpmaincategory.h>


#include "ut_dcpmaincategory.h"
#include <DuiLayout>
#include <DuiAbstractLayoutPolicy>
#include <DuiLinearLayoutPolicy>
#include <DuiGridLayoutPolicy>
#include <DcpComponent>
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
    QVERIFY(m_subject->m_Layout != 0);
    QVERIFY(m_subject->m_Layout->animation() == 0);
    QVERIFY(m_subject->m_LandscapeLayout != 0);
    QVERIFY(m_subject->m_PortraitLayout != 0);
    QCOMPARE((void*)(m_subject->m_Layout->landscapePolicy()),
          (void*)(m_subject->m_LandscapeLayout));
    QCOMPARE((void*)(m_subject->m_Layout->portraitPolicy()),
          (void*)(m_subject->m_PortraitLayout));

}

void Ut_DcpMainCategory::testAppendWidget() 
{
    DcpComponent *component1 = new DcpComponent(0, "test");
    QGraphicsLayoutItem *item1 = 0;
    QGraphicsLayoutItem *item2 = 0;
    int row = m_subject->m_RowCount;
    int col = m_subject->m_ColCount;
    int count = m_subject->m_ItemCount;
    m_subject->appendWidget(component1);
    item1 = m_subject->m_Layout->portraitPolicy()->itemAt(0);
    QCOMPARE((void*)component1, (void*)(QGraphicsWidget*)item1);
    item2 = m_subject->m_LandscapeLayout->itemAt(row, col);
    QCOMPARE((void*)component1, (void*)(QGraphicsWidget*)item2);
    QVERIFY(m_subject->m_ItemCount == count + 1);
    delete component1;
}

void Ut_DcpMainCategory::testMaxColums() 
{
    m_subject->setMaxColumns(2);
    QVERIFY(m_subject->m_MaxColumns == 2);
    QVERIFY(m_subject->maxColumns() == 2);
    for (int col = 0; col < m_subject->m_MaxColumns; col++) 
        QCOMPARE(m_subject->m_LandscapeLayout->columnStretchFactor(col), 1);
}

void Ut_DcpMainCategory::testGetItemCount() 
{
    DcpComponent *component1 = new DcpComponent(0, "test");
    m_subject->appendWidget(component1);
    QVERIFY(m_subject->getItemCount() == 1);
    
    m_subject->appendWidget(component1);
    QVERIFY(m_subject->getItemCount() == 2);

    m_subject->appendWidget(component1);
    QVERIFY(m_subject->getItemCount() == 3);
    delete component1;
}

void Ut_DcpMainCategory::testDuiLayout() 
{
    QVERIFY(m_subject->duiLayout());
    QCOMPARE((void*)m_subject->duiLayout(), (void*)m_subject->m_Layout);
}

void Ut_DcpMainCategory::testHorizontalSpacing() 
{
    m_subject->setHorizontalSpacing(10);
    QVERIFY(m_subject->m_LandscapeLayout->horizontalSpacing() == 10);
}

void Ut_DcpMainCategory::testVerticalSpacing() 
{
    m_subject->setVerticalSpacing(10);
    QVERIFY(m_subject->m_LandscapeLayout->verticalSpacing() == 10);
}

void Ut_DcpMainCategory::testCreateSeparators() 
{
    m_subject->setCreateSeparators(true);
    QVERIFY(m_subject->m_CreateSeparators == true);
    m_subject->setCreateSeparators(false);
    QVERIFY(m_subject->m_CreateSeparators == false);
}

void Ut_DcpMainCategory::testDeleteItems() 
{
    DcpComponent *component1 = new DcpComponent(0, "test1");
    m_subject->appendWidget(component1);
    DcpComponent *component2 = new DcpComponent(0, "test2");
    m_subject->appendWidget(component2);
    QVERIFY(m_subject->m_PortraitLayout->count() != 0); 
    m_subject->deleteItems();
    QSKIP("incomplete", SkipSingle);   // remove this when you've finished
    //QCOMPARE(m_subject->m_PortraitLayout->count(), 0); 
}

void Ut_DcpMainCategory::testCreateContents() 
{
    //empty function
}

void Ut_DcpMainCategory::testAppendSeparatorsIfNeeded() 
{
    QSKIP("incomplete", SkipSingle);   // remove this when you've finished
}

void Ut_DcpMainCategory::testIncrementRowAndCol() 
{
    m_subject->setMaxColumns(2);
    QVERIFY(m_subject->m_ColCount == 0 && m_subject->m_RowCount == 0);
    m_subject->incrementRowAndCol();
    QVERIFY(m_subject->m_ColCount == 1 && m_subject->m_RowCount == 0);
    m_subject->incrementRowAndCol();
    QVERIFY(m_subject->m_ColCount == 0 && m_subject->m_RowCount == 1);
    m_subject->incrementRowAndCol();
    QVERIFY(m_subject->m_ColCount == 1 && m_subject->m_RowCount == 1);
    m_subject->incrementRowAndCol();
    QVERIFY(m_subject->m_ColCount == 0 && m_subject->m_RowCount == 2);
    m_subject->incrementRowAndCol();
    QVERIFY(m_subject->m_ColCount == 1 && m_subject->m_RowCount == 2);
    m_subject->incrementRowAndCol();
}

QTEST_APPLESS_MAIN(Ut_DcpMainCategory)
