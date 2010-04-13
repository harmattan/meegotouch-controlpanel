#include <QtDebug>

#include "dcppage.h"
#include "pages.h"

const PageHandle aHandle(PageHandle::MAIN);

DcpPage::DcpPage() : MApplicationPage() 
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
    return m_Handle;
}

void 
DcpPage::setHandle (
        const PageHandle &handle) 
{
    m_Handle = handle;
}

void 
DcpPage::setHandle (
        PageHandle::PageTypeId       id, 
        const QString               &param)
{

    m_Handle.id = id;
    m_Handle.param = param;
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

