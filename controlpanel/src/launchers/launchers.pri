TARGET = ../duicontrolpanel.launch
SERVICE = ../service/com.nokia.duicontrolpanel.service
APPLAUNCH_SERVICE = ../service/com.nokia.dcpappletlauncher.service
DESKTOP = duicontrolpanel.desktop

# prefix is applied before all executable paths
PREFIX =
# prefix2 is an additional for the main process (not applied on applet launcher)
PREFIX2 =
# postfix can contain parameters for the program itself:
POSTFIX =

# This can enable the outprocess applets by default:
! meego {
    POSTFIX = "-outprocess"
}

# this config can add that software mode gets used by default
# in case dcp gets run through shell script / dbus / its icon
SOFTWARE {
    POSTFIX += "-software"
}

# this controls whether dcp is launched with applauncherd or not:
DISABLE_LAUNCHER {
    DEFINES += DISABLE_LAUNCHER
} else {
    PREFIX += "/usr/bin/invoker --type=m "

    # splash screen:
    PREFIX2 += "--splash=/usr/share/themes/blanco/images/splash/meegotouch-settings-splash.jpg "
}

# make the shell scripts:
system ( \
    cp $${DESKTOP}.1 $$DESKTOP; \
    cp com.nokia.duicontrolpanel.service.1 $$SERVICE; \
    cp com.nokia.dcpappletlauncher.service.1 $$APPLAUNCH_SERVICE; \
    sed -i -e \"s|PREFIX|PREFIX$$PREFIX2|\" \
        $$DESKTOP $$SERVICE; \
    sed -i -e \"s|PREFIX|$$PREFIX|\" \
        -e \"s|POSTFIX|$$POSTFIX|\" \
        $$DESKTOP $$SERVICE $$APPLAUNCH_SERVICE; \
)

# configure .desktop file:
! APPEAR_IN_MENU {
    system(echo \"NotShowIn=X-DUI;X-MEEGO;X-MeeGoTouch;\" >>$$DESKTOP)
}

# create the install target for the .desktop file:
desktop_entry.path = $$DCP_PREFIX/share/applications
desktop_entry.files = $$DESKTOP
INSTALLS += desktop_entry

