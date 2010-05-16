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

#include <dcpappletcategorypage.h>
#include <dcpmaincategory.h>
#include <maintranslations.h>

#include "ut_dcpappletcategorypage.h"

void Ut_DcpAppletCategoryPage::init()
{
    m_subject = new DcpAppletCategoryPage(&DcpMain::CategoryInfos[0]);

}

void Ut_DcpAppletCategoryPage::cleanup()
{
    delete m_subject;
    m_subject = 0;
}

void Ut_DcpAppletCategoryPage::initTestCase()
{
    QSKIP("incomplete", SkipSingle);   // remove this when you've finished
}

void Ut_DcpAppletCategoryPage::cleanupTestCase()
{
}

void Ut_DcpAppletCategoryPage::testCreation()
{
    QVERIFY(m_subject);
    QCOMPARE((void*)m_subject->m_CategoryInfo, 
        (void*)(&DcpMain::CategoryInfos[0]));
//    QCOMPARE(m_subject->m_Category->maxColumns(), 2);
}

void Ut_DcpAppletCategoryPage::testCreateContent()
{
    m_subject->createContent();
}

void Ut_DcpAppletCategoryPage::testAppletCategory()
{
    QCOMPARE(m_subject->appletCategory(), QString("fake-category"));
    m_subject->setCategoryInfo(&DcpMain::CategoryInfos[1]);
    QCOMPARE(m_subject->appletCategory(), QString("fake-category-2"));
}

void Ut_DcpAppletCategoryPage::testCategoryInfo()
{
    m_subject->setCategoryInfo(&DcpMain::CategoryInfos[1]);
    QCOMPARE((void*)m_subject->m_CategoryInfo, 
        (void*)(&DcpMain::CategoryInfos[1]));
  
}

void Ut_DcpAppletCategoryPage::testReload()
{
    m_subject->createContent();
    m_subject->reload();
}

void Ut_DcpAppletCategoryPage::testCleanup()
{
    QSKIP("incomplete", SkipSingle);   // remove this when you've finished
}

void Ut_DcpAppletCategoryPage::testSetTitleId()
{
    m_subject->setTitleId("abcd");
    QCOMPARE(m_subject->m_TitleId, "abcd");
}

void Ut_DcpAppletCategoryPage::testBack()
{
    m_subject->back();
}

void Ut_DcpAppletCategoryPage::testRetranslateUi()
{
    m_subject->m_TitleId = "abcd";
    m_subject->retranslateUi();
    QCOMPARE(m_subject->title(), QString("abcd"));
}

void Ut_DcpAppletCategoryPage::testAddComponent()
{
    QSKIP("incomplete", SkipSingle);   // remove this when you've finished
}

QTEST_APPLESS_MAIN(Ut_DcpAppletCategoryPage)
