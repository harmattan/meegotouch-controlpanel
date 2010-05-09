include(../common_top.pri)

INCLUDEPATH += $$system(find $$SRCDIR -type d)

TARGET = ut_dcpbrief

TEST_SOURCES = \
    $$SRCDIR/appletdb/dcpbrief.cpp \

# unit test and unit
SOURCES += \
    ut_dcpbrief.cpp \
    $$TEST_SOURCES \ 

# base classes
SOURCES += \


# unit test and unit
HEADERS += \
    ut_dcpbrief.h \
    $$SRCDIR/appletdb/dcpbrief.h \

# base classes
HEADERS += \


# service classes
HEADERS += \


