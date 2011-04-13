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

/* Fake appletmanager
 *
 * Works like a real manager which contains by default two plugins from 
 * which only one gets returned for mostUsed items.
 * More applets can be added with addFile which will always succeed.
 *
 * If you need to fake the manager, consider using also:
 * - dcpappletmetadata-fake.cpp, so you can avoid using MDesktopEntry
 *   and .desktop files
 *
 */

#include <QTimer>
#include <QtDebug>

#include "dcpappletmanager.h"
#include "dcpappletmetadata.h"
#include "dcpappletobject.h"

#define FAKE FakeDcpAppletManager::sm_fakeMap[this]

class FakeDcpAppletManager {

public:
    static QMap<const DcpAppletManager *, FakeDcpAppletManager *> sm_fakeMap;
    
    FakeDcpAppletManager(DcpAppletManager *mng) 
    {
        /*
         * by default the fake db contains 2 test applets:
         * - test
         * - mostUsed (which is only returned with the most used list
         */
        sm_fakeMap[mng] = this;
    }

    ~FakeDcpAppletManager() 
    {
        sm_fakeMap.remove(sm_fakeMap.key(this));
    }


    void createTestApplet(const QString& name)
    {
        DcpAppletMetadata* metadata = new DcpAppletMetadata(name);
        DcpAppletObject* obj = new DcpAppletObject (metadata);
        m_AppletsByName[metadata->name()] = metadata;
        m_AppletsByFile[metadata->fileName()] = metadata;
        m_AppletObjectsByName[metadata->name()] = obj;
    }

    DcpAppletObject *applet(const QString &name)
    {
        return m_AppletObjectsByName.value(name, 0);
    }

    DcpAppletMetadata *metadata(const QString &name)
    {
        return m_AppletsByName.value(name, 0);
    }

    DcpAppletMetadataList list()
    {
        return m_AppletsByName.values();
    }

    QMap<QString,DcpAppletMetadata *> m_AppletsByName;
    QMap<QString,DcpAppletMetadata *> m_AppletsByFile;
    QMap<QString,DcpAppletObject *> m_AppletObjectsByName;
};


QMap<const DcpAppletManager *, FakeDcpAppletManager *> FakeDcpAppletManager::sm_fakeMap;
DcpAppletManager *DcpAppletManager::sm_Instance;

DcpAppletManager::DcpAppletManager ()
{
    new FakeDcpAppletManager(this);
}

DcpAppletManager::~DcpAppletManager ()
{
    delete FAKE;
}

DcpAppletManager *
DcpAppletManager::instance ()
{
    if (!sm_Instance) {
        sm_Instance = new DcpAppletManager ();
    }

    return sm_Instance;
}

void
DcpAppletManager::destroyInstance()
{
    delete sm_Instance;
    sm_Instance = 0;
}

void
DcpAppletManager::loadMetadata()
{
    FAKE->createTestApplet("fake");
}

void
DcpAppletManager::loadMetadataAsync()
{
//    QTimer::singleShot(0, this, SLOT(processSingleDesktopFile()));
    processSingleDesktopFile();
}

bool
DcpAppletManager::isMetadataLoaded()
{
    return true;
}

bool
DcpAppletManager::isMetadataLoadStarted()
{
    return false;
}

bool
DcpAppletManager::loadDesktopFile(const QString &path)
{
    Q_UNUSED(path);
    return true;
}

void
DcpAppletManager::addDesktopDir(const QString &pathName)
{
    Q_UNUSED(pathName);
}

DcpAppletMetadataList
DcpAppletManager::listMostUsed () const
{
   static DcpAppletMetadataList mostUsed;
#ifdef MOSTUSED
   if (mostUsed.isEmpty()) {
       mostUsed.append (applet("mostUsed-name")->metadata());
   }
#endif
   return mostUsed;
}


DcpAppletObject *
DcpAppletManager::applet (
        const QString &name)
{
    Q_UNUSED(name);
    return FAKE->applet(name);
}

DcpAppletMetadata *
DcpAppletManager::metadata (const QString &name) const
{
    Q_UNUSED(name);
    return FAKE->metadata(name);
}

bool DcpAppletManager::isAppletLoaded (const QString&) const
{
    return false;
}

QList<DcpAppletObject*> DcpAppletManager::loadedApplets () const
{
    return QList<DcpAppletObject*>();
}

DcpAppletMetadataList
DcpAppletManager::list() const
{
    return FAKE->list();
}

DcpAppletMetadataList 
DcpAppletManager::listByCategory(const QString &category) const
{
    QList<DcpAppletMetadata*> filtered;

    foreach (DcpAppletMetadata *item, FAKE->m_AppletsByFile) {
        if (category.compare(item->category(), Qt::CaseInsensitive) == 0)
            filtered.append(item);
    }

    return filtered;
}

DcpAppletMetadataList
DcpAppletManager::listByCategory(const QStringList &categories,
                                 CheckCategory checkFunction) const
{
    Q_UNUSED(checkFunction);
    QList<DcpAppletMetadata*> filtered;

    foreach (DcpAppletMetadata *item, FAKE->m_AppletsByFile) {
        foreach (QString cat, categories) {
            if (cat.compare(item->category(), Qt::CaseInsensitive) == 0) {
                filtered.append(item);
                break;
            }
        }
    }

    return filtered;
}

QStringList
DcpAppletManager::appletNames() const
{
    return QStringList();
}
       
bool DcpAppletManager::containsFile(const QString &name) const
{
    Q_UNUSED(name);
    return false;
}

bool DcpAppletManager::containsName(const QString &name) const
{
    Q_UNUSED(name);
    return false;
}

void DcpAppletManager::processSingleDesktopFile()
{
    emit metadataLoaded();
}
