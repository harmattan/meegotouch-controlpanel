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

#ifndef DCPAPPLETMETADATA_P_H
#define DCPAPPLETMETADATA_P_H

#include <QFileInfo>
#include <QDateTime>
#include <MDesktopEntry>
class DcpAppletMetadata;

class DcpAppletMetadataPrivate
{
public:
    DcpAppletMetadataPrivate();
    ~DcpAppletMetadataPrivate();

    // last modification time of the desktop entry:
    QTime m_LastModified;
    MDesktopEntry* m_DesktopEntry;
    DcpAppletMetadata *m_Parent;
    QString m_FileName;
    bool m_Disabled;
    int m_Activated;
    static DcpAppletMetadata* sm_LastUsed;
};

enum  {
    KeyCategory = 0,
    KeyOrder,

    KeyWidgetType,
    KeyAlign,
    KeyToggleIconId,

    KeyText2,
    KeyImage,
    KeyBinary,
    KeyDslFilename,
    KeyApplicationCommand,

    KeyName,
    KeyNameId,
    KeyNameCatalog,

    KeyPart,
    KeyUnique,
    KeyParent,
    KeyCount
};

const QString Keys[KeyCount] = {
    "DCP/Category",
    "DCP/Order",

    "DCP/WidgetType",
    "DCP/Align",
    "DCP/ToggleIconId",

    "DCP/Text2",
    "DCP/Image",
    "DUI/X-DUIApplet-Applet",
    "DUI/X-DUIApplet-Dslfile",
    "DUI/X-DUIApplet-ApplicationCommand",

    "Desktop Entry/Name",
    "Desktop Entry/X-logical-id",
    "Desktop Entry/X-translation-catalog",
    "DCP/Part",
    "DCP/Unique",
    "DCP/Parent"
};

#endif // DCPAPPLETMETADATA_P_H

