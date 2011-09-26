/***************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
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

#include <QString>
#include <QFile>
#include <QTextStream>
#include <QtDebug>
#include "dcpconfig.h"

static const int MaxLineLength = 256;

DcpConfig::DcpConfig(const QString &file) {
    parse(file);
}

DcpConfig::~DcpConfig() {
}

void DcpConfig::parse(const QString &file) {
    QFile cfg(file);
    if (cfg.open(QFile::ReadOnly)) {
        QTextStream stream(&cfg);
        QString line;
        while (!stream.atEnd()) {
            line = stream.readLine(MaxLineLength);
            if (!line.startsWith("#")) {
                m_DesktopsToPreload << line.trimmed();
            }
        }
    } else {
        qCritical() << "could not open" << file;
    }
}

QStringList DcpConfig::desktopsToPreload() {
    return m_DesktopsToPreload;
}
