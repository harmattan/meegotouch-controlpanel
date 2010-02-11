/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */

#include <QtDebug>

#include "dcppage.h"
#include <QGraphicsLinearLayout>
#include <DuiSceneManager>
#include <DuiApplication>
#include <DuiApplicationWindow>

#include "duiwidgetcreator.h"
DUI_REGISTER_WIDGET(DcpPage)

#define DEBUG
#include "dcpdebug.h"


DcpPage::DcpPage () :
    DuiApplicationPage ()
{
    DCP_DEBUG ("");
    setEscapeButtonMode (DuiEscapeButtonPanelModel::BackMode);
}


void 
DcpPage::createContent ()
{
    DuiApplicationPage::createContent ();
    setObjectName ("DcpPage");

    setEscapeButtonMode (DuiEscapeButtonPanelModel::BackMode);
    createLayout ();
}

void
DcpPage::createLayout ()
{
    new QGraphicsLinearLayout (Qt::Vertical, centralWidget());
}

void 
DcpPage::appendWidget (
        QGraphicsWidget *widget)
{
    Q_ASSERT (mainLayout());
    DCP_DEBUG ("*** adding   widget at %p", widget);
    /*
     * FIXME: Because we called the hide() in the removeWidget() method we have
     * to call the show() here.
     */
    mainLayout()->addItem (widget);
    widget->show ();
}

/*
 * FIXME: This function does nothing usefull... 
 */
void 
DcpPage::removeWidget (
        QGraphicsWidget *widget)
{
    DCP_DEBUG ("*** deleting widget at %p", widget);
#if 0
    /*
     * FIXME: The applet created the widget and we are destroying it. It is not
     * very good, some applets are sending back the same widget pointer, while
     * those are dead objects already. It is also a very rude thing to destroy
     * page 1 when the applet opens page 2, so I removed this from here.
     * 
     * FIXME: Do we have to solve the memory leak then or we just assume that
     * the applets are going to free all the memory they allocated?
     */
    //widget->deleteLater();
#else
    /*
     * FIXME: Apparently the removeItem will not work, i still can see the
     * widget. So we also call the hide() method.
     */
    mainLayout()->removeItem (widget);
    widget->hide();
#endif
}

void 
DcpPage::connectSignals ()
{
   connect (
           this, SIGNAL(backButtonClicked()), 
           this, SLOT(back()));
}

void 
DcpPage::disconnectSignals ()
{
    disconnect (
            this, SIGNAL(backButtonClicked()), 
            this, SLOT(back()));
}

/*!
 * Returns the handle of the page.
 */
PageHandle 
DcpPage::handle () const 
{
    return m_Handle;
}

/*!
 * \brief Sets the handle (symbolic representation) of the page.
 * Sets the handle for the page. The handle is a purely symbolic representation
 * of the page. The default value of the handle is PageHandle::NOPAGE.
 */
void 
DcpPage::setHandle (
        const PageHandle &handle) 
{
    m_Handle = handle;
    
    DCP_DEBUG ("*** m_Handle  = %s", DCP_STR (m_Handle.getStringVariant()));
    DCP_DEBUG ("*** m_Referer = %s", DCP_STR (m_Referer.getStringVariant()));
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
    m_Handle.id = id; 
    m_Handle.param = param;
    DCP_DEBUG ("*** m_Handle  = %s", DCP_STR (m_Handle.getStringVariant()));
    DCP_DEBUG ("*** m_Referer = %s", DCP_STR (m_Referer.getStringVariant()));
}

/*!
 * Returns the handle of the referer.
 */
PageHandle 
DcpPage::referer () const 
{
    return m_Referer;
}

/*!
 * \brief Sets the handle (symbolic representation) of the page referer.
 * Sets the handle of the referer (parent page) for the page. The handle is a 
 * purely symbolic representation of a page. The default value of the referer 
 * handle is PageHandle::NOPAGE.
 */
void 
DcpPage::setReferer (
        const PageHandle &referer) 
{
    m_Referer = referer;
    DCP_DEBUG ("*** m_Handle  = %s", DCP_STR (m_Handle.getStringVariant()));
    DCP_DEBUG ("*** m_Referer = %s", DCP_STR (m_Referer.getStringVariant()));
}

/*!
 * \brief Sets the handle (symbolic representation) of the page referer.
 * Sets the handle of the referer (parent page) for the page. The handle is a 
 * purely symbolic representation of a page. The default value of the referer 
 * handle is PageHandle::NOPAGE.
 */
void 
DcpPage::setReferer (
        PageHandle::PageTypeId    id, 
        const QString            &param)
{
    m_Referer.id = id; 
    m_Referer.param = param;
    DCP_DEBUG ("*** m_Handle  = %s", DCP_STR (m_Handle.getStringVariant()));
    DCP_DEBUG ("*** m_Referer = %s", DCP_STR (m_Referer.getStringVariant()));
}

/*!
 * A virtual function that is executed when the top right corner 'back' button
 * is clicked on a page. The default implementation will open the referer page
 * (that is will go back to the parent page).
 */
void 
DcpPage::back ()
{
    DCP_DEBUG ("*** m_Handle  = %s", DCP_STR (m_Handle.getStringVariant()));
    DCP_DEBUG ("*** m_Referer = %s", DCP_STR (m_Referer.getStringVariant()));
    emit openSubPage (referer());
}


/*! 
 * FIXME: Why this method is called reload?
 *
 * this is where pages optimize their open up times
 * default implementation sets the correct orientation 
 *
 * FIXME: Removed the function body, we don't use this any more, maybe it should
 * be deleted.
 */
void 
DcpPage::reload ()
{
}

QGraphicsLinearLayout *
DcpPage::mainLayout ()
{
    return (QGraphicsLinearLayout*)(centralWidget()->layout());
}

