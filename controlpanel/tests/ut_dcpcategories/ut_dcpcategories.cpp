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

#include <dcpcategories.h>


#include "ut_dcpcategories.h"

void Ut_DcpCategories::init()
{
}

void Ut_DcpCategories::cleanup()
{
}

void Ut_DcpCategories::initTestCase()
{
    qWarning ("XXX");
    m_subject = new DcpCategories();
    // in C1:
    m_c11 = new MemoryCategory ("C11","id11", "C1");
    m_c12 = new MemoryCategory ("C12","id12", "C1");
    m_c13 = new MemoryCategory ("C13","id13", "C1");

    // in MainPage:
    m_c1 = new MemoryCategory ("C1","id1", "MainPage");
    m_c2 = new MemoryCategory ("C2","id2", "MainPage");
    m_c3 = new MemoryCategory ("C3","id3", "MainPage");

    // in C3:
    m_c31 = new MemoryCategory ("C31","id31", "C3");

    // add them in "random" order:
    m_subject->add (m_c12);
    m_subject->add (m_c1);
    m_subject->add (m_c11);
    m_subject->add (m_c31);
    m_subject->add (m_c2);
    m_subject->add (m_c3);
    m_subject->add (m_c13);

    m_subject->buildParentChildRelations ();
}

void Ut_DcpCategories::cleanupTestCase()
{
    delete m_subject;
    m_subject = 0;
}

void Ut_DcpCategories::testInstance()
{
    // check singleton
    DcpCategories* previous = DcpCategories::instance();
    QCOMPARE (DcpCategories::instance(), previous);

    // destroyal:
    delete previous;
    QCOMPARE (DcpCategories::sm_Instance, (DcpCategories*)0);

    // check creating another instance:
    QVERIFY (DcpCategories::instance());

    // check destroy
    DcpCategories::destroy();
    QCOMPARE (DcpCategories::sm_Instance, (DcpCategories*)0);
    DcpCategories::destroy();
}

void Ut_DcpCategories::testCategoryById()
{
    QVERIFY (m_c1);
    QCOMPARE (m_subject->categoryById ("C1"), m_c1);
    QCOMPARE (m_subject->categoryById ("C13"), m_c13);
    QCOMPARE (m_subject->categoryById ("C21"), (Category*)0);
}

void Ut_DcpCategories::testCategoryChildren()
{
    QList<const Category*> cats;

    // MainPage:
    cats = m_subject->categoryChildren ("MainPage");
    QCOMPARE (cats.count(), 3);
    QVERIFY (cats.contains (m_c1));
    QVERIFY (cats.contains (m_c2));
    QVERIFY (cats.contains (m_c3));

    // C3
    cats = m_subject->categoryChildren ("C3");
    QCOMPARE (cats.count(), 1);
    QCOMPARE (cats.at(0),m_c31);

    // empty:
    QVERIFY (m_subject->categoryChildren ("C2").isEmpty());

    // non existing:
    QVERIFY (m_subject->categoryChildren ("X").isEmpty());
}

void Ut_DcpCategories::testHasCategory()
{
    QVERIFY (DcpCategories::hasCategory ("MainPage"));
    QVERIFY (!DcpCategories::hasCategory ("X"));
}

void Ut_DcpCategories::testMainPageCategory()
{
    QCOMPARE (m_subject->mainPageCategory()->name(),
              DcpCategories::mainPageCategoryName());
}

QTEST_APPLESS_MAIN(Ut_DcpCategories)


