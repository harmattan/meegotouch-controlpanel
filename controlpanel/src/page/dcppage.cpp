/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */

#include <QtDebug>

#include "dcppage.h"
#include <QGraphicsLinearLayout>
#include <DuiSceneManager>
#include <DuiApplication>
#include <DuiApplicationWindow>

//#define DEBUG
#include "dcpdebug.h"


DcpPage::DcpPage() :
    DuiApplicationPage()
{
    setEscapeButtonMode (DuiEscapeButtonPanelModel::BackMode);
}

DcpPage::~DcpPage()
{
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
DcpPage::organizeContent (
        const Dui::Orientation &ori)
{
    Q_UNUSED (ori);
}

void 
DcpPage::append (
        QGraphicsWidget *widget)
{
    Q_ASSERT (mainLayout());
    mainLayout()->addItem (widget);
}

void 
DcpPage::remove (
        QGraphicsWidget *widget)
{
    widget->deleteLater();
}

void 
DcpPage::connectSignals ()
{
   connect (
           this, SIGNAL(backButtonClicked()), 
           this, SLOT(back()));
   connectOrientation ();
}

void 
DcpPage::connectOrientation ()
{
   DuiSceneManager* manager;
   
   manager = DuiApplication::activeApplicationWindow()->sceneManager();
   if (manager) {
       // handle orientation change:
       connect (
               manager, SIGNAL(orientationChanged (Dui::Orientation)),
               this, SLOT(organizeContent(Dui::Orientation)));
   } else {
       qWarning("orientation connect fails");
   }
}

void 
DcpPage::disconnectSignals()
{
    DuiSceneManager *manager = sceneManager ();

    if (manager) {
        disconnect (
                manager, SIGNAL (orientationChanged (Dui::Orientation)),
                this, SLOT (organizeContent(Dui::Orientation)));
    }

    disconnect (this, SIGNAL(backButtonClicked()), this, SLOT(back()));
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


/* this is where pages optimize their open up times
 * default implementation sets the correct orientation */
void 
DcpPage::reload()
{
    if (sceneManager()) {
        organizeContent(sceneManager()->orientation());
    }
}

QGraphicsLinearLayout *
DcpPage::mainLayout ()
{
    return (QGraphicsLinearLayout*)(centralWidget()->layout());
}

