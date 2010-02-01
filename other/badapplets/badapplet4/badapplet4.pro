include(../common.pri)
TEMPLATE      = lib
CONFIG       += plugin gui dui  duicontrolpanel silent debug

MOC_DIR	      = .moc
OBJECTS_DIR   = .objects

INCLUDEPATH += ../
DEPENDPATH += $$INCLUDEPATH


HEADERS       = ../dcpskeletonapplet.h \
		        ../dcpskeletonwidget.h \
                ../dcpskeletonbrief.h

SOURCES       = dcpskeletonapplet.cpp \
		        ../dcpskeletonwidget.cpp \
                ../dcpskeletonbrief.cpp

DESTDIR       = ../lib
TARGET        = $$qtLibraryTarget(dcpbadapplet4)
desktop.files += *.desktop
desktop.path = $$DCP_DESKTOP_DIR
target.path += $$DCP_APPLET_DIR

message("The plugin will be installed to: " $$target.path)

INSTALLS += \
	    target \
        desktop

