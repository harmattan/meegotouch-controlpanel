/***************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Karoliina T. Salminen <karoliina.t.salminen@nokia.com>
**
** This file is part of duicontrolpanel.
**
**
** This library is free software; you can redistribute it and/or
** modify it under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation
** and appearing in the file LICENSE.LGPL included in the packaging
** of this file.
**
****************************************************************************/

#ifndef DCPAPPLET_H
#define DCPAPPLET_H

#include <QString>

namespace DcpApplet {
    const QString DefaultPath = DESKTOP_DIR ":" DESKTOP_DIR2;
    const QString Lib = APPLET_LIBS;
    const QString MostUsedCategory = "MostUsedCategory";
    const QString OtherCategories = "OtherCategories";
    const int MaxMostUsed = 4;
};

#endif // DCPAPPLET_H

