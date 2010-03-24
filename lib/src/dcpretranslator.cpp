/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */
#include "dcpretranslator.h"

#include <DuiLocale>
#include <DuiGConfItem>
#include <DuiApplication>
#include "dcpdebug.h"
#include "dcpappletdb.h"
#include "dcpappletmetadata.h"

#include "dcpdebug.h"

#include <QHash>

class DcpRetranslatorPriv {
public:
    DcpRetranslatorPriv();

    QString lastLanguage;
    QSet<const DcpAppletMetadata*> loadedTranslations; // FIXME: this can be a metadata attribute XXX
    static DcpRetranslator* instance;
};

DcpRetranslator* DcpRetranslatorPriv::instance = 0;

DcpRetranslatorPriv::DcpRetranslatorPriv ()
{
    DuiGConfItem languageItem("/Dui/i18n/Language");
    lastLanguage = languageItem.value().toString();
}

DcpRetranslator::DcpRetranslator (): priv(new DcpRetranslatorPriv())
{
    /*
     * Please note that we are not loading the applet translations automatically
     * any more, for it forced the applet database to be loaded early. The
     * applet database will load the translations immediatelly after the 
     * database loaded.
     */

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
    DuiGConfItem languageItem("/Dui/i18n/Language");
    QString language = languageItem.value().toString();
    if (priv->lastLanguage == language)
        return;

    priv->loadedTranslations.clear();

    DuiApplication* duiApp = DuiApplication::instance();
    DuiLocale locale(language);

    QString binaryName = duiApp->binaryName();
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
        if (metadata->isActive()) {
            loadAppletTranslation (locale, metadata);
        }
    }

    DuiLocale::setDefault(locale);

    running = false;
    priv->lastLanguage = language;
}

void
DcpRetranslator::loadAppletTranslation (
        DuiLocale                &locale,
        const DcpAppletMetadata  *metadata)
{
    Q_ASSERT(metadata);
    qDebug("XXX trial %s",qPrintable(metadata->name()));

    // Do not load the translation if it is already loaded
    if (priv->loadedTranslations.contains(metadata)) return;

    QString catalog = metadata->translationCatalog();
    if (catalog.isEmpty() ) return;

    locale.installTrCatalog(catalog + ".qm"); // install engineering english
    locale.installTrCatalog(catalog); // install real translation, if any

    // mark it as loaded:
    priv->loadedTranslations.insert(metadata);

//    DCP_DEBUG ("Translation %s loaded.", qPrintable(catalog));
    qDebug("XXX Translation %s loaded.\n", qPrintable(catalog));
}

void
DcpRetranslator::ensureTranslationsAreLoaded(const DcpAppletMetadataList& list)
{
    DuiLocale locale;
    foreach (DcpAppletMetadata* metadata, list) {
        loadAppletTranslation(locale, metadata);
    }
    DuiLocale::setDefault(locale);
}

void
DcpRetranslator::ensureTranslationLoaded(DcpAppletMetadata* metadata)
{
    DuiLocale locale;
    loadAppletTranslation(locale, metadata);
    DuiLocale::setDefault(locale);
}

DcpRetranslator*
DcpRetranslator::instance()
{
    if (DcpRetranslatorPriv::instance == NULL) {
        DcpRetranslatorPriv::instance = new DcpRetranslator();
    }
    return DcpRetranslatorPriv::instance;
}

