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

#include "mlocale-fake.h"

#include <QHash>
#include <QList>
#include <QString>
#include <MCollator>

class FakeLocale {
    public:
        QList<QString> catalogs;
};

static const MLocale* defLocale = 0;
static QHash<const MLocale*, FakeLocale*> priv;

QList<QString> MLocale_installedCatalogs()
{
    return MLocale_catalogs(defLocale);
}

QList<QString> MLocale_catalogs(const MLocale* locale)
{
    return priv[locale]->catalogs;
}

MLocale::MLocale(QObject *parent):
    QObject(parent), d_ptr(0)
{
    priv.insert (this, new FakeLocale);
}

MLocale::MLocale(const MLocale &other, QObject *parent):
    QObject(parent), d_ptr(0)
{
    priv.insert (this, new FakeLocale);
    priv[this]->catalogs = priv[&other]->catalogs;
}

MLocale::MLocale(const QString &localeName, QObject *parent):
    QObject(parent), d_ptr(0)
{
    Q_UNUSED (localeName);
    priv.insert (this, new FakeLocale);
}

MLocale::~MLocale()
{
}

void MLocale::installTrCatalog(const QString &name)
{
    priv[this]->catalogs.append (name);
}

void MLocale::setDefault(const MLocale &locale)
{
    defLocale = &locale;
}

MCollator::MCollator(const MLocale &):
    d_ptr(0)
{

}

MCollator::MCollator(const MCollator&):
        d_ptr(0)
{

}

MCollator::~MCollator()
{

}

bool MCollator::operator()(const QString &, const QString &)const
{
    return true;
}

MLocale::Comparison MCollator::compare(const QString &, const QString &)
{
    return MLocale::GreaterThan;
}

Qt::LayoutDirection  MLocale::directionForText (const QString &text)
{
    return Qt::LeftToRight;
}

