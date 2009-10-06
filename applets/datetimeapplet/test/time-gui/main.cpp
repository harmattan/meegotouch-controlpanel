
#include <DuiApplicationWindow>
#include <DuiApplication>
#include <DuiLocale>

#include "page.h"

int main(int argc, char *argv[])
{
    DuiApplication app(argc, argv);
    app.setAnimator(0);

    TestPage *page = new TestPage();

    DuiApplicationWindow win;
    page->appear();
    win.show();

    return app.exec();
}

