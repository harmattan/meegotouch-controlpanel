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
#include "security.h"
#include "dcpappletmanager.h"

#include "dcpappletlauncherifadaptor.h"

#include <QtDebug>
#include <MApplication>
#include <MApplicationWindow>
#include <QDBusError>
#include <dcpdebug.h>
#include <DuiControlPanelIf>
#include <QDBusServiceWatcher>
#include <DcpAppletMetadata>

static const char* serviceName = "com.nokia.DcpAppletLauncher";


DcpAppletLauncherService::DcpAppletLauncherService ():
    MApplicationService (serviceName),
    m_IsServiceRegistered (false),
    m_SkipNextClosing (false)
{
    m_MainIface = new DuiControlPanelIf ("", this);
    // this makes us die if the main process dies anyhow:
#if 0
    // TODO this would be nicer, but does not work:
    connect (iface, SIGNAL (serviceUnavailable(QString)),
             this, SLOT (close()));
#else
    m_MainUnregistrationWatcher =
        new QDBusServiceWatcher ("com.nokia.DuiControlPanel",
                QDBusConnection::sessionBus(),
                QDBusServiceWatcher::WatchForUnregistration, this);
    connect (m_MainUnregistrationWatcher, SIGNAL (serviceUnregistered(QString)),
             this, SLOT (close()));
#endif

    // the main process will be able able to close us down if needed even if
    // the appletlauncher does not provide the service anymore,
    // through its (main process's) own service:
    connect (m_MainIface, SIGNAL (closeAppletLaunchers()), this, SLOT (closeWithDelay()));
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
    DcpAppletManager* mng = DcpAppletManager::instance();
    if (!mng->loadDesktopFile (m_AppletPath)) {
        close ();
    }

    // we get the name of the applet:
    DcpAppletMetadataList list = mng->list();
    dcp_failfunc_unless (list.count() >= 1, false);
    m_PageHandle.param = list.last()->name();

    // we drop our credentials here and load the applet with the credentials
    // it specifies only:
    Security::loadAppletRestricted (m_PageHandle.param);

    bool success = pageFactory->changePage (m_PageHandle);

    if (success) {
        // we only unregister the service if the window is shown to prevent
        // the user click on the appletbutton after that (it would open another
        // instace)
        QTimer::singleShot (1000, this, SLOT (unregisterService()));
        pageFactory->raiseMainWindow ();
    } else {
        close ();
    }

    return success;
}

bool DcpAppletLauncherService::sheduleApplet (const QString& appletPath,
                                              bool isStandalone)
{
    // only care about the first request
    if (m_PageHandle.id != PageHandle::NOPAGE) return false;

    m_PageHandle.id = PageHandle::APPLET;
    m_PageHandle.param = QString();
    m_PageHandle.widgetId = -1;
    m_PageHandle.isStandalone = isStandalone;
    m_AppletPath = appletPath;
    return true;
}


bool DcpAppletLauncherService::appletPage (const QString& appletPath)
{
    return sheduleApplet (appletPath) && maybeAppletRealStart();
}

void DcpAppletLauncherService::closeWithDelay ()
{
    if (m_SkipNextClosing) {
        m_SkipNextClosing = false;
        return;
    }
    QTimer::singleShot (0, this, SLOT(close()));
}

bool DcpAppletLauncherService::appletPageAlone (const QString& appletPath)
{
    m_SkipNextClosing = true;

    bool success = sheduleApplet (appletPath, true);

    // we start the mainwindow animation before loading the applet:
    if (!m_IsSheetOnly) {
        PageFactory::instance()->newWin ();
        PageFactory::instance()->raiseMainWindow ();
    }

    // in this scenario the main process hides its window, and we must
    // ensure that it will close if our window gets closed
    PageFactory::instance()->enableCloseMainProcessOnQuit();

    if (success) {
        success = maybeAppletRealStart();
    }
    return success;
}

bool DcpAppletLauncherService::registerService ()
{
    if (m_IsServiceRegistered) return true;
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
    m_IsServiceRegistered = true;
    return ret;
}

bool DcpAppletLauncherService::unregisterService ()
{
    if (!m_IsServiceRegistered) return true;

    QDBusConnection connection = QDBusConnection::sessionBus();

    connection.unregisterObject("/");
    bool ret = connection.unregisterService (serviceName);
    if (!ret) {
        QDBusError error = connection.lastError();
        qWarning ("Unregistering the service failed (%s): %s",
                qPrintable (error.name()), qPrintable (error.message()));
    }
    m_IsServiceRegistered = false;
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
    // this ensures that we never close the main process if it was the
    // one which instructed us to close
    PageFactory::instance()->enableCloseMainProcessOnQuit (false);

    MApplication* app = MApplication::instance();
    if (app) {
        app->exit (0);
    }
}

