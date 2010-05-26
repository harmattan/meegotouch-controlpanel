include(../common_top.pri)

INCLUDEPATH += $$system(find $$SRCDIR -type d)

TARGET = ft_dcpbrief

TEST_SOURCES = \
    $$SRCDIR/appletdb/dcpbrief.cpp \

# unit test and unit
SOURCES += \
    ft_dcpbrief.cpp \
    $$TEST_SOURCES \ 

# base classes
SOURCES += \


# unit test and unit
HEADERS += \
    ft_dcpbrief.h \
    $$SRCDIR/appletdb/dcpbrief.h \

# base classes
HEADERS += \


# service classes
HEADERS += \


