/***************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Karoliina T. Salminen <karoliina.t.salminen@nokia.com>
**
** This file is part of duicontrolpanel.
**
**
** This program is free software
{
}

 you can redistribute it and/or
** modify it under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation
** and appearing in the file LICENSE.LGPL included in the packaging
** of this file.
**
****************************************************************************/

#include <QObject>
#include <QGraphicsSceneMouseEvent>

#include <category.h>
#include <memorycategory.h>
#include <filecategory.h>


#include "ut_category.h"

void Ut_Category::init()
{
    QStringList compIds;
    compIds << "CompId1" << "CompId2" << "Uncategorized";
    memCat = new MemoryCategory ("Name", "TitleId", "ParentId",
                                 "SubtitleId", "Subtitle",
                                 "IconId", 1, compIds
                                 );
    invalidMemCat = new MemoryCategory ("");
    fileCat = new FileCategory ("xxx");
}

void Ut_Category::cleanup()
{
    delete memCat;
    delete fileCat;
    delete invalidMemCat;
}

void Ut_Category::initTestCase()
{
}

void Ut_Category::cleanupTestCase()
{
}

void Ut_Category::testConstructor()
{
}


void Ut_Category::testParentId()
{
    QCOMPARE (memCat->parentId(), QString("ParentId"));
    QCOMPARE (invalidMemCat->parentId(), QString(""));
    QCOMPARE (fileCat->parentId(), QString());
}


void Ut_Category::testName()
{
    // name
    QCOMPARE (memCat->name(), QString("Name"));
    QCOMPARE (invalidMemCat->name(), QString(""));
    QCOMPARE (fileCat->name(), QString());
}


void Ut_Category::testTitle()
{
    // title
    QCOMPARE (memCat->title(), QString("!! Name"));
    QCOMPARE (invalidMemCat->title(), QString());
    QCOMPARE (fileCat->title(), QString());

    // titleId
    QCOMPARE (memCat->titleId(), QString("TitleId"));
    QCOMPARE (invalidMemCat->titleId(), QString());
    QCOMPARE (fileCat->titleId(), QString());
}


void Ut_Category::testSubtitle()
{
    // title
    QCOMPARE (memCat->subtitle(), QString("!! Subtitle"));
    QCOMPARE (invalidMemCat->subtitle(), QString(""));
    QCOMPARE (fileCat->subtitle(), QString(""));

    // subtitleId
    QCOMPARE (memCat->subtitleId(), QString("SubtitleId"));
    QCOMPARE (invalidMemCat->subtitleId(), QString());
    QCOMPARE (fileCat->subtitleId(), QString());
}


void Ut_Category::testIcon()
{
    QCOMPARE (memCat->iconId(), QString("IconId"));
    QCOMPARE (invalidMemCat->iconId(), QString());
    QCOMPARE (fileCat->iconId(), QString());
}


void Ut_Category::testOrder()
{
    QCOMPARE (memCat->order(), 1);
    // if order is unspecified, the category must be put last:
    QCOMPARE (invalidMemCat->order(), 0);
    QCOMPARE (fileCat->order(), 999999);

    // orderlessthen
    QVERIFY (!Category::orderLessThan(memCat, invalidMemCat));
    QVERIFY (Category::orderLessThan(memCat, fileCat));
    QVERIFY (!Category::orderLessThan(memCat, memCat));
}


void Ut_Category::testReferenceIds()
{
    QStringList result;
    result << "TitleId" << "Name" << "CompId1" << "CompId2" << "Uncategorized";
    QCOMPARE (memCat->referenceIds(), result);
}


void Ut_Category::testIdMatch()
{
    QVERIFY (memCat->idMatch ("TitleId"));
    QVERIFY (memCat->idMatch ("CompId2"));
    QVERIFY (memCat->idMatch ("Name"));
    QVERIFY (!memCat->idMatch ("!! Name"));
    QVERIFY (!memCat->idMatch ("CompId1x"));
}


void Ut_Category::testIsValid()
{
    QVERIFY (memCat->isValid());
    QVERIFY (!invalidMemCat->isValid());
    QVERIFY (!fileCat->isValid());
}


void Ut_Category::testChildren()
{
    MemoryCategory cat1 ("test1");
    MemoryCategory cat2 ("test2");

    // the children has to be sorted by order
    cat1.addChild (fileCat);
    cat1.addChild (invalidMemCat);
    cat1.addChild (memCat);
    QCOMPARE (cat1.children().count(), 3);
    QCOMPARE (cat1.children().at(0), invalidMemCat); // has 0 order
    QCOMPARE (cat1.children().at(1), memCat); // has 1 order
    QCOMPARE (cat1.children().at(2), fileCat); // has 9999999

    // try it with another sequence
    cat2.addChild (invalidMemCat);
    cat2.addChild (memCat);
    cat2.addChild (fileCat);
    QCOMPARE (cat2.children().count(), 3);
    QCOMPARE (cat2.children().at(0), invalidMemCat); // has 0 order
    QCOMPARE (cat2.children().at(1), memCat); // has 1 order
    QCOMPARE (cat2.children().at(2), fileCat); // has 9999999
}


void Ut_Category::testContainsUncategorized()
{
    QVERIFY (memCat->containsUncategorized());
    QVERIFY (!invalidMemCat->containsUncategorized());
    QVERIFY (!fileCat->containsUncategorized());
}



QTEST_APPLESS_MAIN(Ut_Category)

