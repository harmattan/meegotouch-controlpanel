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

#include "ft_dcpcontentitem.h"
#include "dcpappletobject.h"
#include "dcpappletmetadata.h"
#include <MApplication>

void Ft_DcpContentItem::initTestCase()
{
    int argc = 1;
    char *argv = (char *) "./ft_dcpcontentitem";
    app = new MApplication(argc, &argv);
}

void Ft_DcpContentItem::cleanupTestCase()
{
    delete app;
}

void Ft_DcpContentItem::init()
{
    m_Target = new DcpContentItem();
}

void Ft_DcpContentItem::cleanup()
{
    delete m_Target;
}

void Ft_DcpContentItem::testConstructor()
{
    // verifies that the parent is set correctly
    QVERIFY (!m_Target->parentItem());
    DcpContentItem* child = new DcpContentItem(0, m_Target);
    QCOMPARE (child->parentItem(), m_Target);
}

void Ft_DcpContentItem::testSetApplet()
{
    DcpAppletObject* applet =
        new DcpAppletObject(new DcpAppletMetadata("fake"));
    m_Target->setApplet (applet);

    // was the applet set?
    QCOMPARE (m_Target->applet(), applet);

    // were the signals connected?
    // ... TODO: briefChanged from the applet and clicked to the applet
}

void Ft_DcpContentItem::testMattiId()
{
    QString matti = "12345";
    m_Target->setMattiID(matti);
    QCOMPARE (m_Target->mattiID(), matti);
}

QTEST_APPLESS_MAIN(Ft_DcpContentItem)

