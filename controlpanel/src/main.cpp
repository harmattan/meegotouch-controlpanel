#include "mainwindow.h"
#include "service/duicontrolpanelservice.h"

#include <DuiApplication>
#include <DuiLocale>
#include <QtDebug>
#include <stdio.h>
#include <stdlib.h>
#include <DuiGConfItem>

static const char* DEBUG_PREFIX = "(DCP) ";

void dcpMsg(QtMsgType type, const char *msg)
{
    switch (type) {
        case QtDebugMsg:
            fprintf(stderr, "%s%s\n", DEBUG_PREFIX, msg);
            break;
        case QtWarningMsg:
            fprintf(stderr, "%s* %s *\n", DEBUG_PREFIX, msg);
            break;
        case QtCriticalMsg:
            fprintf(stderr, "%s** %s **\n", DEBUG_PREFIX, msg);
            break;
        case QtFatalMsg:
            fprintf(stderr, "Fatal: %s%s\n", DEBUG_PREFIX, msg);
            abort();
    }
}


// copied from widgetsgallery, makes translation reload automatically
class Retranslator : public QObject
{
    Q_OBJECT

public slots:
   void retranslate()
   {
        qDebug() << __PRETTY_FUNCTION__;
        DuiGConfItem languageItem("/Dui/i18n/Language");
        QString language = languageItem.value().toString();
        DuiLocale locale(language);
        locale.installCategoryCatalog(DuiLocale::DuiLcMessages, "duicontrolpanel");
        DuiLocale::setDefault(locale);
   }
};


int main(int argc, char *argv[])
{
    qInstallMsgHandler(dcpMsg);

    DuiControlPanelService* service = new DuiControlPanelService();

    DuiApplication app(argc, argv);
    app.setAnimator(0);

    Retranslator retranslator;
    QObject::connect(&app, SIGNAL(localeSettingsChanged()),
                     &retranslator, SLOT(retranslate()));
 
    MainWindow win;
    service->createStartPage();
    win.show();

    return app.exec();
}

#include "main.moc"

