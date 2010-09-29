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

#include "qfileinfo-fake.h"

#include <QSet>
#include <QHash>
#include <QFileInfo>
#include <QString>
#include <QSharedData>

static QSet<QString> existingFiles;
static QHash<const QFileInfo*, QString> priv;
class QFileInfoPrivate: public QSharedData {};

void qfileinfo_setExists (const QString& filePath, bool exists)
{
    if (exists) {
        existingFiles.insert (filePath);
    } else {
        existingFiles.remove (filePath);
    }
}

QFileInfo::QFileInfo ( const QString & file )
{
    priv[this] = file;
}


bool QFileInfo::exists () const
{
    return existingFiles.contains (this->filePath());
}

QString QFileInfo::filePath () const
{
    return priv[this];
}

