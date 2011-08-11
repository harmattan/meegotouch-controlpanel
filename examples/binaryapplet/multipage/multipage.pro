include(../../common.pri)
TEMPLATE      = lib
CONFIG       += plugin gui meegotouch debug

MOC_DIR	      = .moc
OBJECTS_DIR   = .objects

HEADERS       += dcpmultipageapplet.h \
                 dcpmultipagewidget.h \

SOURCES       = dcpmultipageapplet.cpp \
                dcpmultipagewidget.cpp

DESTDIR       = ../lib
TARGET        = $$qtLibraryTarget(dcpmultipageapplet)
desktop.files += *.desktop
desktop.path = $$DCP_DESKTOP_DIR
target.path += $$DCP_APPLET_DIR

INSTALLS += \
	    target \
        desktop

