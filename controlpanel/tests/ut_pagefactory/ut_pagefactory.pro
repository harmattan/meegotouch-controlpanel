include(../common_top.pri)

CONFIG -= dui
CONFIG -= app_bundle
INCLUDEPATH += $$system(find $$SRCDIR -type d)
INCLUDEPATH += $${LIBDCPINCLUDE}
APPLETDBINCLUDE = $${LIBDCPINCLUDE}/../appletdb
INCLUDEPATH += $${APPLETDBINCLUDE}

TARGET = ut_pagefactory

# base classes
SOURCES += \
    *.cpp \
    $$STUBSDIR/dcppage-fake.cpp \
    $$STUBSDIR/dcpmainpage-fake.cpp \
    $$STUBSDIR/dcpcategorypage-fake.cpp \
    $$STUBSDIR/dcpappletcategorypage-fake.cpp \
    $$STUBSDIR/dcpappletpage-fake.cpp \
    $$STUBSDIR/appleterrorsdialog-fake.cpp \
    $$STUBSDIR/duiapplicationpage-fake.cpp \
    $$STUBSDIR/duiapplication-fake.cpp \
    $$STUBSDIR/duiapplicationwindow.cpp \
    $$SRCDIR/page/pages.cpp \
    $$SRCDIR/page/pagefactory.cpp \
    $$SRCDIR/page/maintranslations.cpp \

# unit test and unit
HEADERS += \
    *.h \
    $$STUBSDIR/duiapplicationwindow.h \
    $$STUBSDIR/duiwindow.h \
    $$SRCDIR/page/pagefactory.h \
    $$SRCDIR/page/dcppage.h \
    $$SRCDIR/page/dcpmainpage.h \
    $$SRCDIR/page/dcpcategorypage.h \
    $$SRCDIR/page/dcpappletcategorypage.h \
    $$SRCDIR/page/dcpappletpage.h \
    $$SRCDIR/appleterrorsdialog.h \

