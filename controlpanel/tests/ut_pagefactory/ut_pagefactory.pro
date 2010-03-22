include(../common_top.pri)
CONFIG += duicontrolpanel
INCLUDEPATH += $$system(find $$SRCDIR -type d)
INCLUDEPATH += $${LIBDCPINCLUDE}

TARGET = ut_pagefactory

TEST_SOURCES = $$SRCDIR/page/pages.cpp \

# unit test and unit
SOURCES += \
    ut_pagefactory.cpp \
    $$TEST_SOURCES \ 

# base classes
SOURCES += \


# unit test and unit
HEADERS += \
    ut_pagefactory.h \
    ../doubles/dcppage-fake.h
# base classes
HEADERS += \


# service classes
HEADERS += \


