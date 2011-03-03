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

#include "dcpappletpage.h"

#include "dcpappletwidget.h"
#include <DcpAppletIf>
#include <DcpAppletMetadata>
#include <DcpAppletObject>
#include <DcpRetranslator>

#include <MLabel>
#include <MLocale>
#include <MAction>
#include <MSceneManager>
#include <mwidgetcreator.h>
#include <QProcess>
#include <QCoreApplication>

#include "dcpdebug.h"

M_REGISTER_WIDGET_NO_CREATE(DcpAppletPage)

DcpAppletPage::DcpAppletPage (DcpAppletObject *applet, int widgetId):
    DcpPage (),
    m_Applet(applet),
    m_WidgetId(widgetId),
    m_MainWidget (0),
    m_MissingLabel (0)
{
}


DcpAppletPage::~DcpAppletPage ()
{
    if (m_Applet) {
        m_Applet->metadata()->markInactive();
    }
}

void
DcpAppletPage::createContent ()
{
    DcpPage::createContent ();
    load();
}

void
DcpAppletPage::polishEvent ()
{
    MSceneManager* manager = sceneManager();

    if (!manager || !manager->pageHistory().isEmpty()) {
        // this is for being able to control leaving or not leaving the page
        // in response to DcpWidget::back()
        setEscapeMode(MApplicationPageModel::EscapeManualBack);
    }
}

bool 
DcpAppletPage::hasWidget ()
{
    return m_MainWidget;
}

bool 
DcpAppletPage::hasError ()
{
    return m_MissingLabel;
}

int 
DcpAppletPage::widgetId ()
{
    return m_WidgetId;
}

/*!
 * This function might do three things. If the applet variant has a binary
 * applet it will call the binary and load the main widget of the applet
 * variant. If the applet variant has an application command (a shell command
 * that should be called when the applet is activated) the function will execute
 * the shell command. Finaly if neither the applet binary is loaded nor the
 * shell command is available this function will create wome widgets to show
 * that the applet is not available.
 */
void
DcpAppletPage::load ()
{
    DCP_DEBUG ("");

    if (m_Applet) {
        m_Applet->metadata()->markActive();
        DcpRetranslator::instance()->ensureTranslationLoaded(
               m_Applet->metadata());

       if (m_Applet->isAppletLoaded()) {

            /*
             * If the plugin is available (loaded) we call it to create a new
             * view. (Here we got the widgetId from the plugin itself using the
             * DCP/Part key of the desktop file.)
             */
            if (m_WidgetId < 0) {
                m_WidgetId = m_Applet->getMainWidgetId();
            }
            loadWidget (m_WidgetId);

            return;
        } else if (m_Applet->metadata()->hasApplicationCommand ()) {
            /*
             * If the applet is not loaded from a binary file, but it has an
             * activation command line we execute an external application.
             */
            QString command = m_Applet->metadata()->applicationCommand();
            QProcess *process = new QProcess();

            /* redirect std io channels to /dev/null
             * because otherwise if command is applauncher's invoker 
             * it will pass pipes created by QProcess to the launched 
             * application, which are not valid anymore 
             * see bug 182372
             */            
            process->setStandardInputFile("/dev/null");
            process->setStandardOutputFile("/dev/null");
            process->setStandardErrorFile("/dev/null");

            // this will free up the QProcess when the process ended:
            connect (process, SIGNAL(finished ( int, QProcess::ExitStatus)),
                     process, SLOT(deleteLater()));

            process->start(command);
            return;
        }

        DCP_WARNING ("The applet has no loaded plugin nor an external "
                "command defined");
    } else {
        DCP_WARNING ("The applet is not valid.");
    }

    /*
     * Showing the 'plugin not available' label. We currently show this only if
     * the plugin is really not available, we will not show this if the plugin
     * is crashed. The plugin will be re-enabled (and most likely crash again)
     * when the user activates the applet by clicking on the brief.
     */
    if (!m_MissingLabel) {
        // FIXME: these are temporary translation ids and not present anywhere

        //% "Plugin not available"
        m_MissingLabel = new MLabel (qtTrId("dcp_no_applet_name"));
        m_MissingLabel->setAlignment (Qt::AlignCenter);
        appendWidget (m_MissingLabel);
        //% "Missing plugin"
        setTitle (qtTrId("dcp_no_applet_title"));
    }
}

