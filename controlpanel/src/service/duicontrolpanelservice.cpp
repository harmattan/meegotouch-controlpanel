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
#include "dcpappletmanager.h"

#include "duicontrolpanelifadaptor.h"
#include "duicontrolpanelif.h"
#include "dcpappletlauncherif.h"
#include "security.h"

#include <MApplicationIfAdaptor>
#include <QtDebug>
#include <MApplication>
#include <MApplicationWindow>
#include <QDBusServiceWatcher>
#include <dcpappletmetadata.h>
#include <dcpremotebriefreceiver.h>

static const char* serviceName = "com.nokia.DuiControlPanel";
static const char* serviceNameAppl = "com.nokia.DcpAppletLauncher";
bool DuiControlPanelService::isStartedByServiceFw = false;

#include "dcpdebug.h"

DuiControlPanelService::DuiControlPanelService ():
    MApplicationService (serviceName),
    m_StartPage (new PageHandle()),
    m_IsRegistered (false)
{
    // by default open the main page:
    if (! isStartedByServiceFw) {
        mainPage();
    }
}

void
DuiControlPanelService::launch ()
{
//    MApplicationService::launch ();

    /* this method not supposed to change the current page,
     * so we only setup a default if there is not any yet
     */

#ifdef NO_PAGE_DROPPING
    MApplicationWindow *win = MApplication::activeApplicationWindow();
    if ((m_StartPage && m_StartPage->id == PageHandle::NOPAGE) ||
        (!m_StartPage && win && !win->currentPage()))
#endif
    {
        mainPage();
    }
}

void
DuiControlPanelService::launch (const QStringList &parameters)
{
    Q_UNUSED (parameters);
    launch();
}


bool
DuiControlPanelService::registerService ()
{
    if (m_IsRegistered) return true;

    // memory owned by QDBusAbstractAdaptor instance and must be on the heap
    new DuiControlPanelIfAdaptor(this);
    new MApplicationIfAdaptor(this);

    QDBusConnection connection = QDBusConnection::sessionBus();

    bool ret = connection.registerService(serviceName);
    if (ret) {
        ret = connection.registerObject("/", this)
              && connection.registerObject("/org/maemo/m", this);

        if (!ret) {
            qWarning ("Error while registering the service object");
        }
    } else {
        qWarning ("Error while registering the service name");
    }

    if (!ret) {
        handleServiceRegistrationFailure();
    }

    m_IsRegistered = ret;
    return ret;
}

bool
DuiControlPanelService::appletPage (const QString& appletName)
{
    DcpAppletManager *mng = DcpAppletManager::instance();
    // TODO we could do some optimization here for popping up an applet the first
    // time (do not parse all .desktops)
    mng->loadMetadata ();
    DcpAppletMetadata* metadata = mng->metadata (appletName);
    dcp_failfunc_unless (metadata, false);

    // if the applet does not have a main view, we pop up its category page:
    if (!metadata->hasMainView()) {
        categoryPage (metadata->category());
        return true;

    } else if (!PageFactory::isInProcessApplets()) {
        MApplicationWindow* win = MApplication::activeApplicationWindow();

        // if we have no page yet and this is the first applet start,
        // then we run it inprocess and behave like an appletlauncher
        if (isStartedByServiceFw && (!win || !win->currentPage()))
        {
            bool success = unregisterService ();
            dcp_failfunc_unless (success, false);
            receiveCloseSignal ();
            Security::loadAppletRestricted (appletName);

            // we do not need the receiver in this process,
            // this ensures that it wont get started
            DcpRemoteBriefReceiver::disable ();

        } else {
            win->hide();
            QCoreApplication::processEvents();

            // if we already have a page, then we start the applet in an
            // appletlauncher:
            DcpAppletLauncherIf iface;
            dcp_failfunc_unless (iface.isValid(), false);
            iface.appletPageAlone (metadata->fileName());

            // close other chained windows:
            emit closeAppletLaunchers();
            PageFactory::instance()->closeHelpPage();

            return true;
        }
    }

    PageHandle handle (PageHandle::APPLET, appletName, -1, true);
    sheduleStart(handle);

    // TODO this hack prevents a servicefw issue, that the app does not get the
    // first query
    // Result means nothing...
    return true;
}

