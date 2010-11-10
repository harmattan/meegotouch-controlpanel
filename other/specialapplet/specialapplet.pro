TEMPLATE      = lib
CONFIG       += plugin gui meegotouch silent debug duicontrolpanel

include ($$[QT_INSTALL_DATA]/mkspecs/dcpconfig.pri)

MOC_DIR	      = .moc
OBJECTS_DIR   = .objects

HEADERS       = *.h
SOURCES       = *.cpp

TARGET        = $$qtLibraryTarget(dcpspecialapplet)
desktop.files += *.desktop
desktop.path = $$DCP_DESKTOP_DIR
target.path += $$DCP_APPLET_DIR

message("The plugin will be installed to: " $$target.path)

INSTALLS += \
	    target \
        desktop

