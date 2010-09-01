include(../common_top.pri)

CONFIG += meegotouch

INCLUDEPATH += $$system(find $$SRCDIR -type d)

TARGET = ut_appletthemes

TEST_SOURCES = \
    $$SRCDIR/appletthemes.cpp \

# unit test and unit
SOURCES += \
    $$STUBSDIR/mtheme-fake.cpp \
    $$STUBSDIR/qfileinfo-fake.cpp \
    ut_appletthemes.cpp \
    $$TEST_SOURCES \ 

# base classes
SOURCES += \


# unit test and unit
HEADERS += \
    ut_appletthemes.h \
    $$SRCDIR/appletthemes.h \

# base classes
HEADERS += \


# service classes
HEADERS += \


