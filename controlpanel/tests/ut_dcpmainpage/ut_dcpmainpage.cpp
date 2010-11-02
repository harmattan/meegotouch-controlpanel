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
#include <QtGlobal> 
#include <dcpmainpage.h>
#include "dcpcategorycomponent.h"
#include "dcpsinglecomponent.h"
#include <QSignalSpy>
#include <MContainer>
#include "ut_dcpmainpage.h"
#include <MLayout>
#include <QGraphicsLinearLayout>
void Ut_DcpMainPage::init()
{
    m_subject = new DcpMainPage();
}

void Ut_DcpMainPage::cleanup()
{
    delete m_subject;
    m_subject = 0;
}

void Ut_DcpMainPage::initTestCase()
{
}

void Ut_DcpMainPage::testCreation()
{
    QVERIFY(m_subject);

    QSignalSpy spy(m_subject, SIGNAL(appeared()));
    m_subject->createContent();
    m_subject->appear((MWindow*)0);
    QVERIFY(spy.count() == 1);

}

void Ut_DcpMainPage::testCreateContent()
{
    m_subject->createContent(); 
    QVERIFY(m_subject->isContentCreated());
    QVERIFY(m_subject->mainLayout());
    QVERIFY(m_subject->m_OtherComp);
    QCOMPARE((void*)(m_subject->m_OtherComp),
        (void*)((QGraphicsWidget*)(m_subject->mainLayout()->itemAt(0))));
    QGraphicsWidget *otherCategories = m_subject->m_OtherComp->centralWidget();
    QVERIFY(otherCategories);
#ifdef MOSTUSED
    QVERIFY(m_subject->m_RecentlyComp);
#endif
}


/*
void Ut_DcpMainPage::testReload()
{
    QSKIP("incomplete", SkipSingle);   // remove this when you've finished
}
*/
void Ut_DcpMainPage::testShown()
{
// case 1: No contents yet
    QSignalSpy spy(m_subject, SIGNAL(firstShown()));
//    QSignalSpy spyReloaded((QObject*)(m_subject->m_RecentlyComp), SIGNAL(reloaded()));
    m_subject->shown();
    QVERIFY(m_subject->m_HasContent);
    QCOMPARE(spy.count(), 1);
// case 2: there is content yet
    m_subject->m_WasHidden = true;
    m_subject->shown();
    QVERIFY(m_subject->m_WasHidden == false);
    QCOMPARE(spy.count(), 1); // not incrementing
//    QCOMPARE(spyReloaded.count(), 1);
// case 3: there is content and visible
    m_subject->m_WasHidden = false;
    m_subject->shown();
    QVERIFY(m_subject->m_WasHidden == false);
    QCOMPARE(spy.count(), 1); // not incrementing
//    QCOMPARE(spyReloaded.count(), 1);// not incrementing
}
/*
void Ut_DcpMainPage::testBack()
{
    m_subject->back();
    QSKIP("incomplete", SkipSingle);   // remove this when you've finished
}
*/
void Ut_DcpMainPage::testRetranslateUi()
{
    // first we need to create all the contents
    m_subject->createContent();
    m_subject->retranslateUi();
    QCOMPARE(m_subject->title(), qtTrId(QT_TRID_NOOP("qtn_sett_main_title")));
#ifdef MOSTUSED
    QCOMPARE(m_subject->m_RecentlyComp->title(),
             qtTrId(QT_TRID_NOOP("qtn_sett_main_most")));
#endif
//    QCOMPARE(m_subject->m_OtherComp->title(),
//             qtTrId(QT_TRID_NOOP("qtn_sett_main_other")));
/*    for (int i=0; i<m_subject->m_CategoryButtons.count(); i++) {
        DcpSingleComponent* comp = m_subject->m_CategoryButtons.at(i);
        QString title =qtTrId(QT_TRID_NOOP(i % 2 ? "qtn-fake" : "qtn-fake-2"));
        QCOMPARE(comp->title(), title);
    } */

}

void Ut_DcpMainPage::testHideEvent()
{
    m_subject->m_WasHidden = false;
    m_subject->hideEvent(0);
    QVERIFY(m_subject->m_WasHidden);
}

void Ut_DcpMainPage::cleanupTestCase()
{
}

QTEST_APPLESS_MAIN(Ut_DcpMainPage)
