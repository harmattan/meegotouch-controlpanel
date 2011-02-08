TOPDIR=../../..
TEMPLATE      = app 
QT += testlib
INCLUDEPATH += $$system(find $$TOPDIR -type d)
CONFIG       += meegotouch silent debug
DATADIR = /usr/lib/duicontrolpanel-tests/ft_dcpcontentbutton-data
LIBS += -L../../lib/ -lduicontrolpanel -lsysinfo

DEFINES += DATADIR=\\\"$$DATADIR\\\"
DEFINES += APPLET_LIBS=\\\"$$DATADIR\\\" DATADIR=\\\"$$DATADIR\\\" DESKTOP_DIR=\\\"$$DATADIR\\\" 
DEFINES += MOSTUSEDCOUNTER_GCONFKEY=\\\"/apps/duicontrolpanel/usagecount\\\"

# disable internal deprecation warnings:
DEFINES += DCP_DISABLE_DEPRECATION_WARNING

TARGET = ../ft_dcpcontentbutton

TEST_SOURCES = \
    $$TOPDIR/src/widget/dcpcontentbutton.cpp \
    $$TOPDIR/src/widget/dcpwidgettypes.cpp \
    $$TOPDIR/src/appletdb/dcpappletmetadata.cpp \
    $$TOPDIR/src/appletdb/dcpappletplugin.cpp \
    $$TOPDIR/src/appletdb/dcpappletdb.cpp \
    $$TOPDIR/src/appletdb/dcpappletobject.cpp \
    $$TOPDIR/src/dcpdebug.cpp \
    $$TOPDIR/src/appletdb/dcpmostusedcounter.cpp \

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
    $$TOPDIR/src/appletdb/dcpmostusedcounter.h \
    $$TOPDIR/src/widget/dcpwidgettypes.h \
    $$TOPDIR/src/appletdb/dcpappletobject.h \
    $$TOPDIR/src/dcpdebug.h \

# base classes
HEADERS += \


# service classes
HEADERS += \

include (../../check.pri)
include (../../coverage.pri)


