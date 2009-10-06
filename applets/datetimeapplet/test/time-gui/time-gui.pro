TEMPLATE = app
TARGET = time-test
OBJECTS_DIR = ./tmp
MOC_DIR = ./tmp

CONFIG += build_all warn_on debug gui dui qmsystem

HEADERS +=	page.h \
		../../src/time/dcptime.h

SOURCES +=	page.cpp \
		../../src/time/dcptime.cpp \
		main.cpp

INCLUDEPATH += /usr/include/clock

LIBS += -lduicontrolpanel -lclockwidgets -ltime
LIBS += /usr/lib/libdatepicker.so

