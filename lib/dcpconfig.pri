# Build configuration

QMAKE_CXXFLAGS_RELEASE += -g
QMAKE_RPATH = -Wl
    DCP_BUILD_PARTS = lib controlpanel tests
    DCP_BUILD_FEATURES = debug

# Directories
     DCP_PREFIX = /usr
     DCP_INSTALL_LIB = $$DCP_PREFIX/lib
     DCP_INSTALL_HEADERS = $$DCP_PREFIX/include/duicontrolpanel
     DCP_THEME_DIR = $$DCP_PREFIX/share/themes/base/dui/duicontrolpanel
     DCP_CSS_DIR = $$DCP_THEME_DIR/style/
     DCP_DESKTOP_DIR = $$DCP_PREFIX/lib/duicontrolpanel
     DCP_APPLET_DIR = $$DCP_PREFIX/lib/duicontrolpanel/applets
     DCP_UIDESC_DIR = $$DCP_PREFIX/lib/duicontrolpanel/uidescriptions
     DCP_TRANSLATIONS_DIR = $$DCP_PREFIX/share/l10n/dui

