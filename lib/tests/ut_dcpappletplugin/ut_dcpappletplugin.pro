include(../common_top.pri)

INCLUDEPATH += $$system(find $$SRCDIR -type d)

TARGET = ut_dcpappletplugin

TEST_SOURCES = \
    $$SRCDIR/appletdb/dcpappletplugin.cpp \

# unit test and unit
SOURCES += \
    ut_dcpappletplugin.cpp \
    $$TEST_SOURCES \ 

# base classes
SOURCES += \


# unit test and unit
HEADERS += \
    ut_dcpappletplugin.h \
    $$SRCDIR/appletdb/dcpappletplugin.h \
    dcpappletplugin-applet.h \
    qpluginloader-fake.h \
    ../doubles/mdesktopentry-stub.h

# base classes
HEADERS += \


# service classes
HEADERS += \

include(../common_bot.pri)
