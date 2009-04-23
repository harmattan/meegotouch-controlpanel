#include "dcplanguageconf.h"

namespace LanguageKey
{
    const QString InputMethod ="Maemo/DuiInputMethod/";
    const QString Languages = InputMethod + "language/";
    const QString CurrentLanguage = Languages + "current";
    const QString KeyboardLayout = InputMethod + "keyboard-layout/";
    const QString CurrentKeyboardLayout = KeyboardLayout + "current";
};

DcpLanguageConf *DcpLanguageConf::sm_Instance = NULL;


DcpLanguageConf*
DcpLanguageConf::instance()
{
    if (!sm_Instance)
        sm_Instance = new DcpLanguageConf();

    return sm_Instance;
}

DcpLanguageConf::DcpLanguageConf() : DuiConf(),
                             m_Settings("Maemo", "DuiControlPanel")
{
    if (!m_Settings.contains(LanguageKey::CurrentLanguage))
        setDisplayLanguage("English GB");
    
    if (!m_Settings.contains(LanguageKey::CurrentKeyboardLayout))
      {
        addKeyboardLanguage(displayLanguage());
        addKeyboardLanguage("Suomi");
      }
}

DcpLanguageConf::~DcpLanguageConf()
{
    if (sm_Instance)
        delete sm_Instance;
}

QString 
DcpLanguageConf::displayLanguage()
{
    return m_Settings.value(LanguageKey::CurrentLanguage).toString();
}

void 
DcpLanguageConf::setDisplayLanguage(QString displayLanguage)
{
    m_Settings.setValue(LanguageKey::CurrentLanguage, displayLanguage);
}

QStringList 
DcpLanguageConf::keyboardLanguages()
{
    return m_Settings.value(LanguageKey::CurrentKeyboardLayout).toStringList();
}

QString 
DcpLanguageConf::keyboardLanguagesAsText()
{
    return keyboardLanguages().join(", ");
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
    return defaultLanguages();
}

QStringList 
DcpLanguageConf::availableKeyboardLanguages()
{
    return defaultLanguages();
};

QStringList 
DcpLanguageConf::defaultLanguages()
{

    QString rushian = 
        QString("P%1cc").arg(QChar(0x0443)) + QChar(0x043A) + QChar(0x0438) + QChar(0x0439); 

    QStringList languageList;
    languageList << "Dansk" << "Deutsch" << "English GB" << "English US" 
            << QString("Fran%1ais (Canada)").arg(QChar(0x00e7)) 
            << QString("Fran%1ais (France)").arg(QChar(0x00e7)) 
            << "Italian"
            << QString("LA Espa%1ol").arg(QChar(0x00f1)) 
            << "Nederlands" << "Norks" 
            << QString("Portugu%1s").arg(QChar(0x00ea))
            << QString("Portugu%1s BR").arg(QChar(0x00ea)) 
            << rushian << "Suomi";
    return languageList;
}
