/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */
#include "dcpretranslator.h"

#include <MLocale>
#include <MGConfItem>
#include <MApplication>
#include "dcpdebug.h"
#include "dcpappletdb.h"
#include "dcpappletmetadata.h"

#include "dcpdebug.h"

#include <QHash>

class DcpRetranslatorPriv {
public:
    DcpRetranslatorPriv();

    QString lastLanguage;
    QSet<QString> loadedTranslations;
    static DcpRetranslator* instance;
    static bool compatibleMode;
};

DcpRetranslator* DcpRetranslatorPriv::instance = 0;
bool DcpRetranslatorPriv::compatibleMode = true;

DcpRetranslatorPriv::DcpRetranslatorPriv ()
{
/*
 * MGConfItem languageItem("/meegotouch/i18n/language");
 * lastLanguage = languageItem.value().toString();
 */
}

DcpRetranslator::DcpRetranslator (): priv(new DcpRetranslatorPriv())
{
    if (DcpRetranslatorPriv::compatibleMode) {
        // load the translations of the applets:
        DcpAppletDb *db = DcpAppletDb::instance();
        ensureTranslationsAreLoaded(db->list());
    }
}

/*
 * ! \brief copied from widgetsgallery, makes translation reload
 *
 * Please note that I had to add a recursion protection to this function because
 * with the newest libdui (libdui0_0.19.4-2_i386.deb) it fell into endless
 * recursion.
 */
void
DcpRetranslator::retranslate ()
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
    MGConfItem languageItem("/meegotouch/i18n/Language");
    QString language = languageItem.value().toString();
    if (priv->lastLanguage == language)
        return;

    priv->loadedTranslations.clear();

    MApplication* mApp = MApplication::instance();
    MLocale locale(language);

    QString binaryName = mApp->binaryName();
    DCP_DEBUG("%s %s", qPrintable(binaryName), qPrintable(language));

    // install engineering english
    locale.installTrCatalog("libdui.qm");
    locale.installTrCatalog(binaryName + ".qm");
    // install real translation
    locale.installTrCatalog("libdui");
    locale.installTrCatalog("common");
    locale.installTrCatalog(binaryName);

    // load the translations of the active applets:
    DcpAppletDb *db = DcpAppletDb::instance();
    foreach (DcpAppletMetadata* metadata, db->list()) {
        if (metadata->isActive() || DcpRetranslatorPriv::compatibleMode) {
            loadAppletTranslation (locale, metadata);
        }
    }

    MLocale::setDefault(locale);

    running = false;
    priv->lastLanguage = language;
}

void
DcpRetranslator::loadAppletTranslation (
        MLocale                &locale,
        const DcpAppletMetadata  *metadata)
{
    Q_ASSERT(metadata);

    QString catalog = metadata->translationCatalog();
    if (catalog.isEmpty() ) return;

    /* Do not load the translation if it is already loaded
     * In compatible mode (for suw), it is skipped.
     */
    if (!DcpRetranslatorPriv::compatibleMode &&
        priv->loadedTranslations.contains(catalog)) return;

    locale.installTrCatalog(catalog + ".qm"); // install engineering english
    locale.installTrCatalog(catalog); // install real translation, if any

    // mark it as loaded:
    priv->loadedTranslations.insert(catalog);

    DCP_DEBUG ("Translation %s loaded.", qPrintable(catalog));
}

void
DcpRetranslator::ensureTranslationsAreLoaded(const DcpAppletMetadataList& list)
{
    MLocale locale;
    foreach (DcpAppletMetadata* metadata, list) {
        loadAppletTranslation(locale, metadata);
    }
    MLocale::setDefault(locale);
}

void
DcpRetranslator::ensureTranslationLoaded(DcpAppletMetadata* metadata)
{
    MLocale locale;
    loadAppletTranslation(locale, metadata);
    MLocale::setDefault(locale);
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
DcpRetranslator*
DcpRetranslator::instance()
{
    if (DcpRetranslatorPriv::instance == NULL)
    {
        DcpRetranslatorPriv::compatibleMode = false;
        DcpRetranslatorPriv::instance = new DcpRetranslator();
    }
    return DcpRetranslatorPriv::instance;
}

