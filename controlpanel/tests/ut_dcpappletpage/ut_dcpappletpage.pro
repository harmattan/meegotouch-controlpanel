include(../common_top.pri)
CONFIG += meegotouch duicontrolpanel
QMAKE_CFlAGS+=-Wno-deprecated
QMAKE_CXXFlAGS+=-Wno-deprecated

INCLUDEPATH += $$system(find $$SRCDIR -type d)
INCLUDEPATH += $${LIBDCPINCLUDE}
APPLETDBINCLUDE = $${LIBDCPINCLUDE}/../appletdb
INCLUDEPATH += $${APPLETDBINCLUDE}
INCLUDEPATH += $${STUBSDIR}


TARGET = ut_dcpappletpage

TEST_SOURCES = \
    $$SRCDIR/page/dcpappletpage.cpp \
    $$SRCDIR/page/pages.cpp \
    $$SRCDIR/page/dcppage.cpp \

# unit test and unit
SOURCES += \
    ut_dcpappletpage.cpp \
    $$STUBSDIR/mapplicationpage-fake.cpp \
    $$STUBSDIR/mapplication-fake.cpp \
    $$STUBSDIR/mapplicationwindow-fake.cpp \
    $$STUBSDIR/mgridlayoutpolicy-fake.cpp \
    $$STUBSDIR/maintranslations-fake.cpp \
    $$STUBSDIR/mabstractlayoutpolicy-fake.cpp \
    $$STUBSDIR/mlayout-fake.cpp \
    $$STUBSDIR/mlinearlayoutpolicy-fake.cpp \
    $$STUBSDIR/mcontainer-fake.cpp \
    $$STUBSDIR/dcpcontentitem-fake.cpp \
    $$STUBSDIR/mwidgetcontroller-fake.cpp \
    $$STUBSDIR/mgconfitem-fake.cpp \
    $$STUBSDIR/mdesktopentry-fake.cpp \
#    $$STUBSDIR/dcppage-fake.cpp \
    $$STUBSDIR/dcpcomponent-fake.cpp \
    $$STUBSDIR/dcpappletdb-fake.cpp \
    $$STUBSDIR/dcpappletplugin-fake.cpp \
    $$STUBSDIR/dcpappletobject-fake.cpp \
    $$STUBSDIR/dcpappletmetadata-fake.cpp \
    $$STUBSDIR/dcpretranslator-fake.cpp \
    $$STUBSDIR/dcpsinglecomponent-fake.cpp \
    $$STUBSDIR/dcpcategorycomponent-fake.cpp \
    $$STUBSDIR/dcpmaincategory-fake.cpp \
    $$STUBSDIR/qgraphicslinearlayout-fake.cpp \
    $$STUBSDIR/qgraphicsobject-fake.cpp \
    $$TEST_SOURCES \ 

# base classes
SOURCES += \


# unit test and unit
HEADERS += \
    ut_dcpappletpage.h \
    $$STUBSDIR/dcpappletplugin-applet.h \
    $$SRCDIR/page/dcpappletpage.h \
    $$SRCDIR/page/dcppage.h \
    $$SRCDIR/page/pages.h \
    $$SRCDIR/page/dcpcategorycomponent.h \
    $$SRCDIR/component/dcpcomponent.h \
    $$SRCDIR/component/dcpmaincategory.h \
    $$SRCDIR/component/dcpsinglecomponent.h \

# base classes
HEADERS += \


# service classes
HEADERS += \


