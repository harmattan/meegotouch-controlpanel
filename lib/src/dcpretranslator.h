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
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */
#ifndef DCP_RETRANSLATOR_H
#define DCP_RETRANSLATOR_H

#include <QObject>
class MLocale;
class DcpAppletMetadata;
#include <QList>

typedef QList<DcpAppletMetadata*> DcpAppletMetadataList;

/*! \brief makes translation reload automatically
 *  \details MApplication's localeSettingsChanged signal should be connected
 *  on the retranslate slot, which loads the new translation.
 *  Also handles loading applet translations, they just should have the filename
 *  "duicontrolpanel-<appletname>.qm"
 *
 * Widgets have to define their retranslateUi() virtual function properly, so
 * that changes (new translations) could be shown immediately. */
class DcpRetranslator : public QObject
{
    Q_OBJECT
public:
    static DcpRetranslator* instance();
    ~DcpRetranslator();
    static void destroy();

    void setMainCatalogName (const QString& catalogName);
    void ensureTranslationsAreLoaded(const DcpAppletMetadataList& list);
    void ensureTranslationLoaded(DcpAppletMetadata* metadata);

public slots:
   void retranslate();

protected:
    DcpRetranslator();
    bool eventFilter(QObject *obj, QEvent *event);
    bool loadAppletTranslation (
            MLocale               &locale,
            const DcpAppletMetadata *metadata);
    class DcpRetranslatorPriv* priv;
    friend class Ut_DcpRetranslator;
};

#endif

