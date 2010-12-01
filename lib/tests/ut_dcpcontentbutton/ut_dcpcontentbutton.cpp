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

#include "ut_dcpcontentbutton.h"
#include "dcpcontentbutton_p.h"

void Ut_DcpContentButton::initTestCase()
{
}

void Ut_DcpContentButton::cleanupTestCase()
{
}

void Ut_DcpContentButton::init()
{
    m_Target = new DcpContentButton();
}

void Ut_DcpContentButton::cleanup()
{
    delete m_Target;
}

void Ut_DcpContentButton::testConstructor()
{
    QVERIFY (m_Target);
}

void Ut_DcpContentButton::testSetApplet()
{
    m_Target->setApplet (0);
    QVERIFY(!m_Target->d_ptr->m_Applet);

    DcpAppletObject* applet =
        new DcpAppletObject(new DcpAppletMetadata("fake"));
    m_Target->setApplet (applet);

    // was the applet set?
    QCOMPARE (m_Target->d_ptr->m_Applet, applet);

    // were the signals connected?
    // ... TODO: briefChanged from the applet and clicked to the applet
}

void Ut_DcpContentButton::testTDriverID()
{
    QString tdriver = "12345";
    m_Target->setTDriverID(tdriver);
    QCOMPARE (m_Target->TDriverID(), tdriver);
}

void Ut_DcpContentButton::testUpdateContents()
{
    
}

void Ut_DcpContentButton::testRetranslateUi()
{
    DcpAppletObject* applet =
        new DcpAppletObject(new DcpAppletMetadata("fake"));
    m_Target->setApplet (applet);

    // test if updateText gets called on retranslateUi
    m_Target->setText ("xxx");
    m_Target->retranslateUi();
    QCOMPARE (m_Target->text(), applet->text2());
}

void Ut_DcpContentButton::testShowHideEvent()
{
    DcpAppletObject* applet =
        new DcpAppletObject(new DcpAppletMetadata("fake"));
    m_Target->setApplet (applet);

    // check if the widget updates on showEvent
    m_Target->setText ("xxx");
    m_Target->showEvent(0);
    QCOMPARE (m_Target->text(), applet->text2());

    // check if signals gets reconnected on showEvent
    // ... TODO
}

void Ut_DcpContentButton::testUpdateText()
{
    DcpAppletObject* applet =
        new DcpAppletObject(new DcpAppletMetadata("fake"));
    m_Target->setApplet (applet);
    m_Target->setText ("xxx");

    m_Target->updateText();

    // updates the texts:
    QCOMPARE (m_Target->text(), QString("fake-text2"));
}


QTEST_APPLESS_MAIN(Ut_DcpContentButton)

