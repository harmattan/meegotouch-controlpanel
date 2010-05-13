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

#ifndef DCPCONTENTITEMPRIVATE_H
#define DCPCONTENTITEMPRIVATE_H

#include "dcpappletobject.h"
#include "dcpappletmetadata.h"
#include "dcpwidgettypes.h"

/******************************************************************************
 * Private data class for the DcpContentItem class.
 */
class DcpContentItemPrivate {
public:
    DcpContentItemPrivate ();

    DcpAppletObject *m_Applet;
    int m_WidgetTypeId;
    bool m_Hidden;

    QString m_MattiID;

    // for the image widget:
    QString m_ImageName; // either the image id or path
    const QPixmap* m_Pixmap;   // the pixmap requested from MTheme if any
};

#endif // DCPCONTENTITEMPRIVATE_H

