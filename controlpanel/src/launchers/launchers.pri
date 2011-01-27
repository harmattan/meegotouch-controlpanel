TARGET = ../duicontrolpanel.launch
DCP_SH = ../../duicontrolpanel
APPLAUNCH_SH = ../../dcpappletlauncher
SERVICE = ../service/com.nokia.duicontrolpanel.service
DESKTOP = duicontrolpanel.desktop
PREFIX =
POSTFIX =

# this config can add that software mode gets used by default
# in case dcp gets run through shell script / dbus / its icon
SOFTWARE {
    POSTFIX += -software
}

# this controls whether dcp is launched with applauncherd or not:
DISABLE_LAUNCHER {
    DEFINES += DISABLE_LAUNCHER
} else {
    QMAKE_CXXFLAGS += -fPIC -fvisibility=hidden -fvisibility-inlines-hidden
    QMAKE_LFLAGS += -pie -rdynamic

    PREFIX += "/usr/bin/invoker --type=m "
}

# make the shell scripts:
system ( \
    cp $${DESKTOP}.1 $$DESKTOP; \
    cp duicontrolpanel.invoker $$DCP_SH; \
    cp dcpappletlauncher.invoker $$APPLAUNCH_SH; \
    cp com.nokia.duicontrolpanel.service.1 $$SERVICE; \
    sed -i -e \"s|PREFIX|$$PREFIX|\" \
        -e \"s|POSTFIX|$$POSTFIX|\" \
        $$DCP_SH $$APPLAUNCH_SH $$DESKTOP $$SERVICE; \
    chmod +x $$DCP_SH $$APLAUNCH_SH \
)

# configure .desktop file:
! APPEAR_IN_MENU {
    system(echo \"NotShowIn=X-DUI;X-MEEGO;X-MeeGoTouch;\" >>$$DESKTOP)
}

# create the install target:
appletlauncher.files += $$DCP_SH \
                        $$APPLAUNCH_SH \

appletlauncher.path += $$DCP_PREFIX/bin
INSTALLS += appletlauncher

# create the install target for the .desktop file:
desktop_entry.path = $$DCP_PREFIX/share/applications
desktop_entry.files = $$DESKTOP
INSTALLS += desktop_entry

