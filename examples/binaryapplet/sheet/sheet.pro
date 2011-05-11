include(../../common.pri)
TEMPLATE      = lib
CONFIG       += plugin gui meegotouch debug

MOC_DIR	      = .moc
OBJECTS_DIR   = .objects

HEADERS       += dcpsheetapplet.h \

SOURCES       = dcpsheetapplet.cpp \

DESTDIR       = ../lib
TARGET        = $$qtLibraryTarget(dcpsheetapplet)
desktop.files += *.desktop
desktop.path = $$DCP_DESKTOP_DIR
target.path += $$DCP_APPLET_DIR

INSTALLS += \
	    target \
        desktop

