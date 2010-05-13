/***************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Karoliina T. Salminen <karoliina.t.salminen@nokia.com>
**
** This file is part of duicontrolpanel.
**
**
** This program is free software; you can redistribute it and/or
** modify it under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation
** and appearing in the file LICENSE.LGPL included in the packaging
** of this file.
**
****************************************************************************/

#include <QObject>
#include <QGraphicsSceneMouseEvent>

#include <dcpmaincategory.h>


#include "ut_dcpmaincategory.h"
#include <MLayout>
#include <MSeparator>
#include <MAbstractLayoutPolicy>
#include <MLinearLayoutPolicy>
#include <MGridLayoutPolicy>
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

void Ut_DcpMainCategory::testMLayout() 
{
    QVERIFY(m_subject->mLayout());
    QCOMPARE((void*)m_subject->mLayout(), (void*)m_subject->m_Layout);
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
//    QSKIP("incomplete", SkipSingle);   // remove this when you've finished
    //QCOMPARE(m_subject->m_PortraitLayout->count(), 0); 
}

void Ut_DcpMainCategory::testCreateContents() 
{
    //empty function
}

void Ut_DcpMainCategory::testAppendSeparatorsIfNeeded() 
{
    m_subject->setMaxColumns(2);
    int col = m_subject->m_ColCount;
    int row = m_subject->m_RowCount;
    int itemCount = m_subject->m_ItemCount;
    // case 1: no elements so no changes are expected
    m_subject->setCreateSeparators(true);
    m_subject->appendSeparatorsIfNeeded();
    QCOMPARE(col, m_subject->m_ColCount);
    QCOMPARE(row, m_subject->m_RowCount);
    QCOMPARE(itemCount, m_subject->m_ItemCount);
    // case 2: there are elements and we want separators
    DcpComponent *component1 = new DcpComponent(0, "test1");
    DcpComponent *component2 = new DcpComponent(0, "test2");
    m_subject->appendWidget(component1);
    m_subject->appendWidget(component2);
    col = m_subject->m_ColCount;
    row = m_subject->m_RowCount;
    m_subject->appendSeparatorsIfNeeded();
    QCOMPARE(m_subject->m_ColCount, 0);
    QCOMPARE(m_subject->m_RowCount, row + 1);
    MSeparator *separator1 = 0;
    MSeparator *separator2 = 0;
    separator1 = (MSeparator*)(m_subject->m_LandscapeLayout->itemAt(row, col));
    separator2 = (MSeparator*)(m_subject->m_LandscapeLayout->itemAt(row, col + 1));
    QVERIFY(separator1);
    QVERIFY(separator2);
    QCOMPARE(separator1->objectName(), m_subject->sm_SeparatorObjectName);
    QCOMPARE(separator2->objectName(), m_subject->sm_SeparatorObjectName);
    // case 3: there are elements, but we do not want separators
    m_subject->setCreateSeparators(false);
    col = m_subject->m_ColCount;
    row = m_subject->m_RowCount;
    itemCount = m_subject->m_ItemCount;
    m_subject->appendSeparatorsIfNeeded();
    QCOMPARE(col, m_subject->m_ColCount);
    QCOMPARE(row, m_subject->m_RowCount);
    QCOMPARE(itemCount, m_subject->m_ItemCount);
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
}

QTEST_APPLESS_MAIN(Ut_DcpMainCategory)
