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

#include <dcpsinglecomponent.h>


#include "ft_dcpsinglecomponent.h"
#include "dcppage.h"
#include "pagefactory.h"

void Ft_DcpSingleComponent::init()
{
    m_subject = new DcpSingleComponent(0, "Logical ID", "title1", "title2");
    m_subject->setSubPage(PageHandle(PageHandle::LOOKANDFEEL, "Look & Feel"));
}

void Ft_DcpSingleComponent::cleanup()
{
    delete m_subject;
    m_subject = 0;
}

void Ft_DcpSingleComponent::initTestCase()
{
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
    QCOMPARE(m_subject->title(), QString("title1"));
    m_subject->setTitle("another title");
    QCOMPARE(m_subject->title(), QString("another title"));
}

void Ft_DcpSingleComponent::testSubtitle()
{
    QVERIFY(m_subject->subtitle() == "title2");
    m_subject->setSubtitle("another subtitle");
    QVERIFY(m_subject->subtitle() == "another subtitle");
}

void Ft_DcpSingleComponent::testActivate()
{
    DcpPage *page = PageFactory::instance()->currentPage();
    QVERIFY(page == 0);
    m_subject->activate();
    page = PageFactory::instance()->currentPage();
    QVERIFY(page->handle().id == PageHandle::LOOKANDFEEL);
    QVERIFY(page->handle().param == "Look & Feel");
}


QTEST_APPLESS_MAIN(Ft_DcpSingleComponent)
