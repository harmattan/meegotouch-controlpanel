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
#include <DcpAppletMetadata>

#include <QStandardItemModel>
#include <QStandardItem>

#include "dcpcontentitemcellcreator.h"

#define fakeInfo DcpMain::CategoryInfos[0]

/* a nonexistent category */
const DcpCategoryInfo zeroCategory =
{
    "qtn_bla_bla",
    "qtn_bla_bla",
    "zero-category",
    PageHandle::NOPAGE,
    0,
    0
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
    DcpAppletButtons buttons1(&fakeInfo);
    QCOMPARE (&fakeInfo, buttons1.m_CategoryInfo);
    //      -> checks if the right items were added to the model:
    QCOMPARE (buttons1.metadataCount(), 1);
    QCOMPARE (buttons1.appletMetadata(0)->name(),
              QString("fake-name"));

    // if we create with mostrecentused
    DcpAppletButtons buttons2(&DcpMain::mostUsedCategory);
    QCOMPARE (&DcpMain::mostUsedCategory, buttons2.m_CategoryInfo);
    //      -> checks if the right items were added to the model:
    QCOMPARE (buttons2.metadataCount(), 1);
    QCOMPARE (buttons2.appletMetadata(0)->name(),
              QString("mostUsed-name"));
}

void Ut_DcpAppletButtons::testAddComponent()
{
    // create an empty appletbuttons:
    DcpAppletButtons buttons1(&zeroCategory);
    QCOMPARE (buttons1.metadataCount(), 0);

    QStandardItemModel model;

    // add a button:
    DcpAppletMetadata* metadata = new DcpAppletMetadata("fake");
    buttons1.addComponent(metadata, &model);
    QCOMPARE (model.rowCount(), 1);
    QCOMPARE (model.item(0)->data().value<DcpAppletMetadata*>()->name(),
              QString("fake-name"));
    delete metadata;
}

void Ut_DcpAppletButtons::testReload()
{
    // create an empty appletbuttons:
    DcpAppletButtons buttons1(&zeroCategory);
    QCOMPARE (buttons1.metadataCount(), 0);

    // change the categoryname to the test one and reload:
    // the fake applet should be loaded
    buttons1.m_CategoryInfo = &fakeInfo;
    buttons1.reload();
    QCOMPARE (buttons1.metadataCount(), 1);
    QCOMPARE (buttons1.appletMetadata(0)->name(),
              QString("fake-name"));

    // change to mostuseditems and reload: applet count should stay the same,
    // but the one applet changes
    buttons1.m_CategoryInfo = &DcpMain::mostUsedCategory;
    buttons1.reload();

    QCOMPARE (buttons1.metadataCount(), 1);
    QCOMPARE (buttons1.appletMetadata(0)->name(),
              QString("mostUsed-name"));
}

QTEST_APPLESS_MAIN(Ut_DcpAppletButtons)

