/***************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Karoliina T. Salminen <karoliina.t.salminen@nokia.com>
**
** This file is part of duicontrolpanel.
**
**
** This library is free software; you can redistribute it and/or
** modify it under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation
** and appearing in the file LICENSE.LGPL included in the packaging
** of this file.
**
****************************************************************************/

#include <QObject>
#include <QGraphicsSceneMouseEvent>

#include "dcpappletobject.h"
#include "dcpappletmetadata.h"
#include "dcpappletif.h"
#include "dcpwidgettypes.h"
#include "dcpwidget.h"
#include "dcpbrief.h"

#include "ft_dcpappletobject.h"

#define DESKTOPFILE "testapplet.desktop"
#define DESKTOPFILE2 "testapplet2.desktop"

/**
 * TODO
 * test meaningful data from brief/metadata in getters
 * test signals and slots
 */

void Ft_DcpAppletObject::init()
{
}

void Ft_DcpAppletObject::cleanup()
{
}

void Ft_DcpAppletObject::initTestCase()
{
    int argc = 1;
    char *appname = (char*) "./ft_dcpappletobject";
    m_app = new MApplication(argc, &appname);
}

void Ft_DcpAppletObject::cleanupTestCase()
{
    delete m_app;
}

// this function ensures that the test can be run locally:
DcpAppletMetadata* createMetadata (const char* fname) {
    QString fpath = DATADIR + QString("/") + fname;
    QString fpathLocal = qApp->applicationDirPath ()+ "/"+fname;
    // First we try to run it on the one from the current directory::
    if (QFileInfo(fpathLocal).exists()) {
        qWarning ("XXXApplet was run from the current dir");
        DcpAppletMetadata::setDefaultSOPath (qApp->applicationDirPath ());
        return new DcpAppletMetadata (fpathLocal);
    }
    // else we use an installed version:
    qWarning ("XXXApplet was run from installed");
    return new DcpAppletMetadata (fpath);
}


void Ft_DcpAppletObject::testLoad()
{
    testApplet(DESKTOPFILE);
}

void Ft_DcpAppletObject::testLoadManyTimes()
{    
    for (int i = 0; i < 4; ++i) {
        qDebug() << "round " << i;
        testApplet(DESKTOPFILE);
        testApplet(DESKTOPFILE2);
    }
}

void Ft_DcpAppletObject::testApplet(const char *desktopfile)
{
    DcpAppletMetadata *metadata = createMetadata(desktopfile);
    DcpAppletObject *appletObj = new DcpAppletObject(metadata);
    QVERIFY2(appletObj->isAppletLoaded(), "applet not loaded");

    DcpAppletIf *applet = appletObj->applet();
    QVERIFY2(applet, "DcpAppletObject::applet() gave NULL");

    DcpBrief *brief = applet->constructBrief();
    DcpWidget *widget = applet->constructWidget(0);
    QVERIFY(widget);
    QVERIFY(brief);

    delete widget;
    delete appletObj;

    // FIXME: test if the applet's destructor has been called
}


void Ft_DcpAppletObject::testGetters()
{
    DcpAppletMetadata *metadata = createMetadata(DESKTOPFILE);
    DcpAppletObject *appletObj = new DcpAppletObject(metadata);
    QCOMPARE(appletObj->widgetTypeID(), static_cast<int>(DcpWidgetType::Label));
    // string coming from testplugin/testapplet.cpp
    QCOMPARE(appletObj->text1(), QString("Test title 1"));


    // FIXME test these values too
    QCOMPARE(appletObj->text2(), QString("")); 
    QCOMPARE(appletObj->align(), Qt::AlignLeft);
    QCOMPARE(appletObj->toggle(), false);
    QCOMPARE(appletObj->imageName(), QString());
    QCOMPARE(appletObj->toggleIconId(), QString());


    delete appletObj;
}

QTEST_APPLESS_MAIN(Ft_DcpAppletObject)

