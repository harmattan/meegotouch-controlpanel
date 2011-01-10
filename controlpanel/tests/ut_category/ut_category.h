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

#ifndef UT_CATEGORY_H
#define UT_CATEGORY_H

#include <QtTest/QtTest>
#include <QObject>

// the real unit/Category class declaration
#include <category.h>

Q_DECLARE_METATYPE(Category*);

class Ut_Category : public QObject
{
    Q_OBJECT

private slots:
    void init();
    void cleanup();
    void initTestCase();
    void cleanupTestCase();

    void testConstructor();
    void testParentId ();
    void testName ();
    void testTitle ();
    void testSubtitle ();
    void testIcon ();
    void testOrder ();
    void testReferenceIds ();
    void testIdMatch ();
    void testIsValid ();
    void testChildren ();
    void testContainsUncategorized ();

private:
    Category* memCat;
    Category* invalidMemCat;
    Category* fileCat;

};

#endif

