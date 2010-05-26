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

#include <dcpwidget.h>
#include "ft_dcpwidget.h"

void Ft_DcpWidget::init()
{
    m_subject = new DcpWidget();
}

void Ft_DcpWidget::cleanup()
{
    delete m_subject;
    m_subject = 0;
}

void Ft_DcpWidget::initTestCase()
{
}

void Ft_DcpWidget::cleanupTestCase()
{
}

void Ft_DcpWidget::testCreation()
{
    QVERIFY(m_subject);
}

void Ft_DcpWidget::testWidgetId()
{
    QCOMPARE(m_subject->getWidgetId(), -1);
    QVERIFY(m_subject->setWidgetId(1));
    QCOMPARE(m_subject->getWidgetId(), 1);
    QVERIFY(!m_subject->setWidgetId(10)); // already set
}

void Ft_DcpWidget::testBack()
{
    QVERIFY(m_subject->back()); // default behaviour
}

void Ft_DcpWidget::testPagePans()
{
    QVERIFY(m_subject->pagePans()); // default behaviour
}


QTEST_APPLESS_MAIN(Ft_DcpWidget)
