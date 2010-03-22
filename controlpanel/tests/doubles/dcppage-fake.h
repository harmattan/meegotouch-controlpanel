/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */

#include <QtDebug>

#include "dcppage.h"
#include "pages.h"

const PageHandle aHandle(PageHandle::MAIN);

DcpPage::DcpPage() 
{
}


void 
DcpPage::createContent()
{
}

void
DcpPage::createLayout ()
{
}

PageHandle 
DcpPage::handle () const 
{
    return aHandle;
}

void 
DcpPage::setHandle (
        const PageHandle &handle) 
{
    Q_UNUSED(handle);
}

/*!
 * \brief Sets the handle (symbolic representation) of the page.
 * Sets the handle for the page. The handle is a purely symbolic representation
 * of the page. The default value of the handle is PageHandle::NOPAGE.
 */
void 
DcpPage::setHandle (
        PageHandle::PageTypeId       id, 
        const QString               &param)
{
    Q_UNUSED(id);
    Q_UNUSED(param);
}

PageHandle 
DcpPage::referer () const 
{
    return aHandle;
}

void
DcpPage::setReferer (
        const PageHandle &referer) 
{
    Q_UNUSED(referer);
}

void 
DcpPage::setReferer (
        PageHandle::PageTypeId    id, 
        const QString            &param)
{
    Q_UNUSED(id);
    Q_UNUSED(param);
}

void 
DcpPage::back ()
{
}


void 
DcpPage::reload ()
{
}

QGraphicsLinearLayout *
DcpPage::mainLayout ()
{
    return 0;
}

