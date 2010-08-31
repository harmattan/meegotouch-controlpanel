#ifndef APPLETTHEMES_H
#define APPLETTHEMES_H

#include <QObject>

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
};


#endif // APPLETTHEMES_H
