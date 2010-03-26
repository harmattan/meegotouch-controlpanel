#include <QObject>

#include <pagefactory.h>

#include "ft_pagefactory.h"

#include "duigconfitem-fake.h"
#include "duidesktopentry-stub.h"
#include "dcpappletobject-fake.h"
#include "dcpappletdb-fake.h"
#include "dcppage-fake.h"
#include "dcpmainpage-fake.h"
#include "dcpcategorypage-fake.h"
#include "dcpappletcategorypage-fake.h"
#include "dcpappletpage-fake.h"
#include "appleterrorsdialog-fake.h"
#include "maintranslations-fake.h"
#include "duiwindow-fake.h" 
#include "duiapplication_stub.h"
#include "duitheme_stub.h"

void Ft_PageFactory::init()
{
}

void Ft_PageFactory::cleanup()
{
    PageFactory::destroy();
}

void Ft_PageFactory::initTestCase()
{
    static int argc = 1;                                                                                                   
    static char *argv = (char*) "./ft_pagefactory";                                                                     
    app = new DuiApplication(argc, &argv);
                                                                                                                  
}

void Ft_PageFactory::cleanupTestCase()
{
    delete app;
}

void Ft_PageFactory::testInstance()
{
    PageFactory *factory = PageFactory::instance();
    QVERIFY(factory);
    QVERIFY(factory == PageFactory::instance());
    PageFactory *factory1 = PageFactory::instance();
    QVERIFY(factory == factory1);
}

void Ft_PageFactory::testCreatePage()
{
    PageFactory *factory = PageFactory::instance();
    DcpPage *page;
    
    page = factory->createPage(PageHandle(PageHandle::MAIN));    
    QVERIFY(page);    
    QVERIFY(page->handle().id == PageHandle::MAIN);    
    
    page = factory->createPage(PageHandle(PageHandle::NOPAGE));    
    QVERIFY(page);    
    QVERIFY(page->handle().id == PageHandle::NOPAGE);    
    
    page = factory->createPage(PageHandle(PageHandle::APPLET, "anApplet"));    
    QVERIFY(page);    
    QVERIFY(page->handle().id == PageHandle::APPLET);    
    
    page = factory->createPage(PageHandle(PageHandle::APPLETCATEGORY, "category"));    
    QVERIFY(page);    
    QVERIFY(page->handle().id == PageHandle::APPLETCATEGORY);    
}


void Ft_PageFactory::testCurrentPage()
{
    PageFactory *factory = PageFactory::instance();
    QVERIFY(factory->currentPage() == 0);
}

void Ft_PageFactory::testChangePage()
{
    PageFactory *factory = PageFactory::instance();
    PageHandle handle = PageHandle(PageHandle::APPLET, "anApplet");    
    factory->changePage(handle);
    DcpPage *page = factory->currentPage();
    QVERIFY(page);
    QVERIFY(page->handle() == handle);
}


void Ft_PageFactory::testAppletWantsToStart()
{
    QSKIP("incomplete", SkipSingle);
}


QTEST_MAIN(Ft_PageFactory)
