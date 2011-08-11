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

#ifndef DCPAPPLETLAUNCHERSERVICE_H
#define DCPAPPLETLAUNCHERSERVICE_H

#include <MApplicationService>
#include "pages.h"

class MApplicationWindow;
class DuiControlPanelIf;
class QDBusServiceWatcher;

class DcpAppletLauncherService: public MApplicationService
{
        Q_OBJECT
public:
    DcpAppletLauncherService ();

    virtual bool registerService ();

public slots:
    bool appletPage (const QString& appletPath);
    bool appletPageAlone (const QString& appletPath);
    void prestart ();
    void close ();
    void closeWithDelay ();
    virtual bool unregisterService ();
    bool maybeAppletRealStart ();

private:
    bool sheduleApplet (const QString& appletPath, bool isStandalone = false);
    PageHandle m_PageHandle;
    QString m_AppletPath;
    bool m_IsServiceRegistered;
    DuiControlPanelIf* m_MainIface;
    QDBusServiceWatcher* m_MainUnregistrationWatcher;
    bool m_SkipNextClosing;
};


#endif // DCPAPPLETLAUNCHERSERVICE_H

