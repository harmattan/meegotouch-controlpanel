include(../common_top.pri)

INCLUDEPATH += $$system(find $$SRCDIR -type d)

TARGET = ft_mkftclassname

TEST_SOURCES = \
    $$SRCDIR/mkftclassname.cpp \

# unit test and unit
SOURCES += \
    ft_mkftclassname.cpp \
    $$TEST_SOURCES \ 

# base classes
SOURCES += \
    mkftbasesources

# unit test and unit
HEADERS += \
    ft_mkftclassname.h \
    $$SRCDIR/mkftclassname.h \

# base classes
HEADERS += \
    mkftbaseheaders

# service classes
HEADERS += \
    mkftserviceheaders

