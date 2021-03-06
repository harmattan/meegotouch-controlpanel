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

#ifndef UT_DCPAPPLETMANAGER_H
#define UT_DCPAPPLETMANAGER_H

#include <QtTest/QtTest>
#include <QObject>

// the real unit/DcpAppletManager class declaration
#include <dcpappletmanager.h>

Q_DECLARE_METATYPE(DcpAppletManager*);

class Ut_DcpAppletManager : public QObject
{
    Q_OBJECT

private slots:
    void init();
    void cleanup();
    void initTestCase();
    void cleanupTestCase();
    void testSingleInstance();
    void testLoadDesktopFile();
    void testLoadMetadata();
    void testLoadMetadataAsync();
    void testPreloadMetadata();
    void testPreloadMetadataAsync();
    void testDesktopDirs();
    void testAccessors();
    void testUseless();

private:
    DcpAppletManager* m_subject;
};

#endif
