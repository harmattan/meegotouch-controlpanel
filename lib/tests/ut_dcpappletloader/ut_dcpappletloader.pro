include(../common_top.pri)

INCLUDEPATH += $$system(find $$SRCDIR -type d)

TARGET = ut_dcpappletloader

TEST_SOURCES = \
    $$SRCDIR/appletdb/dcpappletloader.cpp \

# unit test and unit
SOURCES += \
    ut_dcpappletloader.cpp \
    dcpappletloader-applet.cpp \
    $$TEST_SOURCES \ 

# base classes
SOURCES += \


# unit test and unit
HEADERS += \
    ut_dcpappletloader.h \
    $$SRCDIR/appletdb/dcpappletloader.h \
    dcpappletloader-applet.h \
    qpluginloader-fake.h \
    ../doubles/duidesktopentry-stub.h

# base classes
HEADERS += \


# service classes
HEADERS += \

include(../common_bot.pri)
