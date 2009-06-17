#include "mainwindow.h"

#include <DuiApplication>
#include <DuiLocale>
#include <QtDebug>
#include <duitheme.h>


int main(int argc, char *argv[])
{
    DuiApplication* app = new DuiApplication(argc, argv);

//    DuiTheme::instance()->changeTheme("common");
//    DuiTheme::loadCSS("duicontrolpanel.css");
/*    DuiTheme::instance()->clearPixmapDirectories();
    DuiTheme::instance()->addPixmapDirectory("/usr/share/themes/dui/duicontrolpanel", true);*/

    DuiLocale locale;
    locale.addTranslationPath("./ts");
    locale.addTranslationPath("/usr/share/dui/l10n");
    locale.installCategoryCatalog(DuiLocale::DuiLcMessages, "duicontrolpanel");
    qDebug() << trid("dcp_test", "Teesttt");

    MainWindow* win = new MainWindow();

    win->show();

    return app->exec();
}

