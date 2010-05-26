include(../common_top.pri)

INCLUDEPATH += $$system(find $$SRCDIR -type d)

TARGET = ft_dcpappletplugin

TEST_SOURCES = \
    $$SRCDIR/appletdb/dcpappletplugin.cpp \

# unit test and unit
SOURCES += \
    ft_dcpappletplugin.cpp \
    ../doubles/mdesktopentry-fake.cpp \
    ../doubles/fileDatas.cpp \
    $$TEST_SOURCES \ 

# base classes
SOURCES += \


# unit test and unit
HEADERS += \
    ft_dcpappletplugin.h \
    $$SRCDIR/appletdb/dcpappletplugin.h \
    dcpappletplugin-applet.h \
    qpluginloader-fake.h \

# base classes
HEADERS += \


# service classes
HEADERS += \

include(../common_bot.pri)
