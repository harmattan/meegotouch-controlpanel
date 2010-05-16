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

#include <DcpWidget>
#include <DcpAppletIf>
#include <DcpAppletMetadata>
#include <DcpAppletObject>
#include <DcpRetranslator>

#include <MLabel>
#include <MLocale>
#include <MApplication>
#include <MAction>
#include <QProcess>

#include "dcpdebug.h"

#include "mwidgetcreator.h"
M_REGISTER_WIDGET_NO_CREATE(DcpAppletPage)

DcpAppletPage::DcpAppletPage (DcpAppletObject *applet, int widgetId):
    DcpPage (),
    m_Applet(applet),
    m_WidgetId(widgetId),
    m_MainWidget (0),
    m_MissingLabel (0)
{
    // this is for being able to control leaving or not leaving the page
    // in response to clicking the back button
    setEscapeMode(MApplicationPageModel::EscapeManualBack);
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

    if (handle().isStandalone)
    {
       DCP_DEBUG("This is a standalone applet"); 
       qApp->exit(0);
       return;
    }
    DcpPage::back();
}

void
DcpAppletPage::loadWidget (int widgetId)
{
    DcpWidget  *newMainWidget;

    /*
     * Creating the widget and setting its widgetId.
     */
    newMainWidget = m_Applet->applet()->constructWidget (widgetId);

    /*
     * From now on, this is the widget we have. And if it is NULL, we just
     * return.
     */
    m_MainWidget = newMainWidget;

    if (newMainWidget != 0 && !newMainWidget->setWidgetId (widgetId) &&
        newMainWidget->getWidgetId () != widgetId)
    {
        /*
        * We needed to set the widgetId, for it is a new widget, but we
        * could not set it.
        */
        DCP_WARNING ("The widgetId could not be set for applet '%s' "
                     "widget %d it remains %d.",
                     DCP_STR (m_Applet->metadata()->name()),
                     widgetId,
                     newMainWidget->getWidgetId ());
    }

    if (!m_MainWidget) {
        return;
    }

    setPannable (m_MainWidget->pagePans());

    connect (m_MainWidget, SIGNAL (changeWidget(int)),
             m_Applet, SLOT(activateSlot(int)));
    connect (m_MainWidget, SIGNAL (activatePluginByName (const QString &)),
             m_Applet, SLOT (activatePluginByName (const QString &)));
    if (m_Applet->interfaceVersion() >= 2) {
        connect (m_MainWidget, SIGNAL (closePage()),
                 this, SLOT (back ()));
    }

    // add the actions:
    foreach (MAction* action, m_Applet->applet()->viewMenuItems()) {
        addAction(action);
    }

    appendWidget (m_MainWidget);
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

