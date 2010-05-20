include(common.pri)

declxml.files += declarativeapplet/*.xml
declxml.path = $$DCP_UIDESC_DIR

decldesktop.files += declarativeapplet/*.desktop
decldesktop.path = $$DCP_DESKTOP_DIR

INSTALLS += declxml decldesktop

