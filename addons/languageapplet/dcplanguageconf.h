#ifndef DCPLANGUAGECONF_H
#define DCPLANGUAGECONF_H
#include "duiconf.h"
#include <QString>
#include <QStringList>
class DcpLanguageConf : public DuiConf
{
public:
    static DcpLanguageConf *instance();
    ~DcpLanguageConf();
    QString displayLanguage();
    void setDisplayLanguage(QString displayLanguage);
    QStringList keyboardLanguages();
    QString keyboardLanguagesAsText();
    int keyboardLanguagesNumber();
    QStringList languages();
    void addKeyboardLanguage(QString language);
    void removeKeyboardLanguage(QString language);
    void setKeyboardLanguage(QStringList languages);
protected:
    DcpLanguageConf();
private:
    static DcpLanguageConf *sm_Instance;
    // This will come from GConf. 
    // Storing in private member is for test only!
    QString m_DisplayLanguage;
    QStringList m_KeyboardLanguages;
    QStringList m_Languages;
};
#endif // DCPLANGUAGECONF_H