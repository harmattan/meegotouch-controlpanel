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
    static QString fullName(QString lang);
protected:
    DcpLanguageConf();
    QStringList availableLanguages(QString key);
    QStringList defaultLanguages();
private:
    static DcpLanguageConf *sm_Instance;
    QSettings m_Settings;
};
#endif // DCPLANGUAGECONF_H
