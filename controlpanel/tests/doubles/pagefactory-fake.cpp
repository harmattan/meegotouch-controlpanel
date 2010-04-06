/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */

#include "pagefactory.h"
#include "dcppage.h"

PageFactory *PageFactory::sm_Instance = 0;
static DcpPage* sCurrentPage = 0;

PageFactory::PageFactory ():
    QObject (),
    m_MainPage (0),
    m_AppletCategoryPage (0)
{
}

void
PageFactory::destroy()
{
}

void
PageFactory::mainPageFirstShown ()
{
}


PageFactory *
PageFactory::instance ()
{
    if (!sm_Instance)
        sm_Instance = new PageFactory();
    return sm_Instance;
}

DcpPage*
PageFactory::createPage (
        const PageHandle &)
{
    return 0;
}

DcpPage*
PageFactory::currentPage ()
{
    return sCurrentPage;
}

void
PageFactory::changePage (const PageHandle &handle)
{
    delete sCurrentPage;
    sCurrentPage = new DcpPage();
    sCurrentPage->setHandle (handle.id, handle.param);
}

void
PageFactory::pageChanged (DuiApplicationPage *)
{
}

void
PageFactory::appletWantsToStart (int)
{
}

