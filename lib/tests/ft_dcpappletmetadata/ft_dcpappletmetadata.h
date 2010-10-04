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

#ifndef FT_DCPAPPLETMETADATA_H
#define FT_DCPAPPLETMETADATA_H

#include <QtTest/QtTest>
#include <QObject>

// the real unit/DcpAppletMetadata class declaration
#include <dcpappletmetadata.h>

Q_DECLARE_METATYPE(DcpAppletMetadata*);

class Ft_DcpAppletMetadata : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void cleanupTestCase();
    void init();
    void cleanup();

    void testCreateAndDestroy();
    void testIsValid();
    void testIsModified();
    void testName();
    void testFileName();
    void testCategory();
    void testBinary();
    void testFullBinary();
    void testWidgetTypeID();
    void testAlign();
    void testToggle();
//    void testText1(); it can't be tested
    void testImageName();
    void testOrder();
#ifdef MOSTUSED
    void testUsage();
#endif
    void testPart();

private:
    DcpAppletMetadata* m_subject;
    QString            desktopOrigFile, desktopTestFile, desktopBadTestFile;
    QString            appletDir, appletSo;
    QCoreApplication*  qap;
};

#endif
