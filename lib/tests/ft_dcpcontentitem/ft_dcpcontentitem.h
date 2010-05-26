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

#ifndef FT_DCPCONTENTITEM_H
#define FT_DCPCONTENTITEM_H

#include <QtTest/QtTest>
#include <QObject>

#include <dcpcontentitem.h>

class Ft_DcpContentItem : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void cleanupTestCase();
    void init();
    void cleanup();

    void testConstructor();
    void testSetApplet();
    void testMattiId();
private:
    DcpContentItem* m_Target;

};

#endif // FT_DCPCONTENTITEM_H

