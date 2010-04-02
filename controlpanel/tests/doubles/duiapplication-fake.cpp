#include <duiapplication.h>
#include "duiapplicationwindow-fake.h"
#include "duiwindow.h"

static DuiApplicationWindow* win = 0;

DuiApplicationWindow * DuiApplication::activeApplicationWindow ()
{
    if (!win) win = new DuiApplicationWindow();
    return win;
}

DuiWindow * DuiApplication::activeWindow ()
{
    return activeApplicationWindow();
}

