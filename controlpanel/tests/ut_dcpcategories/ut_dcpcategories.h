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

#ifndef UT_DCPCATEGORIES_H
#define UT_DCPCATEGORIES_H

#include <QtTest/QtTest>
#include <QObject>

#include <dcpcategories.h>
#include <memorycategory.h>

Q_DECLARE_METATYPE(DcpCategories*);

class Ut_DcpCategories : public QObject
{
    Q_OBJECT

private slots:
    void init();
    void cleanup();
    void initTestCase();
    void cleanupTestCase();

    void testInstance();
    void testCategoryById();
    void testCategoryChildren();
    void testHasCategory();
    void testMainPageCategory();


private:
    DcpCategories* m_subject;
    MemoryCategory* m_c1;
    MemoryCategory* m_c2;
    MemoryCategory* m_c3;
    MemoryCategory* m_c11;
    MemoryCategory* m_c12;
    MemoryCategory* m_c13;
    MemoryCategory* m_c31;
};

#endif

