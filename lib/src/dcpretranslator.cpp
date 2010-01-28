#include "dcpretranslator.h"

#include <DuiLocale>
#include <DuiGConfItem>
#include <DuiApplication>
#include "dcpdebug.h"
#include "dcpappletdb.h"
#include "dcpappletmetadata.h"

DcpRetranslator::DcpRetranslator()
{
    // at startup load translations for the applets:
    DuiLocale locale;
    loadAppletTranslations(locale);
    DuiLocale::setDefault(locale);
}

//! \brief copied from widgetsgallery, makes translation reload
void
DcpRetranslator::retranslate()
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
DcpRetranslator::loadAppletTranslations (DuiLocale& locale)
{
    DcpAppletDb* db = DcpAppletDb::instance();
    foreach (DcpAppletMetadata* metadata, db->list()) {
        loadAppletTranslation (locale, metadata);
    }
}

void
DcpRetranslator::loadAppletTranslation (DuiLocale& locale,
                                      const DcpAppletMetadata* metadata)
{
    Q_ASSERT(metadata);
    QString catalog = metadata->translationCatalog();
    if (catalog.isEmpty()) return;

    locale.installTrCatalog(catalog + ".qm"); // install engineering english
    locale.installTrCatalog(catalog); // install real translation, if any
    DCP_DEBUG("Translation %s loaded.", qPrintable(catalog));
}

