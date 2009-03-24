TEMPLATE      = lib
CONFIG       += plugin gui dui
LIBS         += -ldui
INCLUDEPATH  += $$[QT_INSTALL_HEADERS]/dui
MOC_DIR	      = .moc
OBJECTS_DIR   = .objects

HEADERS       = displayapplet.h \
		        displaywidget.h

SOURCES       = displayapplet.cpp \
		        displaywidget.cpp

TARGET        = $$qtLibraryTarget(displayapplet)
DESTDIR       = ../lib

target.path += $$[QT_INSTALL_LIBS]/duicontrolpanel/applets

INSTALLS += \
	    target
