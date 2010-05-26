include(../common_top.pri)

INCLUDEPATH += $$system(find $$SRCDIR -type d)

TARGET = ft_dcpwidget

TEST_SOURCES = \
    $$SRCDIR/appletdb/dcpwidget.cpp \

# unit test and unit
SOURCES += \
    ft_dcpwidget.cpp \
    $$TEST_SOURCES \ 

# base classes
SOURCES += \


# unit test and unit
HEADERS += \
    ft_dcpwidget.h \
    $$SRCDIR/appletdb/dcpwidget.h \

# base classes
HEADERS += \


# service classes
HEADERS += \


