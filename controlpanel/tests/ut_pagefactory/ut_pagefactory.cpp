#include "ut_pagefactory.h"
#include <pagefactory.h>
#include "duiapplicationwindow-fake.h"
#include "duiapplication.h"
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
    DuiApplication::activeApplicationWindow()->setCurrentPage(0);
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
    page = factory->createPage(PageHandle(PageHandle::APPLET, "anApplet"));
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
    PageHandle handle(PageHandle::APPLET, "anApplet");
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
    DuiApplication::activeApplicationWindow()->lower();
    QCOMPARE (DuiApplication::activeApplicationWindow()->isRaised(), false);

    PageFactory *factory = PageFactory::instance();
    QCOMPARE(factory->currentPage(), (void*)0);

    factory->changePage (PageHandle(PageHandle::MAIN));
    QCOMPARE((void*)factory->currentPage(), (void*)factory->m_MainPage);
    QCOMPARE (DuiApplication::activeApplicationWindow()->isRaised(), true);

    factory->changePage (PageHandle(PageHandle::DEVICESYSTEM));
    QCOMPARE((void*)factory->currentPage(), (void*)factory->m_AppletCategoryPage);
}

void Ut_PageFactory::testAppletWantsToStart()
{
    // switch to an appletpage
    PageFactory *factory = PageFactory::instance();
    PageHandle handle(PageHandle::APPLET, "anApplet");
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