// this function makes us close if the main process arrives:
void
DuiControlPanelService::receiveCloseSignal ()
{
    QDBusServiceWatcher* watcher =
        new QDBusServiceWatcher (serviceName,
                QDBusConnection::sessionBus(),
                QDBusServiceWatcher::WatchForRegistration, this);
    connect (watcher, SIGNAL (serviceRegistered(QString)),
             this, SLOT (quitWithDelay()));
}

void DuiControlPanelService::quitWithDelay ()
{
    QTimer::singleShot (1500, qApp, SLOT(quit()));
}

void
DuiControlPanelService::receivePreloadSignal ()
{
    QDBusServiceWatcher* watcher =
        new QDBusServiceWatcher (serviceNameAppl,
                QDBusConnection::sessionBus(),
                QDBusServiceWatcher::WatchForUnregistration, this);
    connect (watcher, SIGNAL (serviceUnregistered(QString)),
             this, SLOT (preloadAppletLauncher()));
}

void
DuiControlPanelService::preloadAppletLauncher ()
{
    PageFactory* pf = PageFactory::instance();
    dcp_failfunc_unless (pf);
    pf->preloadAppletLauncher();
}

// FIXME XXX we should consider a common base class with DcpAppletLauncherService
bool DuiControlPanelService::unregisterService ()
{
    if (!m_IsRegistered) return true;
    QDBusConnection connection = QDBusConnection::sessionBus();

    connection.unregisterObject("/");
    connection.unregisterObject("/org/maemo/m");
    bool ret = connection.unregisterService (serviceName);
    if (!ret) {
        QDBusError error = connection.lastError();
        qWarning ("Unregistering the service failed (%s): %s",
                qPrintable (error.name()), qPrintable (error.message()));
    }

    m_IsRegistered = !ret;
    return ret;
}

bool
DuiControlPanelService::appletPage (const QStringList& params)
{
    if (params.isEmpty()) return false;

    // TODO we could add the other parameters to the applet
    QString appletName = params.at(0);
    return appletPage (appletName);
}

/* Starts the page through PageFactory */
void DuiControlPanelService::startPageForReal(const PageHandle &handle)
{
    PageFactory* pf = PageFactory::instance();

    // true means that it drops all the other pages
    bool success = pf->changePage(handle, true);

    if (success) {
        pf->raiseMainWindow ();
    } else {
        qWarning ("Failed to switch page (wrong page id?)");
    }
}

/* Either starts the page or shedules starting it if the window is not yet
 * created. */
void
DuiControlPanelService::sheduleStart (
                const PageHandle &handle)
{
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
    PageHandle handle (PageHandle::APPLETCATEGORY, category, -1, true);
    sheduleStart(handle);
}

void
DuiControlPanelService::mainPage()
{
    PageHandle handle (PageHandle::MAIN);
    sheduleStart(handle);
}

// this method gets called after mainwindow has been created,
// so after it has been called, the pages can be created for real
void
DuiControlPanelService::createStartPage()
{
    // createStartPage should not be called twice
    dcp_failfunc_unless (m_StartPage);

    PageHandle* handle = m_StartPage;
    m_StartPage = 0;

    // if started through servicefw we can end up not receiving the
    // servicefw call at this point, so taking no action yet
    if (handle->id != PageHandle::NOPAGE) {
        startPageForReal (*handle);
    }

    // From now on, pagefactory will be able to notify the applets running
    // in separate process to close down through this, but only if we
    // are the main process (not an appletlauncher)
    if (m_IsRegistered) {
        PageFactory* pf = PageFactory::instance();
        connect (pf, SIGNAL (resetAppletLauncherProcesses()),
                 this, SIGNAL (closeAppletLaunchers()));

        // applet launcher preloading:
        receivePreloadSignal();
    }

    delete handle;
}

