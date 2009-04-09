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
    QStringList keyboardLanguage();
    QStringList languages();
    void setKeyboardLanguage();
protected:
    DcpLanguageConf();
private:
    static DcpLanguageConf *sm_Instance;
    // This will come from GConf. 
    // Storing in private member is for test only!
    QString m_DisplayLanguage;
};
#endif // DCPLANGUAGECONF_H
