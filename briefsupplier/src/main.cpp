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

#include <MApplication>

#include <DcpRetranslator>
#include "dcpappletdb.h"
#include "dcpwrongapplets.h"
#include "dcpmostusedcounter.h"
#include "briefsupplier.h"
#include "fakeapplicationservice.h"

#include <sys/time.h>
#include <sys/resource.h>

#include <unistd.h>
#include <dcpdebug.h>
#include "syslog.h"
#define LOW_PRIORITY

void cleanup ()
{
    // free up singletons:
    DcpRetranslator::destroy();
    DcpWrongApplets::destroyInstance();
    MostUsedCounter::destroy();
    DcpAppletDb::destroy();

    // free up application:
    delete MApplication::instance();
}

int main (int argc, char* argv[])
{
    openlog ("dcp-briefsupplier", LOG_PID, LOG_USER);
#ifdef LOW_PRIORITY
    setpriority(PRIO_PROCESS, 0, 19);
#endif // LOW_PRIORITY

    MApplication* app = new MApplication(argc, argv, new FakeApplicationService());

    // install the new translations if locale changes:
    DcpRetranslator* retranslator = DcpRetranslator::instance();
#if RETRANSLATE_ON_THE_FLY
    /*
    QObject::connect(&app, SIGNAL(localeSettingsChanged()),
                     retranslator, SLOT(retranslate()));
     */
#else
    Q_UNUSED (retranslator);
#endif

    // handle the arguments:
    QString desktopDir;
    bool noSupervisor = false;

    for (int i = 1; i < argc; ++i) {
        QString s(argv[i]);

        if (s == "-nosupervisor") {
            noSupervisor = true;
        } else if (s == "-desktopdir") {
            if (i + 1 < argc) {
                i++;
                desktopDir = argv[i];
                qDebug() << "Using desktopdir:" << desktopDir;
            }
        }
    }

#ifdef SUPERVISOR
    if (noSupervisor) {
        qDebug() << "Applet supervisor is disabled.";
        DcpWrongApplets::disable();
    } else {
        // start supervisor:
        DcpWrongApplets::connectSupervisorSignals();
        DcpWrongApplets::instance();
    }
#else
    DcpWrongApplets::disable();
#endif

    BriefSupplier supplier(desktopDir);
    QObject::connect(app, SIGNAL(localeSettingsChanged()),
                     &supplier, SLOT(onLocaleChange()));

    int result = app->exec();

    cleanup ();
    return result;
}

