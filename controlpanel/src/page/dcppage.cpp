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
#include <MLabel>
#include <MHelpButton>
#include <MSeparator>
#include <MStylableWidget>
#include <MPannableViewport>
#include <MPositionIndicator>
#include <MWidgetAction>
#include <MDismissEvent>

#include "mwidgetcreator.h"
M_REGISTER_WIDGET(DcpPage)

#include "dcpdebug.h"


DcpPage::DcpPage () :
    MApplicationPage (),
    m_TitleLabel (0),
    m_HelpButton (0),
    m_ActionHack (0),
    m_PreventQuit (false)
{
    setStyleName("CommonApplicationPageInverted");
    dcp_failfunc_unless (pannableViewport());
    dcp_failfunc_unless (pannableViewport()->positionIndicator());
    pannableViewport()->positionIndicator()->setStyleName(
            "CommonPositionIndicatorInverted");
}

DcpPage::~DcpPage ()
{
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
    layout->setSpacing (0);
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

MAction*
DcpPage::createSpacerAction()
{
    MWidgetAction* result = new MWidgetAction (this);
    MWidget* spacer = new MWidget ();
    spacer->setSizePolicy (QSizePolicy::Expanding, QSizePolicy::Expanding);
    result->setLocation (MAction::ToolBarLocation);
    result->setWidget (spacer);
    result->setEnabled (false);
    return result;
}

void
DcpPage::addMAction (MAction* action)
{
    if (m_ActionHack && (action->location() & MAction::ToolBarLocation)) {
        // insert between the two spacers so that they can remain centered:
        removeAction (m_ActionHack);
        delete m_ActionHack;
    }
    addAction (action);
}

/*!
 * This function returns if the page would like to prevent its closing,
 * when the user presses the close or back button.
 */
bool
DcpPage::preventQuit ()
{
    return m_PreventQuit;
}

// This function might prevent closing the window for the applet
// in a normal back button pressed situation (when not the last page)
void
DcpPage::dismissEvent (MDismissEvent *event)
{
    if (preventQuit ()) {
        event->ignore();
        return;
    }
    MApplicationPage::dismissEvent (event);
}

/*!
 * \brief Sets the handle (symbolic representation) of the page.
 * Sets the handle for the page. The handle is a purely symbolic representation
 * of the page. The default value of the handle is PageHandle::NOPAGE.
 */
void
DcpPage::setHandle (const PageHandle &handle)
{
    m_Handle = handle;

    DCP_DEBUG ("*** m_Handle  = %s", DCP_STR (m_Handle.getStringVariant()));
    DCP_DEBUG ("*** m_Referer = %s", DCP_STR (m_Referer.getStringVariant()));

    /* A button for moving back to mainpage:
     */
    if (handle.isStandalone && !m_ActionHack)  {
        // this hack hides the back button:
        setComponentsDisplayMode (MApplicationPage::EscapeButton, MApplicationPageModel::Hide);

        MAction* mainBack = new MAction (this);
        mainBack->setLocation (MAction::ToolBarLocation);
        mainBack->setIconID ("icon-l-settings-main-view");
        QAction* firstAction = actions().isEmpty() ? 0 : actions().first();
        insertAction (firstAction, mainBack);

        // this hack action makes the mainBack align to the left, and the
        // other spacers align centered
        m_ActionHack = createSpacerAction ();
        insertAction (firstAction, m_ActionHack);

        connect(mainBack, SIGNAL(triggered()),
                this, SIGNAL (mainPageIconClicked()));
    }
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
DcpPage::setTitleLabel (const QString& helpId)
{
#ifndef MEEGO
    if (! mainLayout()) return;

    if (title().isEmpty()) {
        if (m_TitleLabel) {
            QGraphicsLayoutItem* title = mainLayout()->itemAt(0);
            QGraphicsLayoutItem* separator = mainLayout()->itemAt(1);
            delete title; // this deletes the helpbutton (if any) & title
            delete separator;
            m_TitleLabel = 0;
            m_HelpButton = 0;
        }
        return;
    }

    if (!m_TitleLabel) {
        m_TitleLabel = new MLabel();
        m_TitleLabel->setAlignment (Qt::AlignLeft | Qt::AlignAbsolute);
        m_TitleLabel->setWordWrap(true);
        m_TitleLabel->setStyleName ("CommonHeaderInverted");
        if (!helpId.isEmpty()) {
            // this can be here, because the help button does not need
            // retranslation. But it also meens that recalling the setTitleLabel
            // will not refresh the help id (currently not used)
            m_HelpButton = new MHelpButton (helpId);
            m_HelpButton->setViewType(MButton::iconType);
            m_HelpButton->setIconID ("icon-s-description-inverse");
            m_HelpButton->setStyleName ("CommonRightIcon");
            QGraphicsLinearLayout* labelLayout = new QGraphicsLinearLayout();
            labelLayout->setSpacing(0);
            labelLayout->setContentsMargins(0, 0, 0, 0);
            labelLayout->addItem (m_TitleLabel);
            labelLayout->addItem (m_HelpButton);
            labelLayout->setAlignment (m_HelpButton, Qt::AlignVCenter);
            m_TitleLabel->setSizePolicy (QSizePolicy::Expanding,
                                         QSizePolicy::Fixed);
            mainLayout()->insertItem (0, labelLayout);
        } else {
            mainLayout()->insertItem (0, m_TitleLabel);
        }
        MSeparator* divider = new MSeparator();
        divider->setStyleName ("CommonHeaderDividerInverted");
        mainLayout()->insertItem (1, divider);
    }

    m_TitleLabel->setText (title ());
#endif
}

void DcpPage::setTitleStyleName (const QString& style)
{
    if (m_TitleLabel) {
        m_TitleLabel->setStyleName (style);
    }
}

