include(../common_top.pri)

INCLUDEPATH += $$system(find $$SRCDIR -type d)

TARGET = ut_dcpwidget

TEST_SOURCES = \
    $$SRCDIR/appletdb/dcpwidget.cpp \

# unit test and unit
SOURCES += \
    ut_dcpwidget.cpp \
    $$TEST_SOURCES \ 

# base classes
SOURCES += \


# unit test and unit
HEADERS += \
    ut_dcpwidget.h \
    $$SRCDIR/appletdb/dcpwidget.h \

# base classes
HEADERS += \


# service classes
HEADERS += \


