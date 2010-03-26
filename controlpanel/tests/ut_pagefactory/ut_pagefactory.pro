include(../common_top.pri)
OBJECTS_DIR = .tmp                                                                                                
MOC_DIR = .tmp 
CONFIG += duicontrolpanel
CONFIG -= app_bundle
INCLUDEPATH += $$system(find $$SRCDIR -type d)
INCLUDEPATH += $${LIBDCPINCLUDE}
APPLETDBINCLUDE = $${LIBDCPINCLUDE}/../appletdb
INCLUDEPATH += $${APPLETDBINCLUDE}
INCLUDEPATH += $${LIBDCPFAKES}
INCLUDEPATH += $${STUBSDIR}

TARGET = ut_pagefactory

TEST_SOURCES = $$SRCDIR/page/pages.cpp \
               $$SRCDIR/page/pagefactory.cpp \
               $$STUBSDIR/stubbase.cpp \

# unit test and unit
SOURCES += \
    ut_pagefactory.cpp \
    $$TEST_SOURCES \ 

# base classes
SOURCES += \
    ../doubles/dcppage-fake.h \
    ../doubles/dcpmainpage-fake.h \
    ../doubles/dcpcategorypage-fake.h \
    ../doubles/dcpappletcategorypage-fake.h \
    ../doubles/dcpappletpage-fake.h \
    ../doubles/appleterrorsdialog-fake.h \
#    $$LIBDCPFAKES/dcpappletobject-fake.h \

# unit test and unit
HEADERS += \
    ut_pagefactory.h \
    $$SRCDIR/page/pagefactory.h \
    $$SRCDIR/page/dcpmainpage.h \
    $$SRCDIR/page/dcpcategorypage.h \
    $$SRCDIR/page/dcpappletcategorypage.h \
    $$SRCDIR/page/dcpappletpage.h \
    $$SRCDIR/appleterrorsdialog.h \

# base classes
HEADERS += $$SRCDIR/page/dcppage.h \


# service classes
# HEADERS += \


