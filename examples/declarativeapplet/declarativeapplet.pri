include(common.pri)

declxml.path = $$DCP_UIDESC_DIR
decldesktop.path = $$DCP_DESKTOP_DIR

INSTALLS += declxml decldesktop

# applet specific things:
include(declarativeapplet/simple/simple.pri)
include(declarativeapplet/localized/localized.pri)

