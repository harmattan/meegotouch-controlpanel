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

#ifndef DCPAPPLETOBJECT_P_H
#define DCPAPPLETOBJECT_P_H

class DcpBrief;
class DcpAppletIf;

class DcpAppletObjectPrivate
{
public:
    DcpAppletObjectPrivate();
    ~DcpAppletObjectPrivate();
    DcpAppletIf *applet;
    DcpBrief* m_Brief;
    DcpAppletMetadata *m_Metadata;
};

#endif // DCPAPPLETOBJECT_P_H

