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

#ifndef UT_PAGEFACTORY_H
#define UT_PAGEFACTORY_H

#include <QtTest/QtTest>
#include <QObject>

// the real unit/PageFactory class declaration
#include <pagefactory.h>

Q_DECLARE_METATYPE(PageFactory*);

class Ut_PageFactory : public QObject
{
    Q_OBJECT

private slots:
    void init();
    void cleanup();
    void initTestCase();
    void cleanupTestCase();
    void testInstance();
    void testCreatePage();
    void testCreateMainPage();
    void testCreateAppletPage();
    void testCreateAppletCategoryPage();
    void testCurrentPage();
    void testChangePage();
    void testAppletWantsToStart();
    void testMainPageFirstShown();
    void testRegisterPage(); 
    void testUseless();
};

#endif
