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

/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et sw=4 ts=4 sts=4: */
#include <QDebug>
#include <QObject>
#include <QGraphicsSceneMouseEvent>
#include <QDir>
#include <QMap>

#include "dcpappletdb.h"

#include "ft_dcpappletdb.h"
#include <MGConfItem>
#include "dcpappletobject-fake.h"

#include "dcpdebug.h"

void Ft_DcpAppletDb::initTestCase()
{
    static int c = 0;
    static QByteArray arg("dummyarg");
    char *argp = arg.data();

    qap = new QCoreApplication(c, &argp);
    qInstallMsgHandler (0);
    QString dataDir(qApp->applicationDirPath() + 
                       "/ft_dcpappletdb-data/");

    emptyDesktopDir = dataDir + "emptyDesktopDir/"; // a non-existent dir
    testDesktopDir = dataDir + "desktops/";
    testDesktopDir2 = dataDir + "desktops2/";
    testDesktopDir3 = dataDir + "desktops3/";
    testDesktopDir4 = dataDir + "desktops4/";
    desktopTestFile = testDesktopDir + "test.desktop";
    desktopTestFile2 = testDesktopDir + "test2.desktop";
    desktopDateTimeFile = testDesktopDir2 + "datetime.desktop";
    desktopDisplayFile = testDesktopDir2 + "display.desktop";
    browserEntryName = "Browser";
    datetimeEntryName = "Date & Time";
    displayEntryName = "Display";

    /*
     * First we delete all the usage counter, so the previous runs will not 
     * ruin the test. 
     */
    Ft_DcpAppletDb::resetUsageCounters ();    
}

void Ft_DcpAppletDb::cleanupTestCase()
{
    /*
     * We clean up the usage counters just to be sure.
     */
    Ft_DcpAppletDb::resetUsageCounters ();

    delete qap;
}

void 
Ft_DcpAppletDb::resetUsageCounters () 
{
    int                   retval;

    /*
     * The gconftool-2 is in the same package gconfd-2 is found, so we can
     * assume it is installed.
     */
    retval = system (
            "gconftool-2 --recursive-unset /apps/duicontrolpanel/usagecount");
    if (retval == -1)
        DCP_WARNING ("Failed resetting usage counters: %m");
}

void Ft_DcpAppletDb::init()
{
    /*
     * FIXME: I removed the initInstance() function simply because it refused to
     * initialize an existing object, it was only usefull to initialize new
     * instances and of course that's the constructor or the instance() function
     * is for.
     * However this init() function has no documentation, so I don't know how to
     * remove it entirely. So I added instance() instead of initInstance()...
     */
    QVERIFY ((m_subject = DcpAppletDb::instance(emptyDesktopDir)));
}

void Ft_DcpAppletDb::cleanup()
{
    DcpAppletDb::destroy();
}

void Ft_DcpAppletDb::testCreateAndDestroy()
{
    if (QTest::currentTestFailed()) return;
}

void Ft_DcpAppletDb::testInstance()
{
    if (QTest::currentTestFailed()) return;

    QVERIFY((m_subject == DcpAppletDb::instance()));
}

void Ft_DcpAppletDb::testAddContainNameFile()
{
    if (QTest::currentTestFailed()) return;

    QVERIFY(!m_subject->containsFile(desktopTestFile));

    QVERIFY(m_subject->addFile(desktopTestFile));
    QVERIFY(m_subject->containsFile(desktopTestFile));

    QVERIFY(!m_subject->addFile(desktopTestFile));
    /* this test was commented out because current implementation
     * requires that two applets with same name can be loaded.
     * eg. display language for controlpanel and for suw */
//    QVERIFY(!m_subject->addFile(desktopTestFile2));

    QVERIFY(m_subject->containsName(browserEntryName));
    QVERIFY(!m_subject->containsName(browserEntryName) + "x");
}

void Ft_DcpAppletDb::testAddPath()
{
    if (QTest::currentTestFailed()) return;

    QVERIFY(m_subject->addPath(testDesktopDir2));
    QVERIFY(m_subject->containsFile(desktopDateTimeFile));
    QVERIFY(m_subject->containsFile(desktopDisplayFile));
}

