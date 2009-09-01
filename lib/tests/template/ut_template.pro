include(../common_top.pri)

INCLUDEPATH += $$system(find $$SRCDIR -type d)

TARGET = ut_mkutclassname

TEST_SOURCES = \
    $$SRCDIR/mkutclassname.cpp \

# unit test and unit
SOURCES += \
    ut_mkutclassname.cpp \
    $$TEST_SOURCES \ 

# base classes
SOURCES += \
    mkutbasesources

# unit test and unit
HEADERS += \
    ut_mkutclassname.h \
    $$SRCDIR/mkutclassname.h \

# base classes
HEADERS += \
    mkutbaseheaders

# service classes
HEADERS += \
    mkutserviceheaders

