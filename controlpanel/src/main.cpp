
#include <DuiApplication>
#include <DuiLocale>
#include <QtDebug>

#include "mainwindow.h"
#include "service/duicontrolpanelservice.h"

int main(int argc, char *argv[])
{
    DuiControlPanelService* service = new DuiControlPanelService();
    DuiApplication app(argc, argv);

    DuiLocale locale;
    locale.addTranslationPath("./ts");
    locale.addTranslationPath(TRANSLATIONS_DIR);
    locale.installCategoryCatalog(DuiLocale::DuiLcMessages, "duicontrolpanel");

    MainWindow win;
    service->createStartPage();
    win.show();

    return app.exec();
}

