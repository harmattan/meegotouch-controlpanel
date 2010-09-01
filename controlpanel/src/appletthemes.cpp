#include "appletthemes.h"

#include <QFileInfo>
#include <MTheme>

AppletThemes* AppletThemes::sm_Instance = 0;

// default dirs:
static const QString commonCssDir = CSSDIR;
static const QString baseCssDir = "/usr/share/themes/";

AppletThemes::AppletThemes()
{
    // watch for theme change signal:
    connect (MTheme::instance(), SIGNAL (themeIsChanging()),
             this, SLOT(onThemeIsChanging()));
}

AppletThemes::~AppletThemes()
{
    sm_Instance = 0;
}

void AppletThemes::onThemeIsChanging()
{
    // clears the applet name list for which the themes are loaded,
    // so that they will be reloaded when the applet gets openned again
    m_LoadedThemes.clear();
}

inline static void loadCssIfExists (const QString& filePath)
{
    if (QFileInfo(filePath).exists()) {
        qDebug ("%s: loading css %s", Q_FUNC_INFO, qPrintable(filePath));
        MTheme::instance()->loadCSS (filePath);
    } else {
        qDebug ("%s: fortunately the applet did not provide css at %s",
                Q_FUNC_INFO, qPrintable(filePath));
    }
}

/*! @brief Ensures that the css for the lib is loaded.
 *
 * This function will ensure that the .css for the applet got loaded.
 * Css file must be under either
 * - the "base" theme directory, from which every theme inherits
 * - the current theme directory
 */
void AppletThemes::ensureCssLoaded(const QString& libName)
{
    // do not load the theme if it is already loaded:
    if (m_LoadedThemes.contains (libName)) return;
    m_LoadedThemes.insert (libName);

    // compute filename (eg.: dcpskeleton.css for libdcpskeletonapplet.so.0.0.1)
    int start = libName.startsWith ("lib") ? 3 : 0;
    int end = libName.lastIndexOf (".so");
    QString fileName = end > start ? libName.mid (start, end - start) : libName;
    fileName += ".css";

    // check if file exists in common dir:
    loadCssIfExists ( commonCssDir + fileName);

    // check if file exists in theme specific dir:
    loadCssIfExists ( baseCssDir + MTheme::instance()->currentTheme()
                      + "/meegotouch/duicontrolpanel/style/" + fileName);
}

AppletThemes* AppletThemes::instance()
{
    if (! sm_Instance) {
        sm_Instance = new AppletThemes();
    }
    return sm_Instance;
}

