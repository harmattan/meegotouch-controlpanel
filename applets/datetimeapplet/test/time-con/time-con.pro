TEMPLATE = app
TARGET = time-test
OBJECTS_DIR = ./tmp
MOC_DIR = ./tmp

CONFIG += build_all warn_on debug qmsystem

SOURCES +=	time.cpp \
                ../../src/time/dcptime.cpp

HEADERS +=      ../../src/time/dcptime.h

