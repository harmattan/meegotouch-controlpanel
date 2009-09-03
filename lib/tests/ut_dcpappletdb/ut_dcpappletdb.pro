include(../common_top.pri)

INCLUDEPATH += $$system(find $$SRCDIR -type d)

TARGET = ut_dcpappletdb

TEST_SOURCES = \
    $$SRCDIR/appletdb/dcpappletdb.cpp \
    $$SRCDIR/appletdb/dcpappletmetadata.cpp

# unit test and unit
SOURCES += \
    ut_dcpappletdb.cpp \
    $$TEST_SOURCES \ 

# base classes
SOURCES += \


# unit test and unit
HEADERS += \
    ut_dcpappletdb.h \
    $$SRCDIR/appletdb/dcpappletdb.h \

# base classes
HEADERS += \


# service classes
HEADERS += \


