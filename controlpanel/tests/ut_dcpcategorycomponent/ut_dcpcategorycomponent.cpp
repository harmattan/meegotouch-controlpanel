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

#include <dcpcategorycomponent.h>


#include "ut_dcpcategorycomponent.h"
#include "maintranslations.h"
#include <dcpappletbuttons.h>
#include <MContainer>

void Ut_DcpCategoryComponent::init()
{
    m_subject = new DcpCategoryComponent(0, &DcpMain::CategoryInfos[0], 0);
}

void Ut_DcpCategoryComponent::cleanup()
{
    delete m_subject;
    m_subject = 0;
}

void Ut_DcpCategoryComponent::initTestCase()
{
}

void Ut_DcpCategoryComponent::cleanupTestCase()
{
}

void Ut_DcpCategoryComponent::testCreation()
{
    QCOMPARE(m_subject->m_CategoryInfo, &DcpMain::CategoryInfos[0]);
    QCOMPARE(m_subject->TDriverID(), QString("DcpCategoryComponent::") + DcpMain::CategoryInfos[0].titleId);
}

void Ut_DcpCategoryComponent::testCreateContents()
{
    QVERIFY(m_subject->m_AppletButtons);
    QCOMPARE(m_subject->m_AppletButtons->title(), m_subject->title());
    QCOMPARE(m_subject->m_Container->centralWidget(), 
        (QGraphicsLayoutItem*)(m_subject->m_AppletButtons));
}

void Ut_DcpCategoryComponent::testRetranslateUi()
{
    m_subject->retranslateUi();
    QCOMPARE(m_subject->title(), qtTrId("qtn-fake")); 
    m_subject->m_CategoryInfo = 0;
    m_subject->retranslateUi();
    QCOMPARE(m_subject->title(), 
        qtTrId(m_subject->m_LogicalId.toLatin1().constData())); 
    
}

void Ut_DcpCategoryComponent::testTitle()
{
    m_subject->setTitle("abcd");
    QCOMPARE(m_subject->title(), QString("abcd"));
    QCOMPARE(m_subject->m_Container->title(), QString("abcd"));
}

void Ut_DcpCategoryComponent::testReload()
{
    QVERIFY(m_subject->reload());
}

void Ut_DcpCategoryComponent::testGetItemCount()
{
    QCOMPARE(m_subject->getItemCount(), m_subject->m_AppletButtons->getItemCount());
    delete m_subject->m_AppletButtons;
    m_subject->m_AppletButtons = 0;
    QCOMPARE(m_subject->getItemCount(), 0);
}
QTEST_APPLESS_MAIN(Ut_DcpCategoryComponent)