void
DcpAppletPage::back ()
{
    DCP_DEBUG ("");

    if (m_MainWidget) {
        if (!m_MainWidget->back()) {
            return;
        }
    }

    /*
     * Disabled this because of bug NB#184916
     * Did not remove the support though, because it might turn out that we
     * have to lower the window here, if the behaviour in this case becomes
     * clear. Do not remove message this until then.
     */
#ifdef STANDALONE_CLOSES
    if (handle().isStandalone)
    {
       DCP_DEBUG("This is a standalone applet"); 
       qApp->exit(0);
       return;
    }
#endif

    DcpPage::back();
}


/*! \brief Constructs the applet's widget
 *
 * \param applet    The applet
 * \param page      If not null, then the page gets initialized with the
 *                  actions, etc the applet specifies
 * \param widgetId  The id of the widget to create.
 *
 * \returns the constructed, initialized DcpWidget.
 */
DcpAppletWidget*
DcpAppletPage::constructAppletWidget (DcpAppletObject* applet,
                                      DcpPage* page, int widgetId)
{
    if (!applet || !applet->applet()) return 0;

    DcpAppletWidget* widget = 0;
    if (applet->interfaceVersion () >= 6) {
        DcpStylableWidget* w =
            applet->applet()->constructStylableWidget (widgetId);
        if (w != 0) {
            widget = new DcpAppletWidget (w);
        }
    }
    if (widget == 0) {
        DcpWidget* w =
            applet->applet()->constructWidget (widgetId);
        if (w != 0) {
            widget = new DcpAppletWidget (w);
        }
    }

    if (!widget) return widget;

    if (!widget->setWidgetId (widgetId) &&
        widget->getWidgetId () != widgetId)
    {
        /*
        * We needed to set the widgetId, for it is a new widget, but we
        * could not set it.
        */
        DCP_WARNING ("The widgetId could not be set for applet '%s' "
                     "widget %d it remains %d.",
                     DCP_STR (applet->metadata()->name()),
                     widgetId,
                     widget->getWidgetId ());
    }

    connect (widget, SIGNAL (changeWidget(int)),
             applet, SLOT(activateSlot(int)));
    connect (widget, SIGNAL (activatePluginByName (const QString &)),
             applet, SLOT (activatePluginByName (const QString &)));

    if (page) {
        if (applet->interfaceVersion() >= 2) {
            connect (widget, SIGNAL (closePage()),
                     page, SLOT (back ()));
            if (applet->interfaceVersion() >= 4) {
                connect (widget, SIGNAL (inProgress (bool)),
                         page, SLOT (setProgressIndicatorVisible (bool)));
                page->setProgressIndicatorVisible (
                        widget->isProgressIndicatorVisible());
            }
        }

        // add the actions:
        foreach (MAction* action, applet->applet()->viewMenuItems()) {
            page->addAction(action);
        }
    }

    return widget;
}

void
DcpAppletPage::loadWidget (int widgetId)
{
    /*
     * Creating the widget and setting its widgetId.
     */
    m_MainWidget = constructAppletWidget (m_Applet, this, widgetId);
    if (!m_MainWidget) return;

    setPannable (m_MainWidget->pagePans());

    appendWidget (m_MainWidget->graphicsWidget());
    retranslateUi();
}

void
DcpAppletPage::retranslateUi ()
{
    DCP_DEBUG ("");

    if (m_Applet && m_Applet->applet()) {
        QString title;
        if (m_MainWidget && m_Applet->interfaceVersion() >= 3) {
            // this is the new way to specify the title:
            title = m_MainWidget->title();
        }

        if (title.isEmpty()) {
            // this is the deprecated way:
            title = m_Applet->applet()->title();
            if (title.isEmpty()) {
                title = m_Applet->text1();
            }
        }

        setTitle(title);
    }
}

DcpAppletObject* DcpAppletPage::applet()
{
    return m_Applet;
}

