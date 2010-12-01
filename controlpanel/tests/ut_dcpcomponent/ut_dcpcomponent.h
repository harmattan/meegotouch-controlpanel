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

#ifndef UT_DCPCOMPONENT_H
#define UT_DCPCOMPONENT_H

#include <QtTest/QtTest>
#include <QObject>

// the real unit/DcpComponent class declaration
#include <dcpcomponent.h>

Q_DECLARE_METATYPE(DcpComponent*);

class Ut_DcpComponent : public QObject
{
    Q_OBJECT

private slots:
    void init();
    void cleanup();
    void initTestCase();
    void cleanupTestCase();
    void testSubPage();
    void testTitle();
    void testCategory();
    void testLogicalId();    
    void testTDriverID();
private:    
    DcpComponent *m_subject;    
};

#endif
