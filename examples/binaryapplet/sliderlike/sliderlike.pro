include(../../common.pri)
TEMPLATE      = lib
CONFIG       += plugin gui meegotouch silent debug

MOC_DIR	      = .moc
OBJECTS_DIR   = .objects

HEADERS       = dcpskeletonapplet.h \
                dcpskeletonbrief.h

SOURCES       = dcpskeletonapplet.cpp \
                dcpskeletonbrief.cpp

DESTDIR       = ../lib
TARGET        = $$qtLibraryTarget(dcpskelsliderapplet)
desktop.files += *.desktop
desktop.path = $$DCP_DESKTOP_DIR
target.path += $$DCP_APPLET_DIR

message("The plugin will be installed to: " $$target.path)

INSTALLS += \
	    target \
        desktop

