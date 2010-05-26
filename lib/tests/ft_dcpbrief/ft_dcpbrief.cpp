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

#include <dcpbrief.h>


#include "ft_dcpbrief.h"
#include "dcpwidgettypes.h"

void Ft_DcpBrief::init()
{
    m_subject = new DcpBrief();
}

void Ft_DcpBrief::cleanup()
{
    delete m_subject;
    m_subject = 0;
}

void Ft_DcpBrief::initTestCase()
{
}

void Ft_DcpBrief::cleanupTestCase()
{
}

void Ft_DcpBrief::testCreation()
{
    QVERIFY(m_subject);
}

void Ft_DcpBrief::testWidgetTypeID()
{
    QVERIFY(m_subject->widgetTypeID() == DcpWidgetType::BriefInvalid);
}

void Ft_DcpBrief::testValueText()
{
    QCOMPARE(m_subject->valueText(), QString());
}

void Ft_DcpBrief::testIcon()
{
    QCOMPARE(m_subject->icon(), QString());
}

void Ft_DcpBrief::testToggleIconId()
{
    QCOMPARE(m_subject->toggleIconId(), QString());
}

void Ft_DcpBrief::testAlign()
{
    QCOMPARE(m_subject->align(), Qt::AlignLeft);
}

void Ft_DcpBrief::testToggle()
{
    QVERIFY(!m_subject->toggle());
}

void Ft_DcpBrief::testImage()
{
    QCOMPARE(m_subject->image(), QString());
}

void Ft_DcpBrief::testActivate()
{
    QSignalSpy spy(m_subject, SIGNAL(activateSignal()));
    QCOMPARE(spy.count(), 0);
    m_subject->activate();
    QCOMPARE(spy.count(), 1);
    m_subject->activate();
    QCOMPARE(spy.count(), 2);

}

void Ft_DcpBrief::testTitleText()
{
    QCOMPARE(m_subject->titleText(), QString());
}


QTEST_APPLESS_MAIN(Ft_DcpBrief)
