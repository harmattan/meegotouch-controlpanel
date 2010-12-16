include(../common_top.pri)
CONFIG += meegotouch
INCLUDEPATH += $$system(find $$SRCDIR -type d)
INCLUDEPATH += ../doubles 

TARGET = ut_dcpmaincategory

TEST_SOURCES = \
    $$SRCDIR/component/dcpmaincategory.cpp \

# unit test and unit
SOURCES += \
    ut_dcpmaincategory.cpp \
    $$SRCDIR/page/pages.cpp \
    ../doubles/mapplication-fake.cpp \
    ../doubles/mapplicationwindow-fake.cpp \
    ../doubles/mwindow-fake.h \
    $$TEST_SOURCES \ 

# base classes
SOURCES += \


# unit test and unit
HEADERS += \
    ut_dcpmaincategory.h \
    $$SRCDIR/component/dcpmaincategory.h \
    $$SRCDIR/page/pages.h \

# base classes
HEADERS += \


# service classes
HEADERS += \