void Ft_DcpAppletDb::testAppletNames()
{
    if (QTest::currentTestFailed()) return;

    QVERIFY(m_subject->addPath(testDesktopDir2));

    QVERIFY(m_subject->appletNames().length() == 2);
    QVERIFY(m_subject->appletNames().contains(datetimeEntryName));
    QVERIFY(m_subject->appletNames().contains(displayEntryName));
}

/* This tests that an invalid desktop file does not stop the
 * parsing of the remaining desktop files. */
void Ft_DcpAppletDb::testAppletNamesIfWrongDesktopFile()
{
    // should return with an error:
    QVERIFY(!m_subject->addPath(testDesktopDir4));

    // should not stop parsing the other desktop files:
    QVERIFY(m_subject->appletNames().length() == 2);
    QVERIFY(m_subject->appletNames().contains(browserEntryName));
    QVERIFY(m_subject->appletNames().contains(displayEntryName));
}


void Ft_DcpAppletDb::testApplet()
{
    if (QTest::currentTestFailed()) return;

    QVERIFY(m_subject->addPath(testDesktopDir2));

  //  QWARN("\n\t ---- Expected QWARN : No such applet: 'xxx' ----");
    QVERIFY(m_subject->applet(displayEntryName));
    QVERIFY(m_subject->applet(datetimeEntryName));
    QVERIFY(!m_subject->applet("xxx"));
}

void Ft_DcpAppletDb::testEraseEntry()
{
    if (QTest::currentTestFailed()) return;

    DcpAppletObject  *applet;

    QVERIFY(m_subject->addPath(testDesktopDir2));
    QVERIFY(m_subject->appletNames().length() == 2);
    QVERIFY((applet=m_subject->applet(datetimeEntryName)));
    m_subject->eraseEntry(applet->metadata());
    QVERIFY(m_subject->appletNames().length() == 1);
}

void Ft_DcpAppletDb::testListByCategory()
{
    if (QTest::currentTestFailed()) return;

    QVERIFY(m_subject->addPath(testDesktopDir3));
    QVERIFY(m_subject->listByCategory("Application").length() == 1);
    QVERIFY(m_subject->listByCategory("Connectivity").length() == 1);
    QVERIFY(m_subject->listByCategory("Device utilities").length() == 1);
    QVERIFY(m_subject->listByCategory("Look & Feel").length() == 3);
    QVERIFY(m_subject->listByCategory("Regional settings").length() == 3);
    QVERIFY(m_subject->listByCategory("Sound").length() == 2);
    QVERIFY(m_subject->listByCategory("Startup").length() == 4);
}

void 
Ft_DcpAppletDb::printAppletListForDebug (
        const QString &title) const
{
    #ifdef DEBUG
    DcpAppletMetadataList applets = m_subject->list();

    DCP_DEBUG ("-------------- The applet list %12s ---------------", 
            DCP_STR(title));
    DCP_DEBUG ("Usage | Name");
    foreach (DcpAppletMetadata *metadata, applets) {
        DCP_DEBUG (" %4d | %s", metadata->usage(), DCP_STR(metadata->name()));
    }
    DCP_DEBUG ("----------------------------------------------------------");
    #else
    Q_UNUSED (title);
    #endif
}


void Ft_DcpAppletDb::testListMostUsed()
{
    m_subject->addPath (testDesktopDir3);
    DcpAppletMetadataList applets = m_subject->list();
    const int             maxN = 10;
    int                   n = 0;

    printAppletListForDebug ("Initial state");

    for (DcpAppletMetadataList::iterator iter = applets.begin();
         iter != applets.end() && n < maxN; ++iter) {
        // "activate" applet n times
        for (int i = 0; i < n; ++i) {
            (*iter)->incrementUsage();
        }
        ++n;
    }

    // most used list shall reverse the first maxN applets in the list
    DcpAppletMetadataList mostUsed = m_subject->listMostUsed();
    DcpAppletMetadataList::iterator orig = applets.begin() + n - 1;
    for (DcpAppletMetadataList::iterator iter = mostUsed.begin();
         iter != mostUsed.end() && orig != applets.end(); ++iter) {
        QCOMPARE(*iter, *orig);
        --orig;
    }
    
    printAppletListForDebug ("After the test");
}

void Ft_DcpAppletDb::testRefresh()
{
    if (QTest::currentTestFailed()) return;

    QSKIP("this test would need modifying .desktop files", SkipSingle);
}

QTEST_APPLESS_MAIN(Ft_DcpAppletDb)
