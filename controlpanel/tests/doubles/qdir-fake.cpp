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

#include <QtDebug>
#include <QDir>
#include <QSharedData>
#include <QMap>

#include "qdir-fake.h"

QMap<QString,QStringList> s_FakeDirContentMap;
QMap<const QDir*,QString> s_FakeDirMap;

void QDirFake::createFakeDir(const QString &dir, const QStringList &content)
{
    s_FakeDirContentMap[dir] = content;
}

void QDirFake::removeFakeDir(const QString &dir)
{
    s_FakeDirContentMap.remove(dir);
}

class QDirPrivate : public QSharedData
{
};

QDir::QDir(const QString &dir)
{
    s_FakeDirMap[this] = dir;
}

QDir::~QDir()
{
    s_FakeDirMap.remove(this);
}

void QDir::setNameFilters(const QStringList &)
{
}

QString QDir::absoluteFilePath(const QString &fileName) const
{
    return s_FakeDirMap[this] + "/" + fileName;
}

QStringList QDir::entryList(const QStringList & nameFilters, 
                            Filters filters, 
                            SortFlags sort) const
{
    Q_UNUSED(nameFilters);
    Q_UNUSED(filters);
    Q_UNUSED(sort);

    return s_FakeDirContentMap[s_FakeDirMap[this]];
}

QStringList QDir::entryList(Filters filters, 
                            SortFlags sort) const
{
    Q_UNUSED(filters);
    Q_UNUSED(sort);

    return s_FakeDirContentMap[s_FakeDirMap[this]];
}

bool QDir::exists(const QString &name) const
{
    qDebug() << "exists" << name << s_FakeDirContentMap[s_FakeDirMap[this]].contains(name);
    return s_FakeDirContentMap[s_FakeDirMap[this]].contains(name);
}
