#include <QObject>

#include <pagefactory.h>

#include "ut_pagefactory.h"


void Ut_PageFactory::init()
{
}

void Ut_PageFactory::cleanup()
{
    PageFactory::destroy();
}

void Ut_PageFactory::initTestCase()
{
    /*
    static int argc = 1;
    static char *app_name[1] = { (char *) "./ut_duiapplicationpage" };
    app = new DuiApplication(argc, app_name);
    appWin = new DuiApplicationWindow;

    qRegisterMetaType<DuiApplicationPage *>();
    qRegisterMetaType<DuiEscapeButtonPanelModel::EscapeMode>();
    */
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
    /*
    PageFactory *factory = PageFactory::instance();
    DcpPage *page;
    
    page = factory->createPage(PageHandle(PageHandle::MAIN));    
    QVERIFY(page);    
    QVERIFY(factory->m_MainPage == page);    
    page = factory->createPage(PageHandle(PageHandle::NOPAGE));    
    QVERIFY(page);    
    QVERIFY(factory->m_MainPage == page);    
    page = factory->createPage(PageHandle(PageHandle::APPLET, "anApplet"));    
    QVERIFY(page);    
    page = factory->createPage(PageHandle(PageHandle::APPLETCATEGORY, "category"));    
    QVERIFY(page);    
    QVERIFY(factory->m_AppletCategoryPage == page);    
    */
}

void Ut_PageFactory::testCreateMainPage()
{
    /*
    QSKIP("incomplete", SkipSingle);
    PageFactory *factory = PageFactory::instance();

    QVERIFY(factory->m_MainPage == 0);    
    
    DcpPage *page = factory->createMainPage();    
    QVERIFY(page);    
     QVERIFY(factory->m_MainPage == page);    
    // Second call should just return existing m_MainPage
    QVERIFY(factory->m_MainPage == factory->createMainPage());    
    */
}

void Ut_PageFactory::testCreateAppletPage()
{
    QSKIP("incomplete", SkipSingle);
    /*
    PageFactory *factory = PageFactory::instance();
    QSKIP("incomplete", SkipSingle);
    QVERIFY(factory->m_MainPage == 0);    
    DcpPage *page = factory->createAppletPage(PageHandle(PageHandle::APPLET, "anApplet"));    
    QVERIFY(page);  
    */  
}

void Ut_PageFactory::testCreateAppletCategoryPage()
{
    QSKIP("incomplete", SkipSingle);
/*
    PageFactory *factory = PageFactory::instance();
    QVERIFY(factory->m_AppletCategoryPage == 0);    
    DcpPage *page = factory->createAppletCategoryPage(PageHandle::LOOKANDFEEL);    
    QVERIFY(page);    
    QVERIFY(factory->m_AppletCategoryPage == page);    
    // Second call should just return existing m_AppletCategoryPage
    QVERIFY(factory->m_AppletCategoryPage == factory->createAppletCategoryPage(PageHandle::LOOKANDFEEL));    
    // Strange, but expected 
    QVERIFY(factory->m_AppletCategoryPage == factory->createAppletCategoryPage(PageHandle::SOUND));    
*/
}


void Ut_PageFactory::testCurrentPage()
{
    QSKIP("incomplete", SkipSingle);
    //PageFactory *factory = PageFactory::instance();
    //QVERIFY(factory->currentPage() == 0);
}

void Ut_PageFactory::testChangePage()
{
    QSKIP("incomplete", SkipSingle);
}


void Ut_PageFactory::testAppletWantsToStart()
{
    QSKIP("incomplete", SkipSingle);
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

