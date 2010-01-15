#include "dcpretranslator.h"

#include <DuiLocale>
#include <QtDebug>
#include <DuiGConfItem>
#include <DuiApplication>
#include <QDir>
#include <QStringList>

DcpRetranslator::DcpRetranslator()
{
    // install translations for the applets if any:
    DuiLocale locale;
    DcpRetranslator::installAppletTranslations(locale);
    DuiLocale::setDefault (locale);
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
    qDebug() << __PRETTY_FUNCTION__ << binaryName << language;

    // install engineering english
    locale.installTrCatalog(binaryName + ".qm");
    // install real translation
    locale.installTrCatalog(binaryName);

    // install translation files for the applets
    installAppletTranslations(locale);

    DuiLocale::setDefault(locale);
}

void
DcpRetranslator::installAppletTranslations(DuiLocale& locale)
{
    static const QString pluginFilePrefix = "duicontrolpanel-";
    QDir localeDir(TRANSLATIONS_DIR);
    QStringList fileNames = 
        localeDir.entryList(QStringList(pluginFilePrefix + "*.qm"),
                            QDir::Files | QDir::Readable,
                            QDir::Name);
    QString translationName = "/";
    foreach (QString fileName, fileNames) {
        // do not load the same translation multiple times
        // (fileNames are sorted)
        if (fileName.startsWith(translationName)) continue;

        int chopIndex = fileName.indexOf('_');
        if (chopIndex == -1)
         chopIndex = fileName.indexOf('.'); // is an engineering english
                                            // translation
        if (chopIndex == -1) continue; // strange error

        translationName = fileName;
        translationName.truncate(chopIndex);
        qDebug() << "Installing translation for" << translationName;

        // install engineering english
        locale.installTrCatalog(translationName + ".qm");
        // install real translation
        locale.installTrCatalog(translationName);
    }
}

