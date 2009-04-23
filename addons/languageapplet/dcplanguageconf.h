#ifndef DCPLANGUAGECONF_H
#define DCPLANGUAGECONF_H
#include "duiconf.h"
#include <QString>
#include <QSettings>
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
    QStringList availableInputLanguages();
    QStringList availableKeyboardLanguages();
    void addKeyboardLanguage(QString language);
    void removeKeyboardLanguage(QString language);
    void setKeyboardLanguages(QStringList languages);
protected:
    DcpLanguageConf();
    QStringList defaultLanguages();
private:
    static DcpLanguageConf *sm_Instance;
    // This will come from GConf. 
    // Storing in private member is for test only!
//    QStringList m_availableInputLanguages;
//    QStringList m_availableKeyboardLanguages;
    QSettings m_Settings;
};
#endif // DCPLANGUAGECONF_H
