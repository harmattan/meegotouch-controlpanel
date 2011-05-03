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


#include "ut_dcpappletplugin.h"
#include "dcpappletplugin_p.h"
#include "qpluginloader-fake.h"
#include "dcpappletmetadata-fake.h"

void Ut_DcpAppletPlugin::init()
{
}

void Ut_DcpAppletPlugin::cleanup()
{
    delete m_subject;
    m_subject = 0;
}

void Ut_DcpAppletPlugin::initTestCase()
{
}

void Ut_DcpAppletPlugin::cleanupTestCase()
{
}

/**
 * checks if appletloader calls applet's init function
 */
void Ut_DcpAppletPlugin::testLoadBinaryOk()
{
    DcpAppletMetadataFake::appletType = 
        DcpAppletMetadataFake::TYPE_BINARY;
    qPluginLoaderFakeSuccessful = true;
    DcpAppletMetadata *metadata = new DcpAppletMetadata("dummy-binary");
    DcpAppletPluginApplet *appl = NULL;
    m_subject = new DcpAppletPlugin(metadata);
    QVERIFY(m_subject->applet());
    appl = dynamic_cast<DcpAppletPluginApplet*>(m_subject->applet());
    QVERIFY(appl && appl->initialized());
    QVERIFY(m_subject->isAppletLoaded());
    delete m_subject;

    m_subject = new DcpAppletPlugin(metadata, true);
    QVERIFY(m_subject->applet());
    appl = dynamic_cast<DcpAppletPluginApplet*>(m_subject->applet());
    QVERIFY(appl && appl->initialized());
    delete metadata;
    QVERIFY(m_subject->isAppletLoaded());
}

/**
 * checks if appletloader returns 0 on load error and
 * errorMsg() contains the load error message coming from the QPluginLoader
 */
void Ut_DcpAppletPlugin::testLoadBinaryError()
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
 * checks if metadata() returns the same pointer that was given in
 * initialization
 */
void Ut_DcpAppletPlugin::testMetadata()
{
    DcpAppletMetadata *metadata = new DcpAppletMetadata("dummy-binary");
    m_subject = new DcpAppletPlugin(metadata);
    QVERIFY(m_subject->metadata() == metadata);
    delete metadata;
}

void Ut_DcpAppletPlugin::testInterfaceVersion()
{
    DcpAppletMetadataFake::appletType = 
        DcpAppletMetadataFake::TYPE_BINARY;
    qPluginLoaderFakeSuccessful = true;
    DcpAppletMetadata *metadata = new DcpAppletMetadata("dummy-binary");
    m_subject = new DcpAppletPlugin(metadata);
    QVERIFY(m_subject->applet());
    QCOMPARE(m_subject->interfaceVersion(), 8);
    delete m_subject->d_ptr->appletInstance;
    m_subject->d_ptr->appletInstance = 0;
    QCOMPARE(m_subject->interfaceVersion(), -1);
    delete metadata;
}

void Ut_DcpAppletPlugin::testLoadHints()
{
    DcpAppletPlugin::setDefaultLoadHints(1);
    QCOMPARE(DcpAppletPluginPrivate::defaultLoadHints, 1);
}

QTEST_APPLESS_MAIN(Ut_DcpAppletPlugin)
