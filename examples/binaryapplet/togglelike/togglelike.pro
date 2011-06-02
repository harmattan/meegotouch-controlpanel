include(../../common.pri)
TEMPLATE      = lib
CONFIG       += plugin gui meegotouch silent debug

MOC_DIR	      = .moc
OBJECTS_DIR   = .objects

HEADERS       = dcptoggleexampleapplet.h \
                dcptoggleexamplebrief.h

SOURCES       = dcptoggleexampleapplet.cpp \
                dcptoggleexamplebrief.cpp

DESTDIR       = ../lib
TARGET        = $$qtLibraryTarget(dcptoggleexampleapplet)
desktop.files += *.desktop
desktop.path = $$DCP_DESKTOP_DIR
target.path += $$DCP_APPLET_DIR

INSTALLS += \
	    target \
        desktop

