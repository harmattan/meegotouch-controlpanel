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

#include "dcpappletwidget.h"
#include <DcpWidget>
#include <DcpStylableWidget>
#include "ut_dcpappletwidget.h"

void Ut_DcpAppletWidget::init()
{
}

void Ut_DcpAppletWidget::cleanup()
{
}

void Ut_DcpAppletWidget::initTestCase()
{
}

void Ut_DcpAppletWidget::cleanupTestCase()
{
}

void Ut_DcpAppletWidget::testConstruct()
{
    DcpWidget fwidget;
    DcpAppletWidget *widget = new DcpAppletWidget(&fwidget);
    QVERIFY(widget);
    QVERIFY(!widget->m_Widget.isNull());
    QVERIFY(widget->m_StylableWidget.isNull());
    delete widget;
    widget = 0;

    DcpStylableWidget fswidget;
    widget = new DcpAppletWidget(&fswidget);
    QVERIFY(widget);
    QVERIFY(widget->m_Widget.isNull());
    QVERIFY(!widget->m_StylableWidget.isNull());
    delete widget;
    widget = 0;
}

void Ut_DcpAppletWidget::testSetReferer()
{
    DcpWidget fwidget;
    DcpAppletWidget *widget = new DcpAppletWidget(&fwidget);
    QVERIFY(widget);
    widget->setReferer(1);
    delete widget;

    DcpStylableWidget fswidget;
    widget = new DcpAppletWidget(&fswidget);
    QVERIFY(widget);
    widget->setReferer(1);
    delete widget;
}

void Ut_DcpAppletWidget::testBack()
{
    DcpWidget fwidget;
    DcpAppletWidget *widget = new DcpAppletWidget(&fwidget);
    QVERIFY(widget);
    QVERIFY(!widget->back());
    delete widget;

    DcpStylableWidget fswidget;
    widget = new DcpAppletWidget(&fswidget);
    QVERIFY(widget);
    QVERIFY(!widget->back());
    delete widget;
}

void Ut_DcpAppletWidget::testProperties()
{
    DcpWidget fwidget;
    DcpAppletWidget *widget = new DcpAppletWidget(&fwidget);
    QVERIFY(widget);

    QVERIFY(widget->getWidgetId() == 1);
    widget->setWidgetId(3);
    QVERIFY(widget->getWidgetId() == 3);

    QCOMPARE(widget->title(), QString());

    QCOMPARE(widget->isProgressIndicatorVisible(), true);
    widget->setProgressIndicatorVisible(false);
    QCOMPARE(widget->isProgressIndicatorVisible(), false);

    delete widget;

    DcpStylableWidget fswidget;
    widget = new DcpAppletWidget(&fswidget);
    QVERIFY(widget);

    QVERIFY(widget->getWidgetId() == 1);
    widget->setWidgetId(3);
    QVERIFY(widget->getWidgetId() == 3);

    QCOMPARE(widget->title(), QString());

    QCOMPARE(widget->isProgressIndicatorVisible(), true);
    widget->setProgressIndicatorVisible(false);
    QCOMPARE(widget->isProgressIndicatorVisible(), false);

    delete widget;
}
QTEST_APPLESS_MAIN(Ut_DcpAppletWidget)

