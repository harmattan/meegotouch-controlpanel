#ifndef DCPLANGUAGECONF_H
#define DCPLANGUAGECONF_H
#include <QString>
#include <QSettings>
#include <QStringList>
class DuiConfItem;
class DcpLanguageConf
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
    Q_DISABLE_COPY(DcpLanguageConf)
    static DcpLanguageConf *sm_Instance;
    QSettings m_Settings;
    DuiConfItem *m_DisplayLanguageItem;
};
#endif // DCPLANGUAGECONF_H

