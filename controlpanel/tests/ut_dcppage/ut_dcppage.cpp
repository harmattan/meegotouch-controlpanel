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
#include <QCoreApplication>
#include <dcppage.h>

#include "ut_dcppage.h"
#include "mlabel-fake.h"
#include <QGraphicsLinearLayout>

void Ut_DcpPage::init()
{
    m_subject = new DcpPage();
}

void Ut_DcpPage::cleanup()
{
    m_subject->deleteLater();
    m_subject = 0;
}

void Ut_DcpPage::initTestCase()
{
}


void Ut_DcpPage::cleanupTestCase()
{
}

void Ut_DcpPage::testCreateContents()
{
    m_subject->createContent();
    QVERIFY(m_subject->isContentCreated());
}

void Ut_DcpPage::testHandle()
{
    PageHandle handle(PageHandle::MAIN, "param", 1, true);
    m_subject->setHandle(handle); 
    PageHandle result = m_subject->handle();
    QVERIFY(result.id == PageHandle::MAIN);
    QVERIFY(result.param == "param");
    QVERIFY(result.widgetId == 1);
    QVERIFY(result.isStandalone == true);
    
    m_subject->setHandle(PageHandle::APPLET, "test"); 
    PageHandle result1 = m_subject->handle();
    QVERIFY(result1.id == PageHandle::APPLET);
    QVERIFY(result1.param == "test");
    QVERIFY(result1.widgetId == -1);
    QVERIFY(result1.isStandalone == false);

}
void Ut_DcpPage::testReferer()
{
    PageHandle handle(PageHandle::MAIN, "param", 1, true);
    m_subject->setReferer(handle); 
    PageHandle result = m_subject->referer();
    QVERIFY(result.id == PageHandle::MAIN);
    QVERIFY(result.param == "param");
    QVERIFY(result.widgetId == 1);
    QVERIFY(result.isStandalone == true);
    
    m_subject->setReferer(PageHandle::APPLET, "test"); 
    PageHandle result1 = m_subject->referer();
    QVERIFY(result1.id == PageHandle::APPLET);
    QVERIFY(result1.param == "test");
    QVERIFY(result1.widgetId == -1);
    QVERIFY(result1.isStandalone == false);

}
void Ut_DcpPage::testMainLayout()
{
    QVERIFY(m_subject->mainLayout() == 
        (QGraphicsLinearLayout*)(m_subject->centralWidget()->layout()));
}
void Ut_DcpPage::testAppendWidget()
{
    MLabel *label1 = new MLabel();
    m_subject->appendWidget(label1);
    QCOMPARE(m_subject->mainLayout()->itemAt(0), (QGraphicsLayoutItem*)label1);
}

void Ut_DcpPage::testSetTitleLabel()
{
    m_subject->setTitle("habala");
    m_subject->setTitleLabel("ize");
    m_subject->setTitle("");
    m_subject->setTitleLabel("ize2");
}

QTEST_APPLESS_MAIN(Ut_DcpPage)

