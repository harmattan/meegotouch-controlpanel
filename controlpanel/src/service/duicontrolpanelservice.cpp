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

#include "duicontrolpanelservice.h"
#include "pagefactory.h"

#include "duicontrolpanelifadaptor.h"
#include <QtDebug>
#include <MApplication>
#include <MWindow>
#include "duicontrolpanelif.h"

static const char* serviceName = "com.nokia.DuiControlPanel";
bool DuiControlPanelService::isStartedByServiceFw = false;

#include "dcpdebug.h"

DuiControlPanelService::DuiControlPanelService ():
    MApplicationService (serviceName),
    m_StartPage (new PageHandle())
{
    DCP_DEBUG ("");

    // by default open the main page:
    if (! isStartedByServiceFw) {
        mainPage();
    }
}


void
DuiControlPanelService::launch ()
{
    mainPage();
    MApplicationService::launch ();
}


bool
DuiControlPanelService::registerService ()
{
    // memory owned by QDBusAbstractAdaptor instance and must be on the heap
    new DuiControlPanelIfAdaptor(this);

    QDBusConnection connection = QDBusConnection::sessionBus();

    bool ret = connection.registerService(serviceName);
    if (ret) {
        ret = connection.registerObject("/", this);
        if (!ret) {
            qWarning ("Error while registering the service object");
        }
    } else {
        qWarning ("Error while registering the service name");
    }

    if (!ret) {
        handleServiceRegistrationFailure();
    }
    return ret;
}

bool
DuiControlPanelService::appletPage (
        const QString& appletName)
{

    DCP_DEBUG ("");
    PageHandle handle (PageHandle::APPLET, appletName, 0, true);
    sheduleStart(handle);

    // TODO this hack prevents a servicefw issue, that the app does not get the
    // first query Result means nothing...
    return true;
}

/* Starts the page through PageFactory */
void
DuiControlPanelService::startPageForReal(
                const PageHandle &handle)
{
    PageFactory::instance()->changePage(handle);

    MWindow *win = MApplication::activeWindow();

    if (win) {
        win->activateWindow();
        win->show();
        win->raise();
    }
}

/* Either starts the page or shedules starting it if the window is not yet
 * created. */
void
DuiControlPanelService::sheduleStart (
                const PageHandle &handle)
{
    DCP_DEBUG ("");
    /* start contains the page to start when the window has appeared.
     * After the window is already created, it is null */
    if (m_StartPage == 0) {
        startPageForReal(handle);
    } else {
        *m_StartPage = handle;
    }
}

void
DuiControlPanelService::categoryPage (const QString& category)
{
    DCP_DEBUG ("");
    Q_UNUSED (category);
    /* FIXME implement it
    PageHandle handle (PageHandle::APPLETCATEGORY, category, 0, true);
    sheduleStart(handle);
     */
    DCP_WARNING("Openning a categoryPage is not implemented yet.");
    mainPage();
}

void
DuiControlPanelService::mainPage()
{
    DCP_DEBUG ("");
    PageHandle handle;
    handle.id = PageHandle::MAIN;
    handle.param = "";
    sheduleStart(handle);
}

// this method gets called after mainwindow has been created,
// so after it has been called, the pages can be created for real
void
DuiControlPanelService::createStartPage()
{
    DCP_DEBUG ("");
    // createStartPage should not be called twice
    Q_ASSERT(m_StartPage);

    PageHandle* handle = m_StartPage;
    m_StartPage = 0;

    // if started through servicefw we can end up not receiving the
    // servicefw call at this point, so taking no action yet
    if (handle->id != PageHandle::NOPAGE) {
        startPageForReal (*handle);
    }

    delete handle;
}

void
DuiControlPanelService::handleServiceRegistrationFailure()
{
    // raise the mainpage of controlpanel:
    DuiControlPanelIf iface;
    if (iface.isValid()) {
        iface.mainPage();
    }

    // quit:
    exit();
}

