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

/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */
#ifndef DCPAPPLETDB_FAKE_H
#define DCPAPPLETDB_FAKE_H

/* Fake appletdb
 *
 * Works like a real db which contains by default two plugins from which only
 * one gets returned for mostUsed items.
 * More applets can be added with addFile which will always succeed.
 *
 * If you need to fake the db, consider using also:
 * - dcpappletmetadata-fake.cpp, so you can avoid using MDesktopEntry
 *   and .desktop files
 *
 */

#include "dcpappletdb.h"
#include "dcpappletdb_p.h"
#include "dcpappletmetadata.h"
#include "dcpappletobject.h"

static void createTestApplet(DcpAppletDbPrivate* d_ptr, const QString& name)
{
    DcpAppletMetadata* metadata = new DcpAppletMetadata(name);
    DcpAppletObject* applet = new DcpAppletObject (metadata);
    d_ptr->appletsByName[metadata->name()] = metadata;
    d_ptr->appletsByFile[metadata->fileName()] = metadata;
    d_ptr->appletObjectsByName[metadata->name()] = applet;
}

DcpAppletDb::DcpAppletDb (
        const QString   &pathName,
        const QString   &nameFilter) : d_ptr(new DcpAppletDbPrivate())
{
    Q_UNUSED(pathName);
    Q_UNUSED(nameFilter);

    /*
     * by default the fake db contains 2 test applets:
     * - test
     * - mostUsed (which is only returned with the most used list
     */
    createTestApplet(d_ptr, "fake");
    createTestApplet(d_ptr, "mostUsed");
}

DcpAppletDb *
DcpAppletDb::instance (
        const QString   &pathName,
        const QString   &nameFilter)
{
    if (!DcpAppletDbPrivate::sm_Instance) {
        DcpAppletDbPrivate::sm_Instance = new DcpAppletDb (
                pathName, nameFilter);
    }

    return DcpAppletDbPrivate::sm_Instance;
}

bool
DcpAppletDb::addFile(const QString& filename)
{
    createTestApplet(d_ptr, filename);
    return true;
}

bool
DcpAppletDb::addPath(const QString &pathName)
{
    Q_UNUSED(pathName);
    return true;
}

bool
DcpAppletDb::addFiles (
        const QString  &pathName, 
        const QString  &filter)
{
    Q_UNUSED(pathName);
    Q_UNUSED(filter);
    return true;
}

#ifdef MOSTUSED
DcpAppletMetadataList
DcpAppletDb::listMostUsed ()
{
   static DcpAppletMetadataList mostUsed;
   if (mostUsed.isEmpty()) {
       mostUsed.append (applet("mostUsed-name")->metadata());
   }
   return mostUsed;
}
#endif

DcpAppletObject *
DcpAppletDb::applet (
        const QString &name)
{
    return d_ptr->appletObjectsByName[name];
}

DcpAppletMetadata *
DcpAppletDb::metadata (const QString &name)
{
    return d_ptr->appletsByName[name];
}

bool DcpAppletDb::isAppletLoaded (const QString&)
{
    return false;
}

#endif // DCPAPPLETDB_FAKE_H

