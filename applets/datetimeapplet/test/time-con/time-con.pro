TEMPLATE = app
TARGET = time-test
OBJECTS_DIR = ./tmp
MOC_DIR = ./tmp

CONFIG += build_all warn_on debug gui qmsystem

SOURCES +=	time.cpp

INCLUDEPATH += /usr/include/clock

