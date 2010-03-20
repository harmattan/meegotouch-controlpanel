include(../common_top.pri)

INCLUDEPATH += $$system(find $$SRCDIR -type d)
INCLUDEPATH += $$system(find $$SRCDIR/../../lib/src/ -type d)
TARGET = ut_pages

TEST_SOURCES = \
    $$SRCDIR/page/pages.cpp \

# unit test and unit
SOURCES += \
    ut_pages.cpp \
    $$TEST_SOURCES \ 

# base classes
SOURCES += \


# unit test and unit
HEADERS += \
    ut_pages.h \
    $$SRCDIR/page/pages.h \

# base classes
HEADERS += \


# service classes
HEADERS += \


