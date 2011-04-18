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
#ifndef DCPAPPLETPLUGIN_H
#define DCPAPPLETPLUGIN_H

#include <QObject>
#include <QString>
class DcpAppletMetadata;
class DcpAppletIf;
class DcpAppletPluginPrivate;
class QTime;

/*!
 * \brief This class loads the binary plugin (if any) based on its metadata.
 *
 */
 class DcpAppletPlugin : public QObject
{
    Q_OBJECT

public:
    explicit DcpAppletPlugin(DcpAppletMetadata *metadata);
    DcpAppletPlugin(DcpAppletMetadata *metadata, bool tryLoad);
    virtual ~DcpAppletPlugin();

    DcpAppletIf *applet() const;
    bool isAppletLoaded() const;
    DcpAppletMetadata *metadata() const;
    const QString errorMsg () const;
    int interfaceVersion() const;

    static void setDefaultLoadHints (int hints);

protected:
    virtual void load ();
    virtual bool loadPluginFile (const QString &binaryPath);
    virtual bool loadDslFile    (const QString &dslPath);

private:
    DcpAppletPluginPrivate *const d_ptr;
    Q_DISABLE_COPY(DcpAppletPlugin);
    friend class Ut_DcpAppletPlugin;

};

#endif

