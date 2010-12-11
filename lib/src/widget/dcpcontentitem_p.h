/***************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Karoliina T. Salminen <karoliina.t.salminen@nokia.com>
**
** This file is part of mcontrolpanel.
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

#include <MImageWidget>
#include <MButton>
#include <MLabel>
#include <MHelpButton>

/******************************************************************************
 * Private data class for the DcpContentItem class.
 */
class DcpContentItemPrivate {
public:
    DcpContentItemPrivate ();

    // one of these is non null
    DcpAppletObject *m_Applet;
    DcpAppletMetadata *m_Metadata;

    bool m_Hidden;

    QString m_TDriverID;

    // for the image widget:
    QString m_ImageName; // either the image id or path

    bool m_LayoutIsToBeChanged;

    // widgets:
    MImageWidget* m_ImageW;
    MImageWidget* m_DrillImage;
    MLabel* m_Text1W;
    MLabel* m_Text2W;
    MHelpButton* m_Help;
    QGraphicsWidget* m_Spacer;
    MButton* m_ButtonW;
};

#endif // DCPCONTENTITEMPRIVATE_H

