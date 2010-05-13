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

#ifndef UT_DCPWRONGAPPLETS_H
#define UT_DCPWRONGAPPLETS_H

#include <QtTest/QtTest>
#include <QObject>

class Ut_DcpWrongApplets : public QObject
{
    Q_OBJECT

private slots:
    void init();
    void cleanup();
    void initTestCase();
    void cleanupTestCase();

    void testBacktraceLineIsAnApplet();
    void testMarkAppletAsBad();
    void testSomeCrashHappened();
    void testTerminationSignalHandler();
    void testQueryBadApplets();
    void testConstructor();
    void testInstanceNDestroy();
    void testIsAppletRecentlyCrashed();
    void testDisable();
    void testGConfRecursiveRemove();
    void testRemoveBadsOnDcpTimeStampChange();
};

#endif
