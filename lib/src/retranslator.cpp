#include "retranslator.h"
#include <DuiLocale>
#include <QtDebug>
#include <DuiGConfItem>

// copied from widgetsgallery, makes translation reload automatically
void 
Retranslator::retranslate()
{
    qDebug() << __PRETTY_FUNCTION__;
    DuiGConfItem languageItem("/Dui/i18n/Language");
    QString language = languageItem.value().toString();
    DuiLocale locale(language);
    locale.installCategoryCatalog(DuiLocale::DuiLcMessages, "duicontrolpanel");
    DuiLocale::setDefault(locale);
}


