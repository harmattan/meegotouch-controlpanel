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

#ifndef UT_DCPCATEGORYCOMPONENT_H
#define UT_DCPCATEGORYCOMPONENT_H

#include <QtTest/QtTest>
#include <QObject>

// the real unit/DcpCategoryComponent class declaration
#include <dcpcategorycomponent.h>

Q_DECLARE_METATYPE(DcpCategoryComponent*);

class Ut_DcpCategoryComponent : public QObject
{
    Q_OBJECT

private slots:
    void init();
    void cleanup();
    void initTestCase();
    void cleanupTestCase();
    void testCreation();
    void testCreateContents();
    void testRetranslateUi();
    void testTitle();
    void testReload();
    void testGetItemCount();
    

private:
    DcpCategoryComponent* m_subject;
};

#endif
