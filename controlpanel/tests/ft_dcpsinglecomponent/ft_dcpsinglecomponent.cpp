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
#include <MApplication>

#include <dcpsinglecomponent.h>


#include "ft_dcpsinglecomponent.h"
#include "dcppage.h"
#include "pagefactory.h"
#include "memorycategory.h"

void Ft_DcpSingleComponent::init()
{
    Category* exampleCategory = new MemoryCategory ("title1", "title1Id", "mainPage",
                                                    "title2Id", "title2", "icon");
    m_subject =
        new DcpSingleComponent(0, exampleCategory);
    m_subject->setSubPage(PageHandle(PageHandle::APPLETCATEGORY, "Personalize"));
}

void Ft_DcpSingleComponent::cleanup()
{
    delete m_subject;
    m_subject = 0;
}

void Ft_DcpSingleComponent::initTestCase()
{
    static int c = 1;
    static char* appName = (char*)"ft_dcpsinglecomponent";

    new MApplication(c, &appName);
}

void Ft_DcpSingleComponent::cleanupTestCase()
{
}

void Ft_DcpSingleComponent::testCreation()
{
    QVERIFY(m_subject);
}

void Ft_DcpSingleComponent::testTitle()
{
    QCOMPARE(m_subject->title(), QString("!! title1"));
    m_subject->setTitle("another title");
    QCOMPARE(m_subject->title(), QString("another title"));
}

void Ft_DcpSingleComponent::testSubtitle()
{
    QCOMPARE(m_subject->subtitle(), QString("!! title2"));
    m_subject->setSubtitle("another subtitle");
    QCOMPARE(m_subject->subtitle(), QString("another subtitle"));
}

void Ft_DcpSingleComponent::testActivate()
{
    /*
    DcpPage *page = PageFactory::instance()->currentPage();
    QCOMPARE (page, (DcpPage*)0);
    m_subject->activate();
    page = PageFactory::instance()->currentPage();
    QCOMPARE(page->handle().id, PageHandle::APPLETCATEGORY);
    QCOMPARE(page->handle().param, QString("Personalize"));
     */
}


QTEST_APPLESS_MAIN(Ft_DcpSingleComponent)

