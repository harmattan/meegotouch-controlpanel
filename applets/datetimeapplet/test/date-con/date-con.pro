TEMPLATE = app
TARGET = date-test
OBJECTS_DIR = ./tmp
MOC_DIR = ./tmp

CONFIG += build_all warn_on debug gui qmsystem qmsystem

SOURCES +=	date-con.cpp \
		../../src/time/dcptime.cpp

HEADERS +=	../../src/time/dcptime.h

INCLUDEPATH += /usr/include/clock

