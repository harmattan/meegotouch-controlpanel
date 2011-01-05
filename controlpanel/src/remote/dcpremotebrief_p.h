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

#ifndef DCPREMOTEBRIEF_P_H
#define DCPREMOTEBRIEF_P_H

#include <../../briefsupplier/src/bsuppliercommands.h>
#include <QString>
#include <QHash>

#include "dcpremotebriefreceiver.h"

class DcpRemoteBriefPriv
{
public:
    DcpRemoteBriefPriv (const QString& name);

    QString appletName;
    QHash<const char*, QString> values;
};

#endif // DCPREMOTEBRIEF_P_H

