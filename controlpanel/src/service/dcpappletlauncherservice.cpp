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

static const char* serviceName = "com.nokia.DcpAppletLauncher";


DcpAppletLauncherService::DcpAppletLauncherService ():
    MApplicationService (serviceName)
{
//    DuiControlPanelIf* iface = new DuiControlPanelIf ("", this);
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
#if 0
    // TODO why is this not working?
    connect (iface, SIGNAL (closeAppletLaunchers()), this, SLOT (close()));
#else
    QDBusConnection::sessionBus().connect ("","/","com.nokia.DuiControlPanelIf",
            "closeAppletLaunchers", this, SLOT(close()));
#endif
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

    // mainwindow:
    MApplicationWindow *win;
    if (MApplication::windows().isEmpty())  {
        win = new MApplicationWindow();
        win->setAttribute( Qt::WA_DeleteOnClose, true );
    } else {
        win = qobject_cast<MApplicationWindow*>(MApplication::windows().at(0));
        dcp_failfunc_unless (win, false);
    }

    // FIXME XXX: the instance() call makes the .desktop files parsed unnecesserily
    PageFactory* pageFactory = PageFactory::instance();
    // the pagefactory starts the applet out of process and refuses to load it,
    // in case it is not already loaded, so we load it here:
    DcpAppletDb::instance()->applet (m_PageHandle.param);
    bool success = pageFactory->changePage (m_PageHandle);

    if (success) {
        unregisterService ();
        win->show();
        win->activateWindow();
        win->raise();
    }

    return success;
}

void DcpAppletLauncherService::sheduleApplet (const QString& appletName)
{
    m_PageHandle.id = PageHandle::APPLET;
    m_PageHandle.param = appletName;
    m_PageHandle.widgetId = 0;
    m_PageHandle.isStandalone = false;
}


bool DcpAppletLauncherService::appletPage (const QString& appletName)
{
    sheduleApplet (appletName);
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
    MApplicationWindow *win = new MApplicationWindow();
    win->setAttribute( Qt::WA_DeleteOnClose, true );
    win->hide();
}

void DcpAppletLauncherService::close ()
{
    MApplication* app = MApplication::instance();
    if (app) {
        app->exit (0);
    }
}

