include(../common_top.pri)

INCLUDEPATH += $$system(find $$SRCDIR -type d)

TARGET = ut_dcpretranslator

TEST_SOURCES = \
    $$SRCDIR/dcpretranslator.cpp \

# unit test and unit
SOURCES += \
    ut_dcpretranslator.cpp \
    ../../../controlpanel/tests/doubles/mapplication-fake.cpp \ 
    ../../../controlpanel/tests/doubles/mapplicationwindow-fake.cpp \ 
    ../doubles/filedatas.cpp \
    ../doubles/mdesktopentry-fake.cpp \
    ../doubles/mgconfitem-fake.cpp \
    ../doubles/mlocale-fake.cpp \
    $$TEST_SOURCES \

# base classes
SOURCES += \


# unit test and unit
HEADERS += \
    ut_dcpretranslator.h \
    $$SRCDIR/dcpretranslator.h \
    ../doubles/filedatas.h \
    ../doubles/mgconfitem-fake.h \
    ../doubles/mlocale-fake.h \

# base classes
HEADERS += \


# service classes
HEADERS += \


