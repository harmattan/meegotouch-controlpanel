include(../common_top.pri)

INCLUDEPATH += $$system(find $$SRCDIR -type d)

TARGET = ut_maintranslations

TEST_SOURCES = \
    $$SRCDIR/page/maintranslations.cpp \

# unit test and unit
SOURCES += \
    ut_maintranslations.cpp \
    $$TEST_SOURCES \ 

# base classes
SOURCES += \


# unit test and unit
HEADERS += \
    ut_maintranslations.h \
    $$SRCDIR/page/maintranslations.h \

# base classes
HEADERS += \


# service classes
HEADERS += \


