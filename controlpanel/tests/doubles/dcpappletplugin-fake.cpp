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

#include "dcpappletplugin.h"
#include "dcpappletplugin-applet.h"
#include "dcpappletplugin_p.h"

DcpAppletPlugin::DcpAppletPlugin(DcpAppletMetadata *metadata):
   d_ptr(new DcpAppletPluginPrivate(metadata))
{
    load();
}

DcpAppletPluginPrivate::DcpAppletPluginPrivate(DcpAppletMetadata* metadata):
    appletMetadata(metadata),
    appletInstance(0)
{
}

DcpAppletPluginPrivate::~DcpAppletPluginPrivate ()
{}

DcpAppletPlugin::~DcpAppletPlugin()
{
}

DcpAppletIf *
DcpAppletPlugin::applet() const
{
    return d_ptr->appletInstance; 
}

bool
DcpAppletPlugin::isAppletLoaded() const
{
    return d_ptr->appletInstance != 0;
}

DcpAppletMetadata*
DcpAppletPlugin::metadata () const 
{ 
    return d_ptr->appletMetadata;
}

const QString 
DcpAppletPlugin::errorMsg () const
{ 
    return d_ptr->errorMsg; 
}

bool 
DcpAppletPlugin::loadPluginFile (
        const QString &)
{
    return false;
}

bool 
DcpAppletPlugin::loadDslFile (
        const QString &)
{
    return false;
}

void 
DcpAppletPlugin::load ()
{
    d_ptr->appletInstance = new DcpAppletPluginApplet();
}

int
DcpAppletPlugin::interfaceVersion() const
{
    return 999999;
}

