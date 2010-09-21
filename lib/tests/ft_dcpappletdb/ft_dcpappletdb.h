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

#ifndef FT_DCPAPPLETDB_H
#define FT_DCPAPPLETDB_H

#include <QtTest/QtTest>
#include <QObject>

// the real unit/DcpAppletDb class declaration
#include <dcpappletdb.h>

Q_DECLARE_METATYPE(DcpAppletDb*);

class Ft_DcpAppletDb : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void cleanupTestCase();
    void init();
    void cleanup();

    void testCreateAndDestroy();
    void testInstance();
    void testAddContainNameFile();
    void testAddPath();
    void testAppletNames();
    void testApplet();
    void testEraseEntry();
    void testListByCategory();
#ifdef MOSTUSED
    void testListMostUsed();
#endif
    void testRefresh();
    void testAppletNamesIfWrongDesktopFile();

private:
    void printAppletListForDebug (const QString &title) const;
    static void resetUsageCounters ();
    
    DcpAppletDb* m_subject;
    QString  emptyDesktopDir, testDesktopDir, testDesktopDir2, testDesktopDir3,
             testDesktopDir4;
    QString  desktopTestFile, desktopTestFile2;
    QString  desktopDateTimeFile, desktopDisplayFile;
    QString  browserEntryName, datetimeEntryName, displayEntryName;
    QCoreApplication* qap;
};

#endif

