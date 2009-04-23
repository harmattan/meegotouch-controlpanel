#include "dcplanguageconf.h"

namespace LanguageKey
{
    const QString InputMethod ="Maemo/DuiInputMethod/";
    const QString Languages = InputMethod + "language/";
    const QString CurrentLanguage = Languages + "current";
    const QString KeyboardLayout = InputMethod + "keyboard-layout/";
    const QString CurrentKeyboardLayout = Languages + "current";
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
    setDisplayLanguage("English GB");
    addKeyboardLanguage(displayLanguage());
    addKeyboardLanguage("Suomi");
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
    return m_KeyboardLanguages;
}

QString 
DcpLanguageConf::keyboardLanguagesAsText()
{
    return m_KeyboardLanguages.join(", ");
}

void 
DcpLanguageConf::addKeyboardLanguage(QString language)
{
    m_KeyboardLanguages.append(language);
}

void 
DcpLanguageConf::removeKeyboardLanguage(QString language)
{
    m_KeyboardLanguages.removeOne(language);
}

void
DcpLanguageConf::setKeyboardLanguage(QStringList languages)
{
    m_KeyboardLanguages = languages;
}

int 
DcpLanguageConf::keyboardLanguagesNumber()
{
    return m_KeyboardLanguages.count();
}

QStringList
DcpLanguageConf::availableInputLanguages(){

}

QStringList 
DcpLanguageConf::availableKeyboardLanguages()
{

};
