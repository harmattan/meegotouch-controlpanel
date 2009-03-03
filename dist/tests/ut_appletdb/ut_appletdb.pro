include(../common_top.pri)
TARGET = ut_appletdb


# the required components for the test:
DEPENDPATH += ../../src/appletdb \ 

HEADERS += ../../src/appletdb/dcpappletdb.h \
         ../../src/appletdb/dcpappletmetadata.h \
		ut_appletdb.h \

SOURCES += ../../src/appletdb/dcpappletdb.cpp \
           ../../src/appletdb/dcpappletmetadata.cpp \
           ut_appletdb.cpp \

include(../common_bottom.pri)

