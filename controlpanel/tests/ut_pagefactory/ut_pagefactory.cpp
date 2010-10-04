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

#include "ut_pagefactory.h"
#include <pagefactory.h>
#include "mapplicationwindow-fake.h"
#include "mapplication.h"
#include <dcppage.h>
#include <dcpappletpage.h>
#include <dcpappletobject.h>

#include <QObject>


void Ut_PageFactory::init()
{
}

void Ut_PageFactory::cleanup()
{
    PageFactory::destroy();

    // this is to make tests start with clean look like app (and fake appwindow
    // does not support tracking the currentwindow on back
    MApplication::activeApplicationWindow()->setCurrentPage(0);
}

void Ut_PageFactory::initTestCase()
{
}

void Ut_PageFactory::cleanupTestCase()
{
}

void Ut_PageFactory::testInstance()
{
    QVERIFY(!PageFactory::sm_Instance);
    PageFactory *factory = PageFactory::instance();
    QVERIFY(factory);
    QVERIFY(factory == PageFactory::sm_Instance);
    QVERIFY(factory == PageFactory::instance());
}

void Ut_PageFactory::testCreatePage()
{
    PageFactory *factory = PageFactory::instance();
    DcpPage *page;

    // a mainpage:
    page = factory->createPage(PageHandle(PageHandle::MAIN));
    QVERIFY(page);
    QCOMPARE((void*)factory->m_MainPage, (void*)page);

    // an invalid page:
    page = factory->createPage(PageHandle(PageHandle::NOPAGE));
    QVERIFY(page);
    QCOMPARE((void*)factory->m_MainPage, (void*)page);

    // an appletpage:
    page = factory->createPage(PageHandle(PageHandle::APPLET, "fake-name"));
    QVERIFY(page);

    // an appletpage with nonexistant applet:
    page = factory->createPage(PageHandle(PageHandle::APPLET, "xxx"));
    QVERIFY(page);

    // applet category pages:
    for (int i = PageHandle::CATEGORY_PAGEID_START+1;
             i < PageHandle::CATEGORY_PAGEID_END; i++)
    {
        page = factory->createPage(PageHandle((PageHandle::PageTypeId)i));
        QVERIFY(page);
        QCOMPARE((void*)factory->m_AppletCategoryPage, (void*) page);
    }
}

void Ut_PageFactory::testCreateMainPage()
{
    PageFactory *factory = PageFactory::instance();

    QVERIFY(factory->m_MainPage == 0);

    DcpPage *page = factory->createMainPage();
    QVERIFY(page);
    QCOMPARE((void*)factory->m_MainPage, (void*) page);

    // Second call should just return existing m_MainPage
    void* lastPage = (void*)factory->m_MainPage;
    QCOMPARE(lastPage, (void*) factory->createMainPage());
}

void Ut_PageFactory::testCreateAppletPage()
{
    PageFactory *factory = PageFactory::instance();
    QCOMPARE((void*)factory->m_MainPage, (void*)0);
    PageHandle handle(PageHandle::APPLET, "fake-name");
    DcpPage *page =
        factory->createAppletPage(handle);
    QVERIFY(page);
}

void Ut_PageFactory::testCreateAppletCategoryPage()
{
    PageFactory *factory = PageFactory::instance();
    QVERIFY(factory->m_AppletCategoryPage == 0);
    DcpPage *page = factory->createAppletCategoryPage(PageHandle::LOOKANDFEEL);
    QVERIFY(page);
    QCOMPARE((void*)factory->m_AppletCategoryPage, (void*) page);

    // Second call should just return the existing m_AppletCategoryPage
    void* lastPage = factory->m_AppletCategoryPage;
    QCOMPARE(lastPage,
            (void*) factory->createAppletCategoryPage(PageHandle::LOOKANDFEEL));

    // Ensures that no second categorypage gets created, but the existing one
    // is used again:
    QCOMPARE(lastPage,
             (void*)factory->createAppletCategoryPage(PageHandle::DEVICESYSTEM));
}


void Ut_PageFactory::testCurrentPage()
{
    PageFactory *factory = PageFactory::instance();
    QCOMPARE((void*)factory->currentPage(), (void*) 0);

    DcpPage* page = new DcpPage();;
    page->appear();
    QCOMPARE((void*)factory->currentPage(), (void*)page);

    DcpPage* page2 = new DcpPage();;
    page2->appear();
    QCOMPARE((void*)factory->currentPage(), (void*)page2);

    // cleanup
    page2->deleteLater();
    page->deleteLater();
}

void Ut_PageFactory::testChangePage()
{
    // for testing that the window was raised on page switch:
    MApplication::activeApplicationWindow()->lower();
    QCOMPARE (MApplication::activeApplicationWindow()->isRaised(), false);

    PageFactory *factory = PageFactory::instance();
    QCOMPARE(factory->currentPage(), (void*)0);

    factory->changePage (PageHandle(PageHandle::MAIN));
    QCOMPARE((void*)factory->currentPage(), (void*)factory->m_MainPage);
    //QCOMPARE (MApplication::activeApplicationWindow()->isRaised(), true);

    factory->changePage (PageHandle(PageHandle::DEVICESYSTEM));
    QCOMPARE((void*)factory->currentPage(), (void*)factory->m_AppletCategoryPage);
}

void Ut_PageFactory::testAppletWantsToStart()
{
    // FIXME: current implementation requires that the mainpagefirstshown gets
    // called, so it is not working when popping up directly an applet page
    PageFactory *factory = PageFactory::instance();
    factory->mainPageFirstShown();

    // switch to an appletpage
    PageHandle handle(PageHandle::APPLET, "fake-name");
    factory->changePage (handle);
    DcpAppletPage* page = qobject_cast<DcpAppletPage*>(factory->currentPage());
    QVERIFY (page);

    /*
     * call appletWantsToStart through the applet
     *
     * (it is a precondition of the function that it is only called from
     * an appletobject)
     */
    DcpAppletObject* applet = page->applet();
    factory->onAppletLoaded (applet); // this is necessery because the fake db
                                      // does not emit a signal for us
    applet->activateSlot(1);
    page = qobject_cast<DcpAppletPage*>(factory->currentPage());
    QVERIFY (page);
    QCOMPARE (page->widgetId(), 1);

    applet = page->applet();
    applet->activateSlot(2);
    page = qobject_cast<DcpAppletPage*>(factory->currentPage());
    QVERIFY (page);
    QCOMPARE (page->widgetId(), 2);
}

void Ut_PageFactory::testMainPageFirstShown()
{
    QSKIP("incomplete", SkipSingle);
}

void Ut_PageFactory::testRegisterPage()
{
    QSKIP("incomplete", SkipSingle);
}

QTEST_APPLESS_MAIN (Ut_PageFactory);

