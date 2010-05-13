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

/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et sw=4 ts=4 sts=4: */
#ifndef DCPAPPLETPLUGIN_FAKE_H
#define DCPAPPLETPLUGIN_FAKE_H
#include "dcpappletplugin.h"
#include "dcpappletplugin_p.h"
#include "dcpappletmetadata-fake.h"

DcpAppletPlugin::DcpAppletPlugin(DcpAppletMetadata *metadata)

    : d_ptr(new DcpAppletPluginPrivate(metadata))  
{};
#endif
