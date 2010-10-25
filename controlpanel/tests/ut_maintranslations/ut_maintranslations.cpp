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
        QT_TRID_NOOP ("qtn_sett_main_applications"),
        "Applications",
        PageHandle::Applications,
        0,
        0
    },
    {
        // The last element must have the .titleId == 0
        0, 0, 0, PageHandle::NOPAGE, 0, 0
    }};
 
    QCOMPARE(DcpMain::findCategoryInfo(PageHandle::CONNECTIVITY),
             &DcpMain::CategoryInfos[0]);
    
    QCOMPARE(DcpMain::findCategoryInfo(PageHandle::Applications, &otherInfos[0]),
             &otherInfos[0]);

    QVERIFY(!DcpMain::findCategoryInfo(PageHandle::CONNECTIVITY, &otherInfos[0]));

    QCOMPARE(DcpMain::findCategoryInfo("qtn_sett_main_connections"),
             &DcpMain::CategoryInfos[0]);
    QVERIFY(!DcpMain::findCategoryInfo("unknown"));
    
    QCOMPARE(DcpMain::findCategoryInfo("qtn_sett_main_applications", &otherInfos[0]),
             &otherInfos[0]);
    QVERIFY(!DcpMain::findCategoryInfo("unknown", &otherInfos[0]));
}

void Ut_maintranslations::testIsCategoryNameEnlisted()
{
    QVERIFY(DcpMain::isCategoryNameEnlisted("qtn_sett_main_personalize"));
    QVERIFY(!DcpMain::isCategoryNameEnlisted("qtn_sett_unknown"));
    QVERIFY(DcpMain::isCategoryNameEnlisted("Startup"));
    
}

QTEST_APPLESS_MAIN(Ut_maintranslations)
