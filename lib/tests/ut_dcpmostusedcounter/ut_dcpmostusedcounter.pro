include(../common_top.pri)

INCLUDEPATH += $$system(find $$SRCDIR -type d)

TARGET = ut_dcpmostusedcounter

TEST_SOURCES = \
    $$SRCDIR/appletdb/dcpmostusedcounter.cpp \

# unit test and unit
SOURCES += \
    ut_dcpmostusedcounter.cpp \
    ../doubles/mgconfitem-fake.cpp \
    $$TEST_SOURCES \ 

# base classes
SOURCES += \


# unit test and unit
HEADERS += \
    ut_dcpmostusedcounter.h \
    $$SRCDIR/dcpmostusedcounter.h \
    ../doubles/mgconfitem_priv.h \

# base classes
HEADERS += \


# service classes
HEADERS += \

include(../common_bot.pri)
