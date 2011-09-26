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
#include "dcptranslationmanager.h"
#include "dcptranslationmanager_p.h"

#include <MLocale>
#include <MApplication>
#include "dcpdebug.h"
#include "dcpappletmanager.h"
#include "dcpappletmetadata.h"

#include "dcpdebug.h"

#include <QHash>

/* extremal value to differentiate the fact when retranslate was never
 * run before. (Becase the loaded language gconf value can also be null or empty
 * in some cases. */
static const QString NO_LANGUAGE_IS_LOADED_YET = "***";

DcpTranslationManager* DcpTranslationManagerPriv::instance = 0;

DcpTranslationManagerPriv::DcpTranslationManagerPriv ():
    filterEvent (true),
    languageItem(new MGConfItem("/meegotouch/i18n/language"))
{
    lastLanguage = languageItem->value().toString();

    MApplication* mApp = MApplication::instance();
    binaryName = mApp->binaryName();
}

DcpTranslationManagerPriv::~DcpTranslationManagerPriv ()
{
    delete languageItem;
}

DcpTranslationManager::DcpTranslationManager (): priv(new DcpTranslationManagerPriv())
{
}

DcpTranslationManager::~DcpTranslationManager()
{
    delete priv;
    DcpTranslationManagerPriv::instance = 0;
}

/*
 * ! \brief copied from widgetsgallery, makes translation reload
 *
 * Please note that I had to add a recursion protection to this function because
 * with the newest libdui (libdui0_0.19.4-2_i386.deb) it fell into endless
 * recursion.
 */
void
DcpTranslationManager::retranslate ()
{
    /*
     * Protection against endless recursion.
     */
    static bool running = false;
    if (running)
        return;
    running = true;

    /*
     * Protection against loading all applet translations multiple times
     */
    QString language = priv->languageItem->value().toString();
    if (priv->lastLanguage == language) {
        running = false;
        return;
    }

    priv->loadedTranslations.clear();

    MLocale locale(language);

    QString binaryName = priv->binaryName;
    DCP_DEBUG("%s %s", qPrintable(binaryName), qPrintable(language));

    // install translation
    locale.installTrCatalog("common");
    locale.installTrCatalog(binaryName);

    // load the translations of the active applets:
    DcpAppletManager *db = DcpAppletManager::instance();
    if (db->isMetadataLoaded()) {
        foreach (DcpAppletMetadata* metadata, db->list()) {
            if (metadata->isActive()) {
                loadAppletTranslation (locale, metadata);
            }
        }
    }

    // we enable one retramslateEvent pass, see filterEvent()
    priv->filterEvent = false;
    MLocale::setDefault(locale);

    running = false;
    priv->lastLanguage = language;
}

/** Loads the translation for the applet into locale
 *
 * @returns true if the locale was modified, false otherwise.
 *
 * Note that false return value does not indicate an error,
 * it is also possible that the translation was already loaded,
 * so no modification was necessery.
 */
bool
DcpTranslationManager::loadAppletTranslation (
        MLocale                &locale,
        const DcpAppletMetadata  *metadata)
{
    dcp_failfunc_unless (metadata, false);

    QStringList catalogList = metadata->translationCatalogs();

    return loadTranslations (locale, catalogList);
}

bool DcpTranslationManager::loadTranslations (MLocale& locale,
                                        const QStringList& catalogList)
{
    bool hasChanged = false;

    foreach (QString catalog, catalogList) {
        if (catalog.isEmpty()) continue;

        /* Do not load the translation if it is already loaded
         */
        if (priv->loadedTranslations.contains(catalog)) continue;

        locale.installTrCatalog(catalog); // install translation, if any
        hasChanged = true;

        // mark it as loaded:
        priv->loadedTranslations.insert(catalog);
    }

    return hasChanged;
}

void
DcpTranslationManager::ensureTranslationsAreLoaded(const DcpAppletMetadataList& list)
{
    MLocale locale;
    bool modified = false;
    foreach (DcpAppletMetadata* metadata, list) {
        if (loadAppletTranslation(locale, metadata)) {
            modified = true;
        }
    }

    /*
     * we only set the locale if it was modified, to avoid unnecessery
     * retranslateUi calls
     */
    if (modified) {
        MLocale::setDefault(locale);
    }
}

void
DcpTranslationManager::ensureTranslationLoaded(DcpAppletMetadata* metadata)
{
    MLocale locale;

    /*
     * we only set the locale if it was modified, to avoid unnecessery
     * retranslateUi calls
     */
    if (loadAppletTranslation(locale, metadata)) {
        MLocale::setDefault(locale);
    }
}

void
DcpTranslationManager::ensureTranslationsAreLoaded (const QStringList& catalogs)
{
    MLocale locale;
    /*
     * we only set the locale if it was modified, to avoid unnecessery
     * retranslateUi calls
     */
    if (loadTranslations(locale, catalogs)) {
        MLocale::setDefault(locale);
    }
}


/*!
* The retranslator is in compatibility mode if you call it with its constructor,
* so as not to cause problems with suw or other program, which are also using the
* retranslator. In compatibility mode retranslator behaves like before:
* it reloads the translations for all applets, which are in the db.
*
* If you call it trough instance() it will not be in compatibility mode,
* which means it only reloads the translations
* for the active plugins, see DcpAppletMetadata::isActive(), and apps have
* to call ensureLoaded functions to load the translations for the actives.
*/
DcpTranslationManager*
DcpTranslationManager::instance()
{
    if (!DcpTranslationManagerPriv::instance)
    {
        DcpTranslationManagerPriv::instance = new DcpTranslationManager();
    }
    return DcpTranslationManagerPriv::instance;
}


void
DcpTranslationManager::setMainCatalogName (const QString& catalogName)
{
    priv->binaryName = catalogName;
    MLocale loc;
    loc.installTrCatalog (catalogName);
    MLocale::setDefault (loc);
}


/*! Filters out unnecessery LanguageChange events
 *
 * If installed on a QApplication it will filter out all LanguageChange events
 * which are not intentional in the sence that they are not caused by the
 * #retranslateUi. This can cause problems of course, so dont use it ;)
 */
bool
DcpTranslationManager::eventFilter(QObject *obj, QEvent *event)
{
    /*
     * This is an optimization, so that LanguageChange event only occur
     * when needed (heavy operation, goes through all visible and nonvisible
     * widgets).
     *
     * The event is only needed when the current locale changes, so
     * we eat it every time an applet (or controlpanel) calls
     * MLocale::setDefault to load a translation. We can do it because
     * the widgets for which the translation will be used get created
     * after the catalog loading, both for
     * - brief view
     * - and applet view
     *
     * One case is there, on the fly translation change, which will need
     * the event so DcpTranslationManager::retranslate() disables the filtering
     * for one time through priv->filterEvent
     *
     * Applications other than controlpanel do not install this as eventfilter,
     * or they are warned at least.
     */
    if (event->type() == QEvent::LanguageChange) {
        if (priv->filterEvent) {
            qDebug ("Filtered out a languageChange event");
            return true;
        } else {
            // lets one event pass out
            qDebug ("Let one languageChange event pass");
            priv->filterEvent = true;
        }
    }
    return QObject::eventFilter (obj, event);
}

/*!
 * Destroys the instance if any.
 */
void DcpTranslationManager::destroy()
{
    if (DcpTranslationManagerPriv::instance) {
        delete DcpTranslationManagerPriv::instance;
        DcpTranslationManagerPriv::instance = 0;
    }
}


