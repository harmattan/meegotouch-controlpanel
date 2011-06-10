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

#ifndef DCPREMOTEBRIEFRECEIVERPRIV_H
#define DCPREMOTEBRIEFRECEIVERPRIV_H

#include <QTextStream>
#include "dcpremotebrief.h"
#include <QHash>
#include <QLocalSocket>
#include <QLocalServer>
#include <QStringList>

class DcpRemoteBriefReceiver;

class DcpRemoteBriefReceiverPriv
{
public:
    DcpRemoteBriefReceiverPriv ();

    QLocalSocket* socket;
    QLocalServer* server;
    QTextStream send;
    QTextStream receive;
    DcpRemoteBrief* currentBrief;
    QHash<QString, DcpRemoteBrief*> briefs;

    static DcpRemoteBriefReceiver* instance;
    static bool disabled;
    static QStringList args;

    QStringList waitingCommands;
};


#endif // DCPREMOTEBRIEFRECEIVERPRIV_H

