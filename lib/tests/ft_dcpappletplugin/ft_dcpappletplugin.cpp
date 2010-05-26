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

#include <QObject>
#include <QGraphicsSceneMouseEvent>

#include "dcpappletplugin.h"


#include "ft_dcpappletplugin.h"
#include "qpluginloader-fake.h"
#include "dcpappletmetadata-fake.h"

void Ft_DcpAppletPlugin::init()
{
}

void Ft_DcpAppletPlugin::cleanup()
{
    delete m_subject;
    m_subject = 0;
}

void Ft_DcpAppletPlugin::initTestCase()
{
}

void Ft_DcpAppletPlugin::cleanupTestCase()
{
}

/**
 * checks if appletloader calls applet's init function
 */
void Ft_DcpAppletPlugin::testLoadBinaryOk()
{
    DcpAppletMetadataFake::appletType = 
        DcpAppletMetadataFake::TYPE_BINARY;
    qPluginLoaderFakeSuccessful = true;
    DcpAppletMetadata *metadata = new DcpAppletMetadata("dummy-binary");
    m_subject = new DcpAppletPlugin(metadata);
    QVERIFY(m_subject->applet());
    QVERIFY(
        dynamic_cast<DcpAppletPluginApplet*>(m_subject->applet())->initialized()
        );
    delete metadata;
    QVERIFY(m_subject->isAppletLoaded());
}

/**
 * checks if appletloader returns 0 on load error and
 * errorMsg() contains the load error message coming from the QPluginLoader
 */
void Ft_DcpAppletPlugin::testLoadBinaryError()
{
    DcpAppletMetadataFake::appletType = 
        DcpAppletMetadataFake::TYPE_BINARY;
    qPluginLoaderFakeSuccessful = false;
    DcpAppletMetadata *metadata = new DcpAppletMetadata("dummy-binary");
    m_subject = new DcpAppletPlugin(metadata);
    QVERIFY(!m_subject->applet());
    QVERIFY(m_subject->errorMsg().contains(fakeErrorMsg));
    QVERIFY(!m_subject->isAppletLoaded());
    delete metadata;
}

/**
 * TODO
 */
void Ft_DcpAppletPlugin::testLoadDsl()
{
    DcpAppletMetadataFake::appletType = 
        DcpAppletMetadataFake::TYPE_DSL;
    QSKIP("TODO: test DSL loading", SkipAll);
}


/**
 * checks if metadata() returns the same pointer that was given in
 * initialization
 */
void Ft_DcpAppletPlugin::testMetadata()
{
    DcpAppletMetadata *metadata = new DcpAppletMetadata("dummy-binary");
    m_subject = new DcpAppletPlugin(metadata);
    QVERIFY(m_subject->metadata() == metadata);
    delete metadata;
}

void Ft_DcpAppletPlugin::testInterfaceVersion()
{
    DcpAppletMetadataFake::appletType = 
        DcpAppletMetadataFake::TYPE_BINARY;
    qPluginLoaderFakeSuccessful = true;
    DcpAppletMetadata *metadata = new DcpAppletMetadata("dummy-binary");
    m_subject = new DcpAppletPlugin(metadata);
    QVERIFY(m_subject->applet());
    QCOMPARE(m_subject->interfaceVersion(), 3);
    delete m_subject;
    qPluginLoaderFakeSuccessful = false;
    m_subject = new DcpAppletPlugin(metadata);
    QCOMPARE(m_subject->interfaceVersion(), -1);
    delete metadata;
}

QTEST_APPLESS_MAIN(Ft_DcpAppletPlugin)
