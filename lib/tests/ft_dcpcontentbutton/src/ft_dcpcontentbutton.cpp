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

#include "ft_dcpcontentbutton.h"
#include <DcpAppletMetadata>
#include <DcpAppletObject>
#include <QFileInfo>
#include <QCoreApplication>

const QString DesktopFile("/buttonapplet.desktop");

void Ft_DcpContentButton::initTestCase()
{
    static int c = 0;
    static QByteArray arg("dummyarg");
    char *argp = arg.data();

    qap = new QCoreApplication(c, &argp);
    qInstallMsgHandler (0);

    // this makes the test able to run locally or installed:
    m_DesktopFile = QCoreApplication::applicationDirPath() + DesktopFile;
    if (!QFileInfo (m_DesktopFile).exists ()) {
        m_DesktopFile = QString(DATADIR) + DesktopFile;
    } else {
        DcpAppletMetadata::setDefaultSOPath (QCoreApplication::applicationDirPath());
    }
}

void Ft_DcpContentButton::cleanupTestCase()
{
}

void Ft_DcpContentButton::init()
{
    m_Target = new DcpContentButton();
}

void Ft_DcpContentButton::cleanup()
{
    delete m_Target;
}

void Ft_DcpContentButton::testConstructor()
{
    QVERIFY (m_Target);
}

void Ft_DcpContentButton::testSetApplet()
{
    m_Target->setApplet (0);
    QVERIFY(!m_Target->applet());
    DcpAppletMetadata *metadata = new DcpAppletMetadata(m_DesktopFile);
    
    QVERIFY(metadata);
    DcpAppletObject* applet = new DcpAppletObject(metadata);
    QVERIFY(applet->applet());
    m_Target->setApplet (applet);
    QVERIFY(m_Target->applet());
    QCOMPARE(m_Target->applet(), applet);
}

void Ft_DcpContentButton::testTDriverID()
{
    QString tdriver = "12345";
    m_Target->setTDriverID(tdriver);

    QCOMPARE (m_Target->TDriverID(), tdriver);
}

void Ft_DcpContentButton::testButtonPhases()
{

}

QTEST_APPLESS_MAIN(Ft_DcpContentButton)

