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
    qDebug() << __PRETTY_FUNCTION__ << duiApp->binaryName();
    DuiGConfItem languageItem("/Dui/i18n/Language");
    QString language = languageItem.value().toString();
    DuiLocale locale(language);
    locale.installCategoryCatalog(DuiLocale::DuiLcMessages, duiApp->binaryName());
    DuiLocale::setDefault(locale);
}


