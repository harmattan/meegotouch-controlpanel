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

/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */

#include <QtDebug>

#include "dcppage.h"
#include <QGraphicsLinearLayout>
#include <MSceneManager>
#include <MApplication>
#include <MApplicationWindow>
#include <MLabel>
#include <MSeparator>
#include <MStylableWidget>

#include "mwidgetcreator.h"
M_REGISTER_WIDGET(DcpPage)

#include "dcpdebug.h"


DcpPage::DcpPage () :
    MApplicationPage (),
    m_TitleLabel (0)
{
    DCP_DEBUG ("");
    setStyleName ("DcpPage");

    // back button handling:
    connect (this, SIGNAL(backButtonClicked()),
             this, SLOT(back()));
}


void 
DcpPage::createContent ()
{
    MApplicationPage::createContent ();

    createLayout ();
}

void
DcpPage::createLayout ()
{
    QGraphicsLinearLayout* layout =
        new QGraphicsLinearLayout (Qt::Vertical, centralWidget());

    // we should not have margins around the mainwidget
    layout->setContentsMargins (0,0,0,0);
}

void 
DcpPage::appendWidget (
        QGraphicsWidget *widget)
{
    dcp_failfunc_unless (mainLayout());
    DCP_DEBUG ("*** adding   widget at %p", widget);
    /*
     * FIXME: Because we called the hide() in the removeWidget() method we have
     * to call the show() here.
     */
    mainLayout()->addItem (widget);
    widget->show ();
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
    m_Handle.widgetId = -1;
    m_Handle.isStandalone=false;

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
    m_Referer.widgetId = -1;
    m_Referer.isStandalone=false;
    DCP_DEBUG ("*** m_Handle  = %s", DCP_STR (m_Handle.getStringVariant()));
    DCP_DEBUG ("*** m_Referer = %s", DCP_STR (m_Referer.getStringVariant()));
}

/*!
 * A virtual function that is executed when the top right corner 'back' button
 * is clicked on a page. The default implementation will call dismiss,
 * so back will be handled by libdui.
 */
void 
DcpPage::back ()
{
    dismiss();
}


/*! 
 * This is called automatically for cached pages to reload their content when
 * they are openned again.
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

/*!
 * sets the title label to the title of the page
 * If there is no title label yet, it creates it.
 */
void
DcpPage::setTitleLabel ()
{
    if (! mainLayout()) return;

    if (title().isEmpty()) {
        if (m_TitleLabel) {
            QGraphicsLayoutItem* title = mainLayout()->itemAt(0);
            QGraphicsLayoutItem* separator = mainLayout()->itemAt(1);
            delete title;
            delete separator;
            m_TitleLabel = 0;
        }
        return;
    }

    if (!m_TitleLabel) {
        MStylableWidget* container = new MStylableWidget();
        container->setStyleName ("CommonXLargeHeaderPanelInverted");
        container->setSizePolicy (QSizePolicy::Expanding, QSizePolicy::Fixed);
        QGraphicsLinearLayout* layout = new QGraphicsLinearLayout(container);
        layout->setContentsMargins (0,0,0,0);
        m_TitleLabel = new MLabel(container);
        m_TitleLabel->setStyleName ("CommonApplicationHeaderInverted");
        layout->addItem (m_TitleLabel);
        container->setLayout (layout);
        mainLayout()->insertItem (0, container);

        MSeparator* separator = new MSeparator();
        separator->setStyleName ("CommonSmallSpacer");
        mainLayout()->insertItem (1, separator);
    }
    m_TitleLabel->setText (title ());
}

