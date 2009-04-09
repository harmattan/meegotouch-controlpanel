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
    m_DisplayLanguage = "en_GB";
//    addDir(DCPLANGUAGECONFDIR);
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
DcpLanguageConf::keyboardLanguage()
{
    return QStringList();
}

void 
DcpLanguageConf::setKeyboardLanguage()
{
}
