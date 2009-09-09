
#include <DuiApplication>
#include <DuiLocale>
#include <QtDebug>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    DuiApplication app(argc, argv);

    DuiLocale locale;
    locale.addTranslationPath("./ts");
    locale.addTranslationPath(TRANSLATIONS_DIR);
    locale.installCategoryCatalog(DuiLocale::DuiLcMessages, "duicontrolpanel");

    MainWindow win;
    win.show();
    return app.exec();
}

