include(../common_top.pri)

INCLUDEPATH += $$system(find $$SRCDIR -type d)
CONFIG += meegotouch
TARGET = ut_dcpcategorypage

TEST_SOURCES = \
    $$SRCDIR/page/dcpcategorypage.cpp \
    $$SRCDIR/page/pages.cpp \

# unit test and unit
SOURCES += \
    ut_dcpcategorypage.cpp \
    ../doubles/dcpmaincategory-fake.cpp \
    ../doubles/dcppage-fake.cpp \
    ../doubles/dcpcomponent-fake.cpp \
    ../doubles/mapplicationpage-fake.cpp \
    ../doubles/mapplicationwindow-fake.cpp \
    $$TEST_SOURCES \ 

# base classes
SOURCES += \


# unit test and unit
HEADERS += \
    ut_dcpcategorypage.h \
    $$SRCDIR/page/dcpcategorypage.h \
    $$SRCDIR/page/dcppage.h \
    $$SRCDIR/component/dcpmaincategory.h \
    $$SRCDIR/component/dcpcomponent.h \
    $$SRCDIR/page/pages.h \

# base classes
HEADERS += \


# service classes
HEADERS += \


