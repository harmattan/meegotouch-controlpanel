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
#include "dcpretranslator.h"

#include "dcpappletmetadata.h"

#include <QString>
#include <QSet>

class DcpRetranslatorPriv {
public:
    DcpRetranslatorPriv();
    QSet<QString> loadedTranslations;
    static DcpRetranslator* instance;
};

DcpRetranslator* DcpRetranslatorPriv::instance = 0;

DcpRetranslatorPriv::DcpRetranslatorPriv ()
{
}

DcpRetranslator::DcpRetranslator (): priv(new DcpRetranslatorPriv())
{
}

DcpRetranslator::~DcpRetranslator()
{
    delete priv;
    DcpRetranslatorPriv::instance = 0;
}

void
DcpRetranslator::retranslate ()
{
}

bool
DcpRetranslator::loadAppletTranslation (
        MLocale                &,
        const DcpAppletMetadata  *metadata)
{
    QStringList catalogList = metadata->translationCatalogs();
    priv->loadedTranslations.unite(catalogList.toSet());
    return true;
}

void
DcpRetranslator::ensureTranslationsAreLoaded(const DcpAppletMetadataList& list)
{
    foreach (DcpAppletMetadata* metadata, list) {
        ensureTranslationLoaded(metadata);
    }
}

void
DcpRetranslator::ensureTranslationLoaded(DcpAppletMetadata* metadata)
{
    QStringList catalogList = metadata->translationCatalogs();
    priv->loadedTranslations.unite(catalogList.toSet());
}

void
DcpRetranslator::ensureTranslationsAreLoaded(const QStringList &catalogs)
{
    priv->loadedTranslations.unite(catalogs.toSet());
}


DcpRetranslator*
DcpRetranslator::instance()
{
    if (DcpRetranslatorPriv::instance == NULL)
    {
        DcpRetranslatorPriv::instance = new DcpRetranslator();
    }
    return DcpRetranslatorPriv::instance;
}

bool
DcpRetranslator::eventFilter(QObject *obj, QEvent *event)
{
    return QObject::eventFilter(obj, event);
}
