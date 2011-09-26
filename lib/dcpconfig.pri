!dcpconfig {
    CONFIG += dcpconfig

isEmpty(HOST_ARCH) {
    HOST_ARCH=$$system(dpkg-architecture -qDEB_HOST_GNU_TYPE || echo meego)
    message("arch $$HOST_ARCH")
    contains(HOST_ARCH,meego){
        CONFIG += meego
        DEFINES += MEEGO
    }

    meego {
        message("MEEGO")
    } else {
        message("NON-MEEGO")
    }
}

# Directories
{
	DCP_PREFIX = /usr
	DCP_INSTALL_LIB = $$DCP_PREFIX/lib
	DCP_INSTALL_HEADERS = $$DCP_PREFIX/include/duicontrolpanel
	DCP_THEME_DIR = $$DCP_PREFIX/share/themes/base/meegotouch/duicontrolpanel
	DCP_CSS_DIR = $$DCP_THEME_DIR/style/
meego {
	DCP_DESKTOP_DIR2 = $$DCP_PREFIX/lib/duicontrolpanel
	DCP_DESKTOP_DIR = $$DCP_PREFIX/share/duicontrolpanel/desktops
} else {
	DCP_DESKTOP_DIR2 = $$DCP_PREFIX/share/duicontrolpanel/desktops
	DCP_DESKTOP_DIR = $$DCP_PREFIX/lib/duicontrolpanel
}
	DCP_APPLET_DIR = $$DCP_PREFIX/lib/duicontrolpanel/applets
	DCP_UIDESC_DIR = $$DCP_PREFIX/share/duicontrolpanel/uidescriptions
	DCP_TRANSLATIONS_DIR = $$DCP_PREFIX/share/l10n/meegotouch
    DCP_CATEGORY_DIR = $$DCP_PREFIX/share/duicontrolpanel/categories
}

# Gconf keys 
{
	DCP_MOSTUSEDCOUNTER_GCONFKEY = /apps/duicontrolpanel/usagecount
}

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
	DEFINES += DESKTOP_DIR2=\\\"\"$$DCP_DESKTOP_DIR2\"\\\"
	DEFINES += DCP_UIDESC_DIR=\\\"\"$$DCP_UIDESC_DIR\"\\\"

	DEFINES += TRANSLATIONS_DIR=\\\"\"$$DCP_TRANSLATIONS_DIR\"\\\"

	DEFINES += MOSTUSEDCOUNTER_GCONFKEY=\\\"\"$$DCP_MOSTUSEDCOUNTER_GCONFKEY\"\\\"

	DEFINES += DCP_CATEGORY_DIR=\\\"\"$$DCP_CATEGORY_DIR\"\\\"

        DEFINES += DCP_CONFIG_PATH=\\\"/etc/duicontrolpanel.conf\\\"
}
}


