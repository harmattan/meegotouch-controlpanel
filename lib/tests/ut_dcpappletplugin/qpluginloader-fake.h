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

#ifndef QPLUGINLOADER_FAKE_H__
#define QPLUGINLOADER_FAKE_H__

#include <QtDebug>
#include "dcpappletplugin-applet.h"

static bool qPluginLoaderFakeSuccessful = true;
static const QString fakeErrorMsg("fake-error-msg");


QPluginLoader::QPluginLoader(const QString &fileName, QObject *parent)
{
    Q_UNUSED(fileName);
    Q_UNUSED(parent);
}

QPluginLoader::~QPluginLoader() {}

bool QPluginLoader::load()
{
    return qPluginLoaderFakeSuccessful;
}

QString QPluginLoader::errorString() const
{
    if (qPluginLoaderFakeSuccessful) {
        return "";
    }

    return fakeErrorMsg;
}

QObject *QPluginLoader::instance()
{
    if (qPluginLoaderFakeSuccessful) {
        return new DcpAppletPluginApplet();
    }

    return 0;
}

#endif
