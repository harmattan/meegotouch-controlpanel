#include <mapplication.h>
#include "mapplicationwindow-fake.h"
#include "mwindow.h"

static MApplicationWindow* win = 0;

MApplicationWindow * MApplication::activeApplicationWindow ()
{
    if (!win) win = new MApplicationWindow();
    return win;
}

MWindow * MApplication::activeWindow ()
{
    return activeApplicationWindow();
}

