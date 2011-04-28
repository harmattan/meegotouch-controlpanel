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
#include <dcpcategories.h>
#include <dcpappletobject.h>
#include <dcpappletmetadata.h>
#include "dcpappletmanager.h"

#include <QObject>

#define CATEGORY DcpCategories::instance()->categoryById("fake-category")

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

    // an invalid page:
    page = factory->createPage(PageHandle(PageHandle::NOPAGE));
    QVERIFY(page); // TODO this should return NULL, shouldnt it?

    // an appletpage:
    page = factory->createPage(PageHandle(PageHandle::APPLET, "fake-name"));
    QVERIFY(page);

    // an appletpage with nonexistant applet:
    page = factory->createPage(PageHandle(PageHandle::APPLET, "xxx"));
    QVERIFY(page); // TODO this should return NULL, shouldnt it?

    // an applet category page:
    page = factory->createPage(PageHandle(PageHandle::APPLETCATEGORY, "ZERO"));
    QVERIFY(page);

    // an applet category page with nonexistant category:
    page = factory->createPage(PageHandle(PageHandle::APPLETCATEGORY, "xxx"));
    QVERIFY(!page);
}

void Ut_PageFactory::testCreateMainPage()
{
    PageFactory *factory = PageFactory::instance();

    DcpPage *page = factory->createMainPage();
    QVERIFY(page);
}

void Ut_PageFactory::testCreateAppletPage()
{
    PageFactory *factory = PageFactory::instance();
    PageHandle handle(PageHandle::APPLET, "fake-name");
    DcpPage *page =
        factory->createAppletPage(handle);
    QVERIFY(page);
}

void Ut_PageFactory::testCreateAppletCategoryPage()
{
    PageFactory *factory = PageFactory::instance();
    DcpPage *page = factory->createAppletCategoryPage(
            PageHandle(PageHandle::APPLETCATEGORY, "ZERO"));
    QVERIFY(page);
}


void Ut_PageFactory::testCurrentPage()
{
    PageFactory *factory = PageFactory::instance();
    QCOMPARE((void*)factory->currentPage(), (void*) 0);

    DcpPage* page = new DcpPage();;
    page->appear(factory->window());
    QCOMPARE((void*)factory->currentPage(), (void*)page);

    DcpPage* page2 = new DcpPage();;
    page2->appear(factory->window());
    QCOMPARE((void*)factory->currentPage(), (void*)page2);

    // cleanup
    page2->deleteLater();
    page->deleteLater();
}

void Ut_PageFactory::testChangePage()
{
    PageFactory *factory = PageFactory::instance();
    QCOMPARE(factory->currentPage(), (void*)0);

    factory->changePage (PageHandle(PageHandle::MAIN));
    QVERIFY((void*)factory->currentPage());

    factory->changePage (PageHandle(PageHandle::APPLETCATEGORY, "ZERO"));
    QVERIFY((void*)factory->currentPage());
}

void Ut_PageFactory::testAppletWantsToStart()
{
    PageFactory* factory = PageFactory::instance();

    DcpAppletManager::instance()->loadMetadata();

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
    QVERIFY(applet);
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

void Ut_PageFactory::testUseless()
{
    PageFactory* factory = PageFactory::instance();

    factory->preloadBriefReceiver();
    factory->completeCategoryPage();
    factory->createAppletCategoryPageIncomplete(CATEGORY);
    DcpAppletMetadata *metadata = new DcpAppletMetadata("dummy-binary");
    QVERIFY(factory->createAppletPage(metadata));
    factory->changeToAppletPage("haba");
    factory->preloadAppletLauncher();

    PageHandle pageH;
    factory->isCurrentPage(pageH);
//    factory->raiseMainWindow();
    factory->switchToMainPageWithPageDropping();
    factory->destroyPageHistory();
    factory->onMetadataLoaded();
    factory->setInProcessApplets(true);
    factory->onDisplayEntered();
//    factory->newWin();
    QEvent event(QEvent::None);
    factory->eventFilter(this, &event);
    factory->newMainPageInSeparateProcess();

}

QTEST_APPLESS_MAIN (Ut_PageFactory);

