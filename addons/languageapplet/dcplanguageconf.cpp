#include "dcplanguageconf.h"
const QString DCPLANGUAGEDIR = "/system/language/";
DcpLanguageConf *DcpLanguageConf::sm_Instance = NULL;

DcpLanguageConf*
DcpLanguageConf::instance()
{
    if (!sm_Instance)
        sm_Instance = new DcpLanguageConf();

    return sm_Instance;
}

DcpLanguageConf::DcpLanguageConf() : DuiConf()
{
//    addDir(DCPLANGUAGECONFDIR);
    m_DisplayLanguage = "English GB";
    addKeyboardLanguage(m_DisplayLanguage);
    addKeyboardLanguage("Suomi");
    addKeyboardLanguage("Whatever");
    removeKeyboardLanguage("Whatever");

}

DcpLanguageConf::~DcpLanguageConf()
{
    if (sm_Instance)
        delete sm_Instance;
}

QString 
DcpLanguageConf::displayLanguage()
{
    return m_DisplayLanguage;
}

void 
DcpLanguageConf::setDisplayLanguage(QString displayLanguage)
{
    m_DisplayLanguage = displayLanguage;
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

QStringList 
DcpLanguageConf::languages()
{
    return m_Languages;
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
    m_KeyboardLanguages.count() + 1;
}
