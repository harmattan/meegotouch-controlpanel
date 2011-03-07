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

#include <DcpRetranslator>
#include "service/duicontrolpanelservice.h"
#include "service/dcpappletlauncherservice.h"
#include "dcpappletdb.h"
#include "dcpwrongapplets.h"
#include "dcpremotebriefreceiver.h"
#include "pagefactory.h"
#include "dcpmostusedcounter.h"
#include "dcpcategories.h"

#include "dcpdebug.h"

#include <cstdio>
#include <sys/wait.h>
#include <unistd.h>
#include <MComponentCache>
#include <MApplication>
#include <MLocale>
#include "syslog.h"

static const QString appIdentifier = "duicontrolpanel";

static inline MApplication* createApplication (int argc, char** argv,
                                               MApplicationService* service)
{
#ifndef DISABLE_LAUNCHER
    return MComponentCache::mApplication(argc, argv, appIdentifier, service);
#else // USE_LAUNCHER
    return new MApplication (argc, argv, appIdentifier, service);
#endif // USE_LAUNCHER
}

int
startMainApplication (int argc, char* argv[])
{
    DCP_DEBUG ("");
    openlog ("dcp-main", LOG_PID, LOG_USER);

    // init servicefw api:
    DuiControlPanelService* service = new DuiControlPanelService ();

    MApplication *app = createApplication (argc, argv, service);

    // install the new translations if locale changes:
    DcpRetranslator* retranslator = DcpRetranslator::instance();
    QObject::connect(app, SIGNAL(localeSettingsChanged()),
                     retranslator, SLOT(retranslate()));

    /*
     * the translations of duicontrolpanel turned out to be in catalog
     * "settings"
     */
    DcpRetranslator::instance()->setMainCatalogName("settings");

    // we create the start page here
    service->createStartPage();

    int result = app->exec();

    return result;
}

int
startAppletLoader (int argc, char* argv[])
{
    DCP_DEBUG ("");
    openlog ("dcp-appletloader", LOG_PID, LOG_USER);

    // force the db to be empty, so that we do not popuplate it on the
    // instance call (and parse the .desktop files)
    DcpAppletDb::initEmptyDb();

    // init servicefw api:
    DcpAppletLauncherService* service = new DcpAppletLauncherService ();

    MApplication *app = createApplication (argc, argv, service);

    // we sleep until an applet gets requested through dbus:
    int result = app->exec();
    return result;
}

void cleanup ()
{
    // delete windows and pages:
    PageFactory::destroy();

    // free up singletons:
    DcpRemoteBriefReceiver::destroy();
    DcpRetranslator::destroy();
    DcpWrongApplets::destroyInstance();
    MostUsedCounter::destroy();
    DcpCategories::destroy();
    DcpAppletDb::destroy();

    // free up application:
    // This was disabled as a temporary workaround for a bug which I could not
    // reproduce, but which keeps coming on coreweb (NB#223592)
    // delete MApplication::instance();
}


M_EXPORT int main(int argc, char *argv[])
{
    // disables applet supervisor since only the helper process needs it
    DcpWrongApplets::disable();

    // parse options
    QString desktopDir;
    bool isAppletLoader = false; // are we the appletloader process?
    bool isOutprocess = false; // should we run applets outprocess?

    for (int i = 1; i < argc; ++i) {
        QString s(argv[i]);
        if (s == "-h" || s == "-help" || s == "--help" ) {
            QTextStream out(stdout);
            out << "Usage: " << argv[0] <<
                " [LIBM OPTION]... [-desktopdir DIR]\n\n";
            out << "  -desktopdir DIR     Load .desktop files from DIR\n";
            out << "  -nosupervisor       Disables applet supervisor\n";
            out << "  -nobriefs           Disables dynamic briefs\n";
            out << "  -outprocess         Run the applets in a separate process\n";
            out << "\n\n";
            break;

        } else if (s == "-nobriefs") {
            DcpRemoteBriefReceiver::disable ();

        } else if (s == "-servicefw") {
            DuiControlPanelService::isStartedByServiceFw = true;

        } else if (s == "-desktopdir") {
            if (i + 1 < argc) {
                i++;
                desktopDir = argv[i];
                qDebug() << "Using desktopdir:" << desktopDir;
            }
        } else if (s == "-outprocess") {
            isOutprocess = true;
            PageFactory::setInProcessApplets (!isOutprocess);

        } else if (s == "-appletloader") {
            isAppletLoader = true;
            isOutprocess = true;
            PageFactory::setInProcessApplets (!isOutprocess);
        }
    }

    int result;

    if (isAppletLoader) {
        // start the appletloader process here:
        result = startAppletLoader (argc, argv);

    } else 
    {
        // start the main process here:
        DcpRemoteBriefReceiver::setArguments (argc, argv);

        /*!
         * FIXME: If we have a desktop directory we have to load the desktop files
         * now. We could delay it by changing the DcpAppletDb class implementation.
         */
        if (!desktopDir.isEmpty()) {
            DCP_DEBUG ("### Creating DcpAppletDb in directory '%s'.", 
                    DCP_STR(desktopDir));
            DcpAppletDb::instance (desktopDir);
        }

        result = startMainApplication (argc, argv);
    }

    cleanup ();
    return result;
}

