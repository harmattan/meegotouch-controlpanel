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

#ifndef UT_DCPAPPLETCATEGORYPAGE_H
#define UT_DCPAPPLETCATEGORYPAGE_H

#include <QtTest/QtTest>
#include <QObject>

// the real unit/DcpAppletCategoryPage class declaration
#include <dcpappletcategorypage.h>

Q_DECLARE_METATYPE(DcpAppletCategoryPage*);

class Ut_DcpAppletCategoryPage : public QObject
{
    Q_OBJECT

private slots:
    void init();
    void cleanup();
    void initTestCase();
    void cleanupTestCase();
    void testCreation();
    void testCreateContent();
    void testAppletCategory();
    void testCategoryInfo();
    void testReload();
    void testCleanup();
    void testSetTitleId();
    void testBack();
    void testRetranslateUi();
    void testAddComponent();
    

private:
    DcpAppletCategoryPage* m_subject;
};

#endif
