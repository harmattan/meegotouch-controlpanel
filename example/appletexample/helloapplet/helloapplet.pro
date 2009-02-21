TEMPLATE      = lib
CONFIG       += plugin gui dui
LIBS         += -ldui
INCLUDEPATH  += $$[QT_INSTALL_HEADERS]/dui
MOC_DIR	      = .moc
OBJECTS_DIR   = .objects

HEADERS       = helloapplet.h \
		hellowidget.h

SOURCES       = helloapplet.cpp \
		hellowidget.cpp

TARGET        = $$qtLibraryTarget(exampleapplet)
DESTDIR       = ../lib

target.path += $$[QT_INSTALL_LIBS]/dui/applets

INSTALLS += \
	    target
