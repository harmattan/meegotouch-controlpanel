/***************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
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
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */

#include <QDir>
#include <QDebug>
#include <QTimer>

#include "dcpappletmanager.h"
#include "dcpappletmetadata.h"
#include "dcpappletobject.h"
#include "dcpdebug.h"

const QString AppletFilter = "*.desktop";
DcpAppletManager *DcpAppletManager::sm_Instance = 0;

DcpAppletManager *DcpAppletManager::instance()
{
    if (!sm_Instance) {
        sm_Instance = new DcpAppletManager;
    }
    return sm_Instance;
}

void DcpAppletManager::destroyInstance()
{
    delete sm_Instance;
    sm_Instance = 0;
}

DcpAppletManager::DcpAppletManager() 
{
}

DcpAppletManager::~DcpAppletManager()
{
    clearData();
}

void DcpAppletManager::addDesktopDir(const QString &dir)
{
    m_DesktopDirs.append(dir);
}

/*! \brief Loads applet definitions from .desktop files in a blocking way
 */
void DcpAppletManager::loadMetadata()
{
    QStringList nameFilters(AppletFilter);
    foreach (QString dirName, m_DesktopDirs) {
        QDir dir(dirName);
        dir.setNameFilters(nameFilters);
        foreach (QString entry, dir.entryList(QDir::Files)) {
            QString path = dir.absoluteFilePath(entry);
            DCP_DEBUG ("Loading %s", DCP_STR(path));
            if (!loadDesktopFile(path)) {
                qWarning() << "Failed to load" << path;
            }
        }
    }
 }

/*! \brief Loads applet definitions from .desktop files in an asynchronous way.
 *
 * When finishes it emits metadataLoaded signal. If loadMetadataAsync
 * is called again before the previous job finished metadataLoaded
 * will still be emitted only once.
 */
void DcpAppletManager::loadMetadataAsync()
{
    QStringList nameFilters(AppletFilter);
    foreach (QString dirName, m_DesktopDirs) {
        QDir dir(dirName);
        dir.setNameFilters(nameFilters);
        foreach (QString entry, dir.entryList(QDir::Files)) {
            m_DesktopFilesToProcess.append(dir.absoluteFilePath(entry));
        }
    }
    QTimer::singleShot(0, this, SLOT(processSingleDesktopFile()));
}

/*! \brief Adds a single applet defined in path to the manager
 */
bool DcpAppletManager::loadDesktopFile(const QString &path)
{
    if (containsFile(path)) {
        qWarning() << path << "is already loaded, ignoring";
        return false;
    }

    DcpAppletMetadata *metadata = new DcpAppletMetadata(path);
    if (!metadata->isValid()) {
        qWarning() << "invalid desktop file:" << path;
        delete metadata;
        return false;
    }
    if (metadata->isHidden()) {
        DCP_DEBUG ("ignoring hidden applet: %s", DCP_STR(path));
        delete metadata;
        return false;
    }

    DCP_DEBUG ("Adding applet name '%s'", DCP_STR (metadata->name()));
    m_AppletsByName[metadata->name()] = metadata;
    m_AppletsByFile[path] = metadata;
    return true;
}

DcpAppletMetadataList DcpAppletManager::list() const
{
    return m_AppletsByFile.values();
}

DcpAppletMetadataList 
DcpAppletManager::listByCategory(const QString &category) const
{
    QList<DcpAppletMetadata*> filtered;

    foreach (DcpAppletMetadata *item, m_AppletsByFile) {
        if (category.compare(item->category(), Qt::CaseInsensitive) == 0)
            filtered.append(item);
    }

    return filtered;
}

DcpAppletMetadataList
DcpAppletManager::listByCategory(const QStringList &categories,
                                 CheckCategory checkFunction) const
{
    QList<DcpAppletMetadata*> filtered;

    foreach (DcpAppletMetadata *item, m_AppletsByFile) {
        foreach (QString category, categories) {
            /*
             * We add this item if we asked to include the uncategorized
             * items and this is an uncategorized item or if the item is in the
             * category we are requested for.
             */
            if ((checkFunction && !checkFunction (item->category ())) ||
                    !item->category().compare (
                        QString(category), Qt::CaseInsensitive)) {
                filtered.append (item);
                break;
            }
        }
    }

    return filtered;
}

DcpAppletMetadataList DcpAppletManager::listMostUsed() const
{
    DcpAppletMetadataList mostUsed;
#ifdef MOSTUSED
    DcpAppletMetadata* lastUsed = DcpAppletMetadata::lastUsed();

    for (QMap<QString, DcpAppletMetadata*>::iterator iter =
            m_AppletsByName.begin(); iter != m_AppletsByName.end();
            iter++)
    {
        // we skip not used items, and also the last used item
        // (to avoid duplication)
        if (iter.value()->usage() && iter.value() != lastUsed)
            mostUsed.push_back(iter.value());
    }

    qSort (mostUsed.begin(), mostUsed.end(), 
           DcpAppletMetadata::usageGreatherThan);

   // last clicked item should be the first item (see bug NB#169944)
   if (lastUsed) {
        mostUsed.prepend (lastUsed);
   }
   mostUsed = mostUsed.mid (0, DcpApplet::MaxMostUsed);
#endif
   return mostUsed;
}

/*!
 * \brief Returns the applet found in the database by its name.
 */
DcpAppletObject *DcpAppletManager::applet (const QString &name)
{
    DcpAppletObject *obj = m_AppletObjectsByName.value(name, 0);

    if (!obj)
    {
        DcpAppletMetadata *metadata = m_AppletsByName.value(name, 0);
        if (metadata)
        {
            obj = new DcpAppletObject(metadata);
            m_AppletObjectsByName[name] = obj;
            emit appletLoaded (obj);
        }
        else
            qWarning() << "No such applet:" << name;
    }
    return obj;
}

DcpAppletMetadata *DcpAppletManager::metadata(const QString &name) const
{
    return m_AppletsByName.value(name);
}

QStringList DcpAppletManager::appletNames() const
{
    return m_AppletsByName.keys();
}

bool DcpAppletManager::containsFile(const QString &name) const
{
    return m_AppletsByFile.contains(name);
}

bool DcpAppletManager::containsName(const QString &name) const
{
    return m_AppletsByName.contains(name);
}

bool DcpAppletManager::isAppletLoaded(const QString &name) const
{
    return m_AppletObjectsByName.contains(name);
}

QList<DcpAppletObject*> DcpAppletManager::loadedApplets() const
{
    return m_AppletObjectsByName.values();
}

void DcpAppletManager::processSingleDesktopFile()
{
    if (m_DesktopFilesToProcess.isEmpty()) {
        DCP_DEBUG ("metadata load finished");
        emit metadataLoaded();
        return;
    }

    QString file = m_DesktopFilesToProcess.takeFirst();
    DCP_DEBUG ("Loading %s", DCP_STR(file));
    bool st = loadDesktopFile(file);
    if (!st) {
        qWarning() << "Failed to load" << file;
    }
    QTimer::singleShot(0, this, SLOT(processSingleDesktopFile()));
}

void DcpAppletManager::clearData()
{
    DCP_DEBUG ("Destroying DcpAppletObjects");
    foreach(DcpAppletObject *applet, m_AppletObjectsByName) {
        delete applet;
    }
    m_AppletObjectsByName.clear();

    DCP_DEBUG ("Destroying all metadata.");
    foreach(DcpAppletMetadata *metadata, m_AppletsByName) {
        delete metadata;
    }
    m_AppletsByName.clear();

    // clear indexes:
    m_AppletsByFile.clear();
    m_DesktopDirs.clear();
}
