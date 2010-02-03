include(../common_top.pri)

CONFIG += duicontrolpanel
 
INCLUDEPATH += $$system(find $$SRCDIR -type d)
INCLUDEPATH += $$LIBDCPINCLUDE 
TARGET = ft_dcpcomponent

TEST_SOURCES = \
    $$SRCDIR/component/dcpcomponent.cpp \

# unit test and unit
SOURCES += \
    ft_dcpcomponent.cpp \
    $$TEST_SOURCES \ 

# base classes
SOURCES += $$SRCDIR/page/pages.cpp


# unit test and unit
HEADERS += \
    ft_dcpcomponent.h \
    $$SRCDIR/include/* \
    $$SRCDIR/component/dcpcomponent.h \

message ($$HEADERS)
# base classes
HEADERS += \


# service classes
HEADERS += \


