QT += testlib
SRCDIR = ../../../src
DCP_TESTS_INSTALL_LIB = /usr/lib/duicontrolpanel-tests                
TARGET = ft_dcpappletobject
target.path = $${DCP_TESTS_INSTALL_LIB}
INSTALLS += target

INCLUDEPATH += $$system(find $$SRCDIR -type d)

TARGET = ft_dcpappletobject

CONFIG += meegotouch

DATADIR = /usr/lib/duicontrolpanel-tests/ft_dcpappletobject-data
DEFINES += APPLET_LIBS=\\\"$$DATADIR\\\" DATADIR=\\\"$$DATADIR\\\" DESKTOP_DIR=\\\"$$DATADIR\\\" MOSTUSEDCOUNTER_GCONFKEY=\\\"/apps/duicontrolpanel/usagecount\\\"

# disable internal deprecation warnings:
DEFINES += DCP_DISABLE_DEPRECATION_WARNING

# FIXME these dependencies should be eliminated
DB_SOURCES = \
    $$SRCDIR/appletdb/dcpappletdb.cpp \
    $$SRCDIR/dcpretranslator.cpp \

DB_HEADERS = \
    $$SRCDIR/appletdb/dcpappletdb.h \
    $$SRCDIR/dcpretranslator.h \

TEST_SOURCES = \
    $$SRCDIR/appletdb/dcpappletobject.cpp \
    $$SRCDIR/appletdb/dcpappletmetadata.cpp \
    $$SRCDIR/appletdb/dcpmostusedcounter.cpp \
    $$SRCDIR/widget/dcpwidgettypes.cpp \
    $$SRCDIR/dcpdebug.cpp \
    $$DB_SOURCES

# unit test and unit
SOURCES += \
    ft_dcpappletobject.cpp \
    $$TEST_SOURCES \ 

# base classes
SOURCES += \
    $$SRCDIR/appletdb/dcpappletplugin.cpp


# unit test and unit
HEADERS += \
    ft_dcpappletobject.h \
    $$SRCDIR/appletdb/dcpappletobject.h \
    $$SRCDIR/widget/dcpwidgettypes.h \
    $$SRCDIR/appletdb/dcpappletmetadata.h \
    $$SRCDIR/dcpdebug.h

# base classes
HEADERS += \
    $$SRCDIR/appletdb/dcpappletplugin.h \
    $$DB_HEADERS


# service classes
HEADERS += \
