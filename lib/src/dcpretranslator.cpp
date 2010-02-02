/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */
#include "dcpretranslator.h"

#include <DuiLocale>
#include <DuiGConfItem>
#include <DuiApplication>
#include "dcpdebug.h"
#include "dcpappletdb.h"
#include "dcpappletmetadata.h"

#define DEBUG
#include "dcpdebug.h"

DcpRetranslator::DcpRetranslator ()
{
    // at startup load translations for the applets:
    DuiLocale locale;
    loadAppletTranslations (locale);
    DuiLocale::setDefault (locale);
}


//! \brief copied from widgetsgallery, makes translation reload
void
DcpRetranslator::retranslate ()
{
    DuiApplication* duiApp = DuiApplication::instance();
    DuiGConfItem languageItem("/Dui/i18n/Language");
    QString language = languageItem.value().toString();
    DuiLocale locale(language);

    QString binaryName = duiApp->binaryName();
    DCP_DEBUG("%s: %s %s", __PRETTY_FUNCTION__, qPrintable(binaryName),
              qPrintable(language));

    // install engineering english
    locale.installTrCatalog(binaryName + ".qm");
    // install real translation
    locale.installTrCatalog(binaryName);

    loadAppletTranslations(locale);

    DuiLocale::setDefault(locale);
}

void
DcpRetranslator::loadAppletTranslations (
		DuiLocale& locale)
{
    //Q_ASSERT (false);
    DcpAppletDb *db = DcpAppletDb::instance();
    foreach (DcpAppletMetadata* metadata, db->list()) {
        loadAppletTranslation (locale, metadata);
    }
}

void
DcpRetranslator::loadAppletTranslation (
		DuiLocale                &locale,
		const DcpAppletMetadata  *metadata)
{
    Q_ASSERT(metadata);
    QString catalog = metadata->translationCatalog();
    if (catalog.isEmpty()) return;

    locale.installTrCatalog(catalog + ".qm"); // install engineering english
    locale.installTrCatalog(catalog); // install real translation, if any
    DCP_DEBUG ("Translation %s loaded.", qPrintable(catalog));
}

