include(../common_top.pri)

INCLUDEPATH += $$system(find $$SRCDIR -type d)

TARGET = ft_dcpmostusedcounter

TEST_SOURCES = \
    $$SRCDIR/appletdb/dcpmostusedcounter.cpp \

# unit test and unit
SOURCES += \
    ft_dcpmostusedcounter.cpp \
    $$TEST_SOURCES \ 

# base classes
SOURCES += \


# unit test and unit
HEADERS += \
    ft_dcpmostusedcounter.h \
    $$SRCDIR/dcpmostusedcounter.h \

# base classes
HEADERS += \


# service classes
HEADERS += \

include(../common_bot.pri)
