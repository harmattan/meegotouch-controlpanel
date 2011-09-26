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

#ifndef DCPAPPLETMANAGER_H_
#define DCPAPPLETMANAGER_H_

#include <QObject>
#include <QStringList>
#include <QMap>
#include "dcpapplet.h"

/*!
 * \class DcpAppletManager
 * \brief This singleton class keeps track of all installed applets of Conrol
 *   Panel
 *
 * \details Applet manager loads applets based on .desktop files, they can
 *   be queried by category, usage, by applet name.  
 *   
 *   It has the same functinality as DcpAppletDb, but it has an asynchronous
 *   API.
 */

class DcpAppletMetadata;
class DcpAppletObject;

typedef QList<DcpAppletMetadata*> DcpAppletMetadataList;
typedef bool (*CheckCategory)(const QString &);
typedef QMap<QString, DcpAppletMetadata*> DcpAppletMetadataMap;
typedef QMap<QString, DcpAppletObject*> DcpAppletObjectMap;


class DcpAppletManager : public QObject
{
    Q_OBJECT

    public:
        static DcpAppletManager *instance();
        static void destroyInstance();

        virtual ~DcpAppletManager();
        void addDesktopDir(const QString &dir);
        void loadMetadata();
        void loadMetadataAsync();
        void preloadMetadata();
        void preloadMetadataAsync();
        bool isMetadataLoaded();
        bool isMetadataLoadStarted();
        bool mainPageAppletFound();
        bool isMetadataPreloaded();
        bool isMetadataPreloadStarted();
        bool loadDesktopFile(const QString &path);

        DcpAppletMetadataList list() const;
        DcpAppletMetadataList listByCategory(const QString &category) const;
        DcpAppletMetadataList listByCategory(const QStringList &categories,
                                             CheckCategory checkFunction = 0) const;
        DcpAppletMetadataList listMostUsed() const;
        DcpAppletObject *applet(const QString &name);
        DcpAppletMetadata *metadata(const QString &name) const;
        QStringList appletNames() const;
        bool containsFile(const QString &name) const;
        bool containsName(const QString &name) const;
        bool isAppletLoaded(const QString &name) const;
        QList<DcpAppletObject*> loadedApplets() const;

    signals:
        void metadataLoaded();
        void metadataPreloaded();
        void appletLoaded(DcpAppletObject *applet);

    protected:
        DcpAppletManager();

    private slots:
        void processSingleDesktopFile();

    private:
        static DcpAppletManager *sm_Instance;

        void clearData();

        Q_DISABLE_COPY(DcpAppletManager);
        DcpAppletMetadataMap m_AppletsByName;
        DcpAppletMetadataMap m_AppletsByFile;
        DcpAppletObjectMap m_AppletObjectsByName;
        QList<QString> m_DesktopDirs;
        QStringList m_DesktopFilesToProcess;
        bool m_IsMetadataLoaded;
        bool m_IsMetadataLoadStarted;
        bool m_MainPageAppletFound;
        bool m_IsMetadataPreloaded;
        bool m_IsMetadataPreloadStarted;

        friend class Ut_DcpAppletManager;
};

#endif // DCPAPPLETMANAGER_H_
