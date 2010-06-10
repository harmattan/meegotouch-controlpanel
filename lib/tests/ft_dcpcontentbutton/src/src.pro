TOPDIR=../../..
include($$TOPDIR/dcpconfig.pri)
include($$TOPDIR/tests/common_top.pri)
TEMPLATE      = app 
INCLUDEPATH += $$system(find $$TOPDIR -type d)
CONFIG       += testlib meegotouch silent debug
DATADIR = /usr/lib/duicontrolpanel-tests/ft_dcpcontentbutton-data

DEFINES += DATADIR=\\\"$$DATADIR\\\"
TARGET = ../ft_dcpcontentbutton

TEST_SOURCES = \
    $$TOPDIR/src/widget/dcpcontentbutton.cpp \
    $$TOPDIR/src/appletdb/dcpappletmetadata.cpp \
    $$TOPDIR/src/appletdb/dcpappletplugin.cpp \
    $$TOPDIR/src/appletdb/dcpappletdb.cpp \
    $$TOPDIR/src/appletdb/dcpappletobject.cpp \

# unit test and unit
SOURCES += \
    ft_dcpcontentbutton.cpp \
    $$TEST_SOURCES \

# base classes
SOURCES += \


# unit test and unit
HEADERS += \
    ft_dcpcontentbutton.h \
    $$TOPDIR/src/widget/dcpcontentbutton.h \
    $$TOPDIR/src/appletdb/dcpappletmetadata.h \
    $$TOPDIR/src/appletdb/dcpappletplugin.h \
    $$TOPDIR/src/appletdb/dcpappletdb.h \
    $$TOPDIR/src/appletdb/dcpappletobject.h \

# base classes
HEADERS += \


# service classes
HEADERS += \


