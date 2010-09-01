#include <MTheme>
#include "mtheme-fake.h"

static MTheme* inst = 0;
static QSet<QString> loadedThemes;

MTheme::MTheme(const QString &, const QString &, ThemeService ): d_ptr(0)
{
}


MTheme * MTheme::instance()
{
    if (!inst) inst = new MTheme ("x");
    return inst;
}

bool MTheme::loadCSS(const QString &filename, InsertMode)
{
    loadedThemes.insert (filename);
    return true;
}

QString MTheme::currentTheme ()
{
    return "x";
}

QSet<QString>& mtheme_loadedThemes()
{
    return loadedThemes;
}

