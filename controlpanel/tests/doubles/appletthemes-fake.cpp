#include "appletthemes.h"

static AppletThemes* instance = 0;

AppletThemes::~AppletThemes(){}
AppletThemes* AppletThemes::instance()
{
    if (!::instance) {
        ::instance = new AppletThemes();
    }
    return ::instance;
}

void AppletThemes::ensureCssLoaded(const QString&){}
void AppletThemes::onThemeIsChanging(){}
AppletThemes::AppletThemes(){}

