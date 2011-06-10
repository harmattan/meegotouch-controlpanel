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

#ifndef UT_DCPAPPLETWIDGET_H
#define UT_DCPAPPLETWIDGET_H

#include <QtTest/QtTest>
#include <QObject>

// the real unit/DcpAppletWidget class declaration
#include <dcpappletwidget.h>

Q_DECLARE_METATYPE(DcpAppletWidget*);

class Ut_DcpAppletWidget : public QObject
{
    Q_OBJECT

private slots:
    void init();
    void cleanup();
    void initTestCase();
    void cleanupTestCase();

    void testConstruct();
    void testSetReferer();
    void testBack();
    void testProperties();
};

#endif

