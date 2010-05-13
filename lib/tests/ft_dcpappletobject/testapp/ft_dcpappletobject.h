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

#ifndef FT_DCPAPPLETOBJECT_H
#define FT_DCPAPPLETOBJECT_H

#include <QtTest/QtTest>
#include <QObject>
#include <MApplication>

// the real unit/DcpAppletObject class declaration
#include "dcpappletobject.h"

Q_DECLARE_METATYPE(DcpAppletObject*);

class Ft_DcpAppletObject : public QObject
{
    Q_OBJECT

private slots:
    void init();
    void cleanup();
    void initTestCase();
    void cleanupTestCase();
    void testLoad();
    void testLoadManyTimes();
    void testGetters();
    

private:
    void testApplet(const char *desktopfile);
    void doAppletTest (const char *desktopfile);

    MApplication*  m_app;
};

#endif
