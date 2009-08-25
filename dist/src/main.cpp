
#include <DuiApplication>
#include <DuiLocale>
#include <QtDebug>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    DuiApplication app(argc, argv);

    DuiLocale locale;
    locale.addTranslationPath("./ts");
    locale.addTranslationPath("/usr/share/dui/l10n");
    locale.installCategoryCatalog(DuiLocale::DuiLcMessages, "duicontrolpanel");

    MainWindow win;
    win.show();
    return app.exec();
}

