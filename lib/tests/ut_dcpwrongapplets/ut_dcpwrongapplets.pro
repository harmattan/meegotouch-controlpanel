include(../common_top.pri)

CONFIG += qt meegotouch

INCLUDEPATH += $$system(find $$SRCDIR -type d)

TARGET = ut_dcpwrongapplets

TEST_SOURCES = \

# unit test and unit
SOURCES += \
    ut_dcpwrongapplets.cpp \
    ../doubles/mgconfitem-fake.cpp \
    execinfo-fake.cpp \
    signal-fake.cpp \
    $$TEST_SOURCES \ 

# unit test and unit
HEADERS += \
    ut_dcpwrongapplets.h \

