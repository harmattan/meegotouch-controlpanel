# Build configuration

QMAKE_CXXFLAGS_RELEASE += -g
QMAKE_RPATH = -Wl
    DCP_BUILD_PARTS = lib controlpanel tests
    DCP_BUILD_FEATURES = debug

# Directories
     DCP_PREFIX = /usr
     DCP_INSTALL_LIB = $$DCP_PREFIX/lib
     DCP_INSTALL_HEADERS = $$DCP_PREFIX/include/duicontrolpanel
     DCP_THEME_DIR = $$DCP_PREFIX/share/duicontrolpanel/themes
     DCP_CSS_DIR = $$DCP_THEME_DIR/style/
     DCP_DESKTOP_DIR = $$DCP_PREFIX/lib/duicontrolpanel
     DCP_APPLET_DIR = $$DCP_PREFIX/lib/duicontrolpanel/applets
     DCP_UIDESC_DIR = $$DCP_PREFIX/lib/duicontrolpanel/uidescriptions
     DCP_TRANSLATIONS_DIR = $$DCP_PREFIX/share/l10n/dui

# defines for directories, they work cross-platform like this
{
    DEFINES += PREFIX=\\\"\"$$DCP_PREFIX\"\\\"
    # THEMEDIR determines the location of the theme
    DEFINES += THEMEDIR=\\\"\"$$DCP_THEME_DIR\"\\\"
    
    DEFINES += CSSDIR=\\\"\"$$DCP_CSS_DIR\"\\\"

    # APPLET_LIBS determines the location where all applet binaries are
    DEFINES += APPLET_LIBS=\\\"\"$$DCP_APPLET_DIR\"\\\"

    # APPLET_DATA determines where the .desktop files are located
    DEFINES += DESKTOP_DIR=\\\"\"$$DCP_DESKTOP_DIR\"\\\"
    
    DEFINES += TRANSLATIONS_DIR=\\\"\"$$DCP_TRANSLATIONS_DIR\"\\\"

}

