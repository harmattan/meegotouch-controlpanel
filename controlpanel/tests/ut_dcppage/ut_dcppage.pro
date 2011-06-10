include(../common_top.pri)

CONFIG += meegotouch

INCLUDEPATH += $$system(find $$SRCDIR -type d)
INCLUDEPATH += $$system(find $$SRCDIR/../../lib/src/ -type d)

TARGET = ut_dcppage

TEST_SOURCES = \
    $$SRCDIR/page/dcppage.cpp \
    $$SRCDIR/page/pages.cpp \

# unit test and unit
SOURCES += \
    *.cpp \
    $$STUBSDIR/mlayout-fake.cpp \
    $$STUBSDIR/mapplicationpage-fake.cpp \
    $$STUBSDIR/mapplicationwindow-fake.cpp \
    $$STUBSDIR/mlabel-fake.cpp \
    $$LIBDCPFAKES/mhelpbutton-fake.cpp \
    $$SRCDIR/../../lib/src/dcpdebug.cpp\
    $$TEST_SOURCES \ 

# base classes
SOURCES += \


# unit test and unit
HEADERS += \
    *.h \
    $$SRCDIR/page/dcppage.h \
    $$SRCDIR/../../lib/src/dcpdebug.h

# base classes
HEADERS += \


# service classes
HEADERS += \

