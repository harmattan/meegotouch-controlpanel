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
#include <QSignalSpy>

#include <dcpwidget.h>
#include <dcpwidget_p.h>


#include "ut_dcpwidget.h"

void Ut_DcpWidget::init()
{
    m_subject = new DcpWidget();
}

void Ut_DcpWidget::cleanup()
{
    delete m_subject;
    m_subject = 0;
}

void Ut_DcpWidget::initTestCase()
{
}

void Ut_DcpWidget::cleanupTestCase()
{
}

void Ut_DcpWidget::testCreation()
{
    QVERIFY(m_subject);
}

void Ut_DcpWidget::testWidgetId()
{
    QCOMPARE(m_subject->d_ptr->m_WidgetId, -1);
    QVERIFY(m_subject->setWidgetId(1));
    QCOMPARE(m_subject->d_ptr->m_WidgetId, 1);
    QCOMPARE(m_subject->getWidgetId(), 1);
    QVERIFY(!m_subject->setWidgetId(10)); // already set
}

void Ut_DcpWidget::testBack()
{
    QVERIFY(m_subject->back()); // default behaviour
}

void Ut_DcpWidget::testPagePans()
{
    QVERIFY(m_subject->pagePans()); // default behaviour
}

void Ut_DcpWidget::testProgressIndicator()
{
    // default value:
    QVERIFY(!m_subject->isProgressIndicatorVisible());

    QSignalSpy spy (m_subject, SIGNAL(inProgress(bool)));

    // show it:
    m_subject->setProgressIndicatorVisible(true);
    QVERIFY(m_subject->isProgressIndicatorVisible());
    QCOMPARE(spy.count(), 1);
    QVERIFY(spy.takeFirst().at(0).toBool());

    // hide it:
    m_subject->setProgressIndicatorVisible(false);
    QVERIFY(!m_subject->isProgressIndicatorVisible());
    QCOMPARE(spy.count(), 1);
    QVERIFY(!spy.takeFirst().at(0).toBool());
}

void Ut_DcpWidget::testUseless()
{
    m_subject->setReferer(0);
    QCOMPARE(m_subject->title(), QString());
}

QTEST_APPLESS_MAIN(Ut_DcpWidget)

