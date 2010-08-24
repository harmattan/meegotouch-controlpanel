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

#include <dcpappletbuttons.h>

#include "ut_dcpappletbuttons.h"
#include "maintranslations.h"
#include <mlinearlayoutpolicy.h>
#include <DcpAppletMetadata>
#include <DcpAppletObject>
#include <DcpContentItem>


#define fakeInfo DcpMain::CategoryInfos[0]

/* a nonexistent category */
const DcpCategoryInfo zeroCategory =
{
    "qtn_bla_bla",
    "zero-category",
    PageHandle::NOPAGE,
    NULL
};


void Ut_DcpAppletButtons::init()
{
}

void Ut_DcpAppletButtons::cleanup()
{
}

void Ut_DcpAppletButtons::initTestCase()
{
}

void Ut_DcpAppletButtons::cleanupTestCase()
{
}

void Ut_DcpAppletButtons::testCreation()
{
    // if we create with a category other then mostrecentused
    DcpAppletButtons buttons1(&fakeInfo, "fake-category");
    QCOMPARE (&fakeInfo, buttons1.m_CategoryInfo);
    //      -> checks if the right widgets were added to the layout:
    QCOMPARE (buttons1.m_PortraitLayout->count(), 1);
    QCOMPARE (((DcpContentItem*)buttons1.m_PortraitLayout->
                itemAt(0))->metadata()->name(),
              QString("fake-name"));

    // if we create with mostrecentused
    DcpAppletButtons buttons2(&DcpMain::mostUsedCategory, "MostUsed");
    QCOMPARE (&DcpMain::mostUsedCategory, buttons2.m_CategoryInfo);
    //      -> checks if the right widgets were added to the layout:
    QCOMPARE (buttons2.m_PortraitLayout->count(), 1);
    QCOMPARE (((DcpContentItem*)buttons2.m_PortraitLayout->
                itemAt(0))->metadata()->name(),
              QString("mostUsed-name"));
}

void Ut_DcpAppletButtons::testAddComponent()
{
    // create an empty appletbuttons:
    DcpAppletButtons buttons1(&zeroCategory, "null");
    QCOMPARE (buttons1.m_PortraitLayout->count(), 0);

    // add a button:
    DcpAppletMetadata* metadata = new DcpAppletMetadata("fake");
    buttons1.addComponent(metadata);
    QCOMPARE (buttons1.m_PortraitLayout->count(), 1);
    QCOMPARE (((DcpContentItem*)buttons1.m_PortraitLayout->
                itemAt(0))->metadata()->name(),
              QString("fake-name"));
}

void Ut_DcpAppletButtons::testReload()
{
    // create an empty appletbuttons:
    DcpAppletButtons buttons1(&zeroCategory, "null");
    QCOMPARE (buttons1.m_PortraitLayout->count(), 0);

    // change the categoryname to the test one and reload:
    // the fake applet should be loaded
    buttons1.m_CategoryInfo = &fakeInfo;
    buttons1.reload();
    QCOMPARE (buttons1.m_PortraitLayout->count(), 1);
    QCOMPARE (((DcpContentItem*)buttons1.m_PortraitLayout->
                itemAt(0))->metadata()->name(),
              QString("fake-name"));

    // change to mostuseditems and reload: applet count should stay the same,
    // but the one applet changes
    buttons1.m_CategoryInfo = &DcpMain::mostUsedCategory;
    buttons1.reload();

    // note, this is 2 because the widgets are deleted with deleteLater
    // and there is no eventloop :(
    // not sure how to fix it
    QCOMPARE (buttons1.m_PortraitLayout->count(), 2);
    QCOMPARE (((DcpContentItem*)buttons1.m_PortraitLayout->
                itemAt(1))->metadata()->name(),
              QString("mostUsed-name"));
}

QTEST_APPLESS_MAIN(Ut_DcpAppletButtons)

