include(../common_top.pri)

CONFIG += meegotouch

INCLUDEPATH += $$system(find $$SRCDIR -type d)
INCLUDEPATH += $${LIBDCPINCLUDE}
APPLETDBINCLUDE = $${LIBDCPINCLUDE}/../appletdb
INCLUDEPATH += $${APPLETDBINCLUDE}
INCLUDEPATH += /usr/include/m

TARGET = ut_pagefactory

# base classes
SOURCES += \
    *.cpp \
    $$STUBSDIR/dcppage-fake.cpp \
    $$STUBSDIR/dcpmainpage-fake.cpp \
    $$STUBSDIR/dcpappletcategorypage-fake.cpp \
    $$STUBSDIR/dcpappletpage-fake.cpp \
    $$STUBSDIR/mapplicationpage-fake.cpp \
    $$STUBSDIR/mapplication-fake.cpp \
    $$STUBSDIR/mapplicationwindow-fake.cpp \
    $$LIBDCPFAKES/mgconfitem-fake.cpp \
    $$STUBSDIR/dcpappletdb-fake.cpp \
    $$STUBSDIR/dcpcategories-fake.cpp \
    $$STUBSDIR/category-fake.cpp \
    $$STUBSDIR/dcpappletplugin-fake.cpp \
    $$STUBSDIR/dcpappletmetadata-fake.cpp \
    $$SRCDIR/page/pages.cpp \
    $$SRCDIR/page/pagefactory.cpp \

# unit test and unit
HEADERS += \
    *.h \
    $$STUBSDIR/mapplicationwindow-fake.h \
    $$STUBSDIR/mwindow-fake.h \
    $$SRCDIR/page/pagefactory.h \
    $$SRCDIR/page/dcppage.h \
    $$SRCDIR/page/dcpmainpage.h \
    $$SRCDIR/page/dcpappletcategorypage.h \
    $$SRCDIR/page/dcpappletpage.h \
    $$STUBSDIR/dcpappletplugin-applet.h \

include(../common_bot.pri)

