include(../common_top.pri)

CONFIG += meegotouch

# FIXME: this has to be removed if the functionality has merged into meegotouch
contains(DEFINES,USE_USERGUIDE) {
    CONFIG+=userguide
}

INCLUDEPATH += $$system(find $$SRCDIR -type d)
INCLUDEPATH += $${LIBDCPINCLUDE}
APPLETDBINCLUDE = $${LIBDCPINCLUDE}/../appletdb
INCLUDEPATH += $${APPLETDBINCLUDE}
INCLUDEPATH += $${STUBSDIR}

TARGET = ut_dcpappletbuttons

TEST_SOURCES = \
    $$SRCDIR/page/dcpappletbuttons.cpp \
    $$SRCDIR/page/pages.cpp \
    $$SRCDIR/component/dcpmaincategory.cpp \
    $$SRCDIR/component/dcpcomponent.cpp \
    $$SRCDIR/component/dcpappletwidget.cpp \

# unit test and unit
SOURCES += \
    *.cpp \
    $$STUBSDIR/dcpappletplugin-fake.cpp \
    $$STUBSDIR/dcpremoteappletobject-fake.cpp \
    $$STUBSDIR/maintranslations-fake.cpp \
    $$STUBSDIR/dcpappletdb-fake.cpp \
    $$LIBDCPFAKES/mgconfitem-fake.cpp \
    $$LIBDCPFAKES/mhelpbutton-fake.cpp \
    $$STUBSDIR/dcpappletmetadata-fake.cpp \
    $$STUBSDIR/dcpretranslator-fake.cpp \
    $$STUBSDIR/mwidgetcontroller-fake.cpp \
    $$STUBSDIR/dcpcontentitem-fake.cpp \
    $$STUBSDIR/dcpcontentitemcellcreator-fake.cpp \
    $$STUBSDIR/qgraphicsobject-fake.cpp \
    $$STUBSDIR/mlist-fake.cpp \
    $$STUBSDIR/mtheme-fake.cpp \
    $$STUBSDIR/qgraphicslinearlayout-fake.cpp \
    $$TEST_SOURCES \

# base classes
SOURCES += \


# unit test and unit
HEADERS += \
    ut_dcpappletbuttons.h \
    $$STUBSDIR/dcpappletplugin-applet.h \
    $$SRCDIR/page/dcpappletbuttons.h \
    $$SRCDIR/component/dcpmaincategory.h \
    $$SRCDIR/component/dcpcomponent.h \
    $$SRCDIR/component/dcpappletwidget.h \
    $$SRCDIR/page/dcpcontentitemcellcreator.h \
    $$SRCDIR/remote/dcpremoteappletobject.h \

# base classes
HEADERS += \


# service classes
HEADERS += \


