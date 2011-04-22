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

#include <dcpappletbuttons.h>
#include "ut_dcpappletbuttons.h"
#include <DcpAppletMetadata>
#include "dcpcontentitemcellcreator.h"
#include "category.h"
#include "dcpcategories.h"
#include "dcpappletmanager.h"

#include <QObject>
#include <QGraphicsSceneMouseEvent>
#include <QStandardItemModel>
#include <QStandardItem>
#include <DcpWidgetTypes>

#define fakeInfo *(DcpCategories::instance()->categoryById("fake-category"))
#define zeroCategory *(DcpCategories::instance()->categoryById("ZERO"))
#define mostUsedCategory *(DcpCategories::instance()->categoryById("mostUsed"))

extern int currentWidgetType;

void Ut_DcpAppletButtons::init()
{
    DcpAppletManager::instance()->loadMetadata();
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

#if 0
    FIXME put back this test MOSTUSED
    // if we create with mostUsed
    DcpAppletButtons buttons2(&mostUsedCategory);
    QCOMPARE (&mostUsedCategory, buttons2.m_CategoryInfo);
    //      -> checks if the right items were added to the model:
    QCOMPARE (buttons2.metadataCount(), 1);
    QCOMPARE (buttons2.appletMetadata(0)->name(),
              QString("mostUsed-name"));
#endif
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

    currentWidgetType = DcpWidgetType::Button;
    buttons1.addComponent(metadata, &model);

    currentWidgetType = DcpWidgetType::Special;
    buttons1.addComponent(metadata, &model);

    currentWidgetType = DcpWidgetType::Slider;
    buttons1.addComponent(metadata, &model);

    delete metadata;
    currentWidgetType = 0;
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

    // change to zero category and reload: applet should be removed
    buttons1.m_CategoryInfo = &zeroCategory;
    buttons1.reload();

    QCOMPARE (buttons1.metadataCount(), 0);
}

void Ut_DcpAppletButtons::testCategoryInfo()
{
    DcpAppletButtons buttons1(&zeroCategory);

    buttons1.setCategoryInfo(&fakeInfo);
}

void Ut_DcpAppletButtons::testIDs()
{

    DcpAppletButtons buttons1(&zeroCategory);

    buttons1.setMattiID("id1");
    QCOMPARE(buttons1.m_TDriverID, QString("id1"));
    QCOMPARE(buttons1.mattiID(), QString("id1"));
    QCOMPARE(buttons1.TDriverID(), QString("id1"));

    buttons1.setTDriverID("id2");
    QCOMPARE(buttons1.m_TDriverID, QString("id2"));
    QCOMPARE(buttons1.mattiID(), QString("id2"));
    QCOMPARE(buttons1.TDriverID(), QString("id2"));
}

QTEST_APPLESS_MAIN(Ut_DcpAppletButtons)

