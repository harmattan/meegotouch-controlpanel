#include "dcplanguageconf.h"
#include <duilocale.h>
#include <duivaluespace.h>
namespace LanguageKey
{
    const QString InputMethod ="Maemo/DuiInputMethod/";
    const QString Languages = InputMethod + "language/";
    const QString CurrentLanguage = Languages + "current";
    const QString KeyboardLayout = InputMethod + "keyboard-layout/";
    const QString CurrentKeyboardLayout = KeyboardLayout + "current";
    const QString SettingsLanguage("Dui.i18n.Language");
    const QString SettingsCountry("Dui.i18n.Country");

};

DcpLanguageConf *DcpLanguageConf::sm_Instance = NULL;


DcpLanguageConf*
DcpLanguageConf::instance()
{
    if (!sm_Instance)
        sm_Instance = new DcpLanguageConf();

    return sm_Instance;
}

DcpLanguageConf::DcpLanguageConf() : 
                             m_Settings("Maemo", "DuiControlPanel")
{
    
    m_DisplayLanguageItem = new DuiConfItem(LanguageKey::SettingsLanguage);
    
    if (!m_Settings.contains(LanguageKey::CurrentKeyboardLayout))
      {
        addKeyboardLanguage(displayLanguage());
      }
}

DcpLanguageConf::~DcpLanguageConf()
{
    if (sm_Instance)
        delete sm_Instance;
    delete m_DisplayLanguageItem;
}

QString 
DcpLanguageConf::displayLanguage()
{
    
    return m_DisplayLanguageItem->value().toString();
    //return m_Settings.value(LanguageKey::CurrentLanguage).toString();
}

void 
DcpLanguageConf::setDisplayLanguage(QString displayLanguage)
{
    
    m_DisplayLanguageItem->set(displayLanguage);
    //m_Settings.setValue(LanguageKey::CurrentLanguage, displayLanguage);
}

QStringList 
DcpLanguageConf::keyboardLanguages()
{
    return m_Settings.value(LanguageKey::CurrentKeyboardLayout).toStringList();
}

QString 
DcpLanguageConf::keyboardLanguagesAsText()
{
    QStringList list;
    foreach(QString langCode, keyboardLanguages())
       list.append(fullName(langCode)); 
    return list.join(", ");
}

void 
DcpLanguageConf::addKeyboardLanguage(QString language)
{
    QStringList list = keyboardLanguages();
    list.append(language);
    setKeyboardLanguages(list);
}

void 
DcpLanguageConf::removeKeyboardLanguage(QString language)
{
    QStringList list = keyboardLanguages();
    list.removeOne(language);
    setKeyboardLanguages(list);
}

void
DcpLanguageConf::setKeyboardLanguages(QStringList languages)
{
    m_Settings.setValue(LanguageKey::CurrentKeyboardLayout, languages);
}

int 
DcpLanguageConf::keyboardLanguagesNumber()
{
    return keyboardLanguages().count();
}

QStringList
DcpLanguageConf::availableInputLanguages()
{
    return availableLanguages(LanguageKey::Languages);

}

QStringList 
DcpLanguageConf::availableKeyboardLanguages()
{
    return availableLanguages(LanguageKey::KeyboardLayout);
};

QStringList
DcpLanguageConf::availableLanguages(QString key)
{
    m_Settings.beginGroup(key);
    QStringList languages;
    foreach (QString langKey, m_Settings.childKeys()) {
        bool ok;
        langKey.toInt(&ok);
        if (ok)
            languages.append(m_Settings.value(langKey).toString());
    }
    m_Settings.endGroup();
    
    if (languages.isEmpty())
        languages = defaultLanguages();
   
    return languages;
;
}
QString
DcpLanguageConf::fullName(QString lang)
{
    DuiLocale locale(lang);
    if (lang.isEmpty())
        return "";
    QString result = locale.languageEndonym();
    if (locale.language() != locale.country().toLower())
        result += " (" + locale.countryEndonym() + ")";
   	result[0]=result.at(0).toUpper();
    return result; 
}


QStringList 
DcpLanguageConf::defaultLanguages()
{

    QStringList languageList;
    languageList << "da_DA" << "de_DE" << "en_GB" << "en_US" 
     << "fr_CA" << "fr_FR" << "it_IT" << "es_ES" << "nl_NL" << "no_NO"
     << "pt_PT" << "pt_BR" << "ru_RU" << "fi_FI";
    return languageList;
}
