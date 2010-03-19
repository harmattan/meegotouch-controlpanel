include(../common_top.pri)
CONFIG += dui
INCLUDEPATH += $$system(find $$SRCDIR -type d)
INCLUDEPATH += $$system(find $$SRCDIR/../../lib/src/ -type d)

TARGET = ft_dcppage

TEST_SOURCES = \
    $$SRCDIR/page/dcppage.cpp \
    $$SRCDIR/page/pages.cpp \

# unit test and unit
SOURCES += \
    ft_dcppage.cpp \
    $$SRCDIR/../../lib/src/dcpdebug.cpp\
    $$TEST_SOURCES \ 

# base classes
SOURCES += \


# unit test and unit
HEADERS += \
    ft_dcppage.h \
    $$SRCDIR/page/dcppage.h \
    $$SRCDIR/../../lib/src/dcpdebug.h

# base classes
HEADERS += \


# service classes
HEADERS += \

