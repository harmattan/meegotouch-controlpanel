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

#ifndef UT_DCPWIDGET_H
#define UT_DCPWIDGET_H

#include <QtTest/QtTest>
#include <QObject>

// the real unit/DcpWidget class declaration
#include <dcpwidget.h>

Q_DECLARE_METATYPE(DcpWidget*);

class Ut_DcpWidget : public QObject
{
    Q_OBJECT

private slots:
    void init();
    void cleanup();
    void initTestCase();
    void cleanupTestCase();
    void testCreation();
    void testWidgetId();
    void testBack();
    void testPagePans();
    void testProgressIndicator();
    void testUseless();
private:
    DcpWidget* m_subject;
};

#endif
