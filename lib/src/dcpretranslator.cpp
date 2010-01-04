#include "dcpretranslator.h"
#include <DuiLocale>
#include <QtDebug>
#include <DuiGConfItem>
#include <DuiApplication>


//! \brief copied from widgetsgallery, makes translation reload
void 
DcpRetranslator::retranslate()
{
    DuiApplication* duiApp = DuiApplication::instance();
    DuiGConfItem languageItem("/Dui/i18n/Language");
    QString language = languageItem.value().toString();
    DuiLocale locale(language);

    QString binaryName = duiApp->binaryName();
    qDebug() << __PRETTY_FUNCTION__ << binaryName << language;

    // install engineering english
    locale.installTrCatalog(binaryName+".qm");

    // install real translation
    locale.installTrCatalog(binaryName);

    DuiLocale::setDefault(locale);
}


