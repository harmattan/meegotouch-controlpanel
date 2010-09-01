#ifndef APPLETTHEMES_H
#define APPLETTHEMES_H

#include <QObject>
#include <QSet>
#include <QString>

class AppletThemes: public QObject
{
    Q_OBJECT

public:
    ~AppletThemes();
    static AppletThemes* instance();
    void ensureCssLoaded (const QString& appletName);

protected slots:
    void onThemeIsChanging();

protected:
    AppletThemes();

    QSet<QString> m_LoadedThemes;
    static AppletThemes* sm_Instance;

    friend class Ut_AppletThemes;
};


#endif // APPLETTHEMES_H
