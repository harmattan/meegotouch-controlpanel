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

#include <QObject>
#include <QGraphicsSceneMouseEvent>

#include <dcpappletpage.h>
#include <dcpwidget.h>
#include <dcpappletmetadata.h>
#include <dcpappletobject.h>

#include "ut_dcpappletpage.h"

void Ut_DcpAppletPage::init()
{
    DcpAppletMetadata *metadata = new DcpAppletMetadata("dummy-binary");
    DcpAppletObject *applet = new DcpAppletObject(metadata);
    m_subject = new DcpAppletPage(applet);
}

void Ut_DcpAppletPage::cleanup()
{
    delete m_subject;
    m_subject = 0;
}

void Ut_DcpAppletPage::initTestCase()
{
    QSKIP("incomplete", SkipSingle);   // remove this when you've finished
}

void Ut_DcpAppletPage::testCreateContents()
{
    QVERIFY(m_subject);
    QVERIFY(m_subject->isContentCreated());
}

void Ut_DcpAppletPage::testHasError()
{
    QVERIFY(!(m_subject->m_MissingLabel || m_subject->hasError()));
    m_subject->m_MissingLabel = (MLabel*)1; //not 0
    QVERIFY(m_subject->hasError());
}

void Ut_DcpAppletPage::testHasWidget()
{
    QVERIFY(!(m_subject->m_MainWidget || m_subject->hasWidget()));
    m_subject->m_MainWidget = new DcpWidget(); //not 0
    QVERIFY(m_subject->hasWidget());
}

void Ut_DcpAppletPage::testWidgetId()
{
    m_subject->m_WidgetId = 1;
    QCOMPARE(m_subject->widgetId(), 1);
    m_subject->m_WidgetId = 10;
    QCOMPARE(m_subject->widgetId(), 10);
}

void Ut_DcpAppletPage::testBack()
{
    QSKIP("incomplete", SkipSingle);   // remove this when you've finished
}

void Ut_DcpAppletPage::testLoad()
{
    QSKIP("incomplete", SkipSingle);   // remove this when you've finished
}

void Ut_DcpAppletPage::testLoadWidget()
{
    QSKIP("incomplete", SkipSingle);   // remove this when you've finished
}

void Ut_DcpAppletPage::testApplet()
{
    QVERIFY(m_subject->applet());
    QCOMPARE((void*)m_subject->applet(), (void*)m_subject->m_Applet);
}

void Ut_DcpAppletPage::cleanupTestCase()
{
}

QTEST_APPLESS_MAIN(Ut_DcpAppletPage)
