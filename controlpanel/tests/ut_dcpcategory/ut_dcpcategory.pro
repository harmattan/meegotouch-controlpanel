include(../common_top.pri)

INCLUDEPATH += $$system(find $$SRCDIR -type d)

TARGET = ut_dcpcategory

TEST_SOURCES = \
    $$SRCDIR/dcpcategory.cpp \

# unit test and unit
SOURCES += \
    ut_dcpcategory.cpp \
    $$TEST_SOURCES \ 

# base classes
SOURCES += \


# unit test and unit
HEADERS += \
    ut_dcpcategory.h \
    $$SRCDIR/dcpcategory.h \

# base classes
HEADERS += \


# service classes
HEADERS += \


