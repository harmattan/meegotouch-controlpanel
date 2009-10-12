#include "mainwindow.h"
#include "service/duicontrolpanelservice.h"

#include <DuiApplication>
#include <DuiLocale>
#include <QtDebug>
#include <stdio.h>
#include <stdlib.h>

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

int main(int argc, char *argv[])
{
    qInstallMsgHandler(dcpMsg);

    DuiControlPanelService* service = new DuiControlPanelService();

    DuiApplication app(argc, argv);
    app.setAnimator(0);

    DuiLocale locale;
    locale.addTranslationPath("./ts");
    locale.addTranslationPath(TRANSLATIONS_DIR);
    locale.installCategoryCatalog(DuiLocale::DuiLcMessages, "duicontrolpanel");

    MainWindow win;
    service->createStartPage();
    win.show();

    return app.exec();
}

