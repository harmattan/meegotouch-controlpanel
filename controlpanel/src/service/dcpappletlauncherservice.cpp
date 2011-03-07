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

#include "dcpappletlauncherservice.h"

#include "pagefactory.h"

#include "dcpappletlauncherifadaptor.h"

#include <QtDebug>
#include <MApplication>
#include <MApplicationWindow>
#include <QDBusError>
#include <DcpAppletDb>
#include <dcpdebug.h>
#include <DuiControlPanelIf>
#include <QDBusServiceWatcher>
#include <DcpAppletMetadata>

static const char* serviceName = "com.nokia.DcpAppletLauncher";


DcpAppletLauncherService::DcpAppletLauncherService ():
    MApplicationService (serviceName)
{
    DuiControlPanelIf* iface = new DuiControlPanelIf ("", this);
    // this makes us die if the main process dies anyhow:
#if 0
    // TODO this would be nicer, but does not work:
    connect (iface, SIGNAL (serviceUnavailable(QString)),
             this, SLOT (close()));
#else
    QDBusServiceWatcher* watcher =
        new QDBusServiceWatcher ("com.nokia.DuiControlPanel",
                QDBusConnection::sessionBus(),
                QDBusServiceWatcher::WatchForUnregistration, this);
    connect (watcher, SIGNAL (serviceUnregistered(QString)),
             this, SLOT (close()));
#endif

    // the main process will be able able to close us down if needed even if
    // the appletlauncher does not provide the service anymore,
    // through its (main process's) own service:
    connect (iface, SIGNAL (closeAppletLaunchers()), this, SLOT (close()));
}


/*
 * Pops up the applet's page if the window is already created
 * and raises it
 *
 * Returns false only if there was window but the page popup was unsuccessful
 */
bool DcpAppletLauncherService::maybeAppletRealStart ()
{
    if (m_PageHandle.id == PageHandle::NOPAGE)  return true;

    PageFactory* pageFactory = PageFactory::instance();

    // the db is empty, so we add the started applet into it:
    DcpAppletDb* db = DcpAppletDb::instance();
    if (!db->addFile (m_AppletPath)) {
        close ();
    }

    // we get the name of the applet:
    DcpAppletMetadataList list = db->list();
    dcp_failfunc_unless (list.count() >= 1, false);
    m_PageHandle.param = list.last()->name();

    // the pagefactory starts the applet out of process and refuses to load it,
    // in case it is not already loaded, so we load it here:
    DcpAppletDb::instance()->applet (m_PageHandle.param);
    bool success = pageFactory->changePage (m_PageHandle);

    if (success) {
        unregisterService ();
        pageFactory->raiseMainWindow ();
    } else {
        close ();
    }

    return success;
}

void DcpAppletLauncherService::sheduleApplet (const QString& appletPath)
{
    m_PageHandle.id = PageHandle::APPLET;
    m_PageHandle.param = QString();
    m_PageHandle.widgetId = 0;
    m_PageHandle.isStandalone = false;
    m_AppletPath = appletPath;
}


bool DcpAppletLauncherService::appletPage (const QString& appletPath)
{
    sheduleApplet (appletPath);
    return maybeAppletRealStart();
}

bool DcpAppletLauncherService::registerService ()
{
    // memory owned by QDBusAbstractAdaptor instance and must be on the heap
    new DcpAppletLauncherIfAdaptor(this);

    QDBusConnection connection = QDBusConnection::sessionBus();

    bool ret = connection.registerService (serviceName);
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

bool DcpAppletLauncherService::unregisterService ()
{
    QDBusConnection connection = QDBusConnection::sessionBus();

    connection.unregisterObject("/");
    bool ret = connection.unregisterService (serviceName);
    if (!ret) {
        QDBusError error = connection.lastError();
        qWarning ("Unregistering the service failed (%s): %s",
                qPrintable (error.name()), qPrintable (error.message()));
    }
    return ret;
}

void DcpAppletLauncherService::prestart ()
{
    MApplicationWindow* win = PageFactory::instance()->window();
    dcp_failfunc_unless (win);
    win->hide();
}

void DcpAppletLauncherService::close ()
{
    MApplication* app = MApplication::instance();
    if (app) {
        app->exit (0);
    }
}

