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
#include <cstdio>
#include <sys/wait.h>
#include <csignal>
#include <MApplicationWindow>
#include <MComponentCache>
#include <DcpDebug>
#include <DcpRetranslator>
#include <MApplication>
#include <MLocale>
#include "service/duicontrolpanelservice.h"
#include "dcpappletdb.h"
#include "appleterrorsdialog.h"
#include "dcpwrongapplets.h"
#include "dcpremotebriefreceiver.h"

#include "dcpdebug.h"

static const QString appIdentifier = "duicontrolpanel";

/* 
 * this redefines the signal handler for TERM and INT signals, so as to be able
 * to use aboutToQuit signal from qApp also in these cases 
 */
void 
onTermSignal (
        int param)
{
    DCP_DEBUG ("");

    Q_UNUSED(param);
    if (qApp) {
        qApp->quit();
    }
}

int
startApplication (int argc, char* argv[])
{
    DCP_DEBUG ("");

    // init servicefw api:
    DuiControlPanelService* service = new DuiControlPanelService ();

#ifndef DISABLE_LAUNCHER
    MApplication *app = MComponentCache::mApplication(argc, argv,
                                                      appIdentifier, service);
#else // USE_LAUNCHER
    MApplication *app = new MApplication (argc, argv, appIdentifier, service);
#endif // USE_LAUNCHER
    signal(SIGTERM, &onTermSignal);
    signal(SIGINT, &onTermSignal);

    // install the new translations if locale changes:
    DcpRetranslator* retranslator = DcpRetranslator::instance();
    QObject::connect(app, SIGNAL(localeSettingsChanged()),
                     retranslator, SLOT(retranslate()));

    /*
     * the translations of duicontrolpanel turned out to be in catalog
     * "settings"
     */
    DcpRetranslator::instance()->setMainCatalogName("settings");

    // mainwindow:
#ifndef DISABLE_LAUNCHER
    MApplicationWindow *win = MComponentCache::mApplicationWindow();
#else // USE_LAUNCHER
    MApplicationWindow *win = new MApplicationWindow();
#endif // USE_LAUNCHER

    win->installEventFilter(retranslator);

    // we create the start page here
    service->createStartPage();

    return app->exec();
}


M_EXPORT int main(int argc, char *argv[])
{
    DcpRemoteBriefReceiver::setArguments (argc, argv);

    // disables applet supervisor since only the helper process needs it
    DcpWrongApplets::disable();

    // parse options
    QString desktopDir;
    for (int i = 1; i < argc; ++i) {
        QString s(argv[i]);
        if (s == "-h" || s == "-help" || s == "--help" ) {
            QTextStream out(stdout);
            out << "Usage: " << argv[0] <<
                " [LIBM OPTION]... [-desktopdir DIR]\n\n";
            out << "  -desktopdir DIR     Load .desktop files from DIR\n";
            out << "  -nosupervisor       Disables applet supervisor";
            out << "\n\n";
            break;
        } else if (s == "-servicefw") {
            DuiControlPanelService::isStartedByServiceFw = true;
        } else if (s == "-desktopdir") {
            if (i + 1 < argc) {
                i++;
                desktopDir = argv[i];
                qDebug() << "Using desktopdir:" << desktopDir;
            }
        }
    }

    /*!
     * FIXME: If we have a desktop directory we have to load the desktop files
     * now. We could delay it by changing the DcpAppletDb class implementation.
     */
    if (desktopDir.isEmpty()) {
        DCP_DEBUG ("### Not creating DcpAppletDb, we can do it later.");
         //DcpAppletDb::instance ();
    } else {
        DCP_DEBUG ("### Creating DcpAppletDb in directory '%s'.", 
                DCP_STR(desktopDir));
        DcpAppletDb::instance (desktopDir);
    }

    DCP_DEBUG ("### Starting up application.");
    int st = startApplication (argc, argv);

    DcpAppletDb::destroy();

    return st;
}

