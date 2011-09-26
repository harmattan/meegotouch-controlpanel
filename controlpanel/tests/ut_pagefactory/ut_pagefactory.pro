include(../common_top.pri)

CONFIG += meegotouch

INCLUDEPATH += $$system(find $$SRCDIR -type d)
INCLUDEPATH += $${LIBDCPINCLUDE}
APPLETDBINCLUDE = $${LIBDCPINCLUDE}/../appletdb
INCLUDEPATH += $${APPLETDBINCLUDE}

TARGET = ut_pagefactory

# base classes
SOURCES += \
    *.cpp \
    $$STUBSDIR/dcppage-fake.cpp \
    $$STUBSDIR/categoryutils-fake.cpp \
    $$STUBSDIR/dcpappletcategorypage-fake.cpp \
    $$STUBSDIR/dcpappletpage-fake.cpp \
    $$STUBSDIR/mapplicationpage-fake.cpp \
    $$STUBSDIR/mapplication-fake.cpp \
    $$STUBSDIR/mapplicationwindow-fake.cpp \
    $$LIBDCPFAKES/mgconfitem-fake.cpp \
    $$STUBSDIR/dcpappletmanager-fake.cpp \
    $$STUBSDIR/dcptranslationmanager-fake.cpp \
    $$STUBSDIR/dcpcategories-fake.cpp \
    $$STUBSDIR/dcpappletplugin-fake.cpp \
    $$STUBSDIR/dcpappletmetadata-fake.cpp \
    $$STUBSDIR/dcpremotebriefreceiver-fake.cpp \
    $$SRCDIR/page/pages.cpp \
    $$SRCDIR/page/pagefactory.cpp \
    $$SRCDIR/categories/category.cpp \
    $$SRCDIR/categories/memorycategory.cpp \

# unit test and unit
HEADERS += \
    *.h \
    $$STUBSDIR/mapplicationwindow-fake.h \
    $$STUBSDIR/mwindow-fake.h \
    $$SRCDIR/page/pagefactory.h \
    $$SRCDIR/page/dcppage.h \
    $$SRCDIR/page/dcpappletcategorypage.h \
    $$SRCDIR/page/dcpappletpage.h \
    $$STUBSDIR/dcpappletplugin-applet.h \
    $$SRCDIR/appletmanager/dcpappletmanager.h \
    $$SRCDIR/appletmanager/dcptranslationmanager.h \

include(../common_bot.pri)

