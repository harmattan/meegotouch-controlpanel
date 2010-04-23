include(../common_top.pri)
CONFIG += meegotouch
INCLUDEPATH += $$system(find $$SRCDIR -type d)
INCLUDEPATH += ../doubles 
INCLUDEPATH += $$LIBDCPSRC/include 

TARGET = ut_dcpcomponent

TEST_SOURCES = \
    $$SRCDIR/component/dcpcomponent.cpp \
    $$SRCDIR/page/pages.cpp \
    #../doubles/mapplicationpage-fake.cpp \
    #../doubles/mapplicationwindow-fake.cpp \

# unit test and unit
SOURCES += \
    ut_dcpcomponent.cpp \
    $$TEST_SOURCES \ 

# base classes
SOURCES += \


# unit test and unit
HEADERS += \
    ut_dcpcomponent.h \
    $$SRCDIR/component/dcpcomponent.h \
    $$SRCDIR/page/pages.h \

# base classes
HEADERS += \


# service classes
HEADERS += \


