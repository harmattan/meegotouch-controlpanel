include(../common_top.pri)

CONFIG += meegotouch duicontrolpanel

INCLUDEPATH += $$system(find $$SRCDIR -type d)
INCLUDEPATH += $${LIBDCPINCLUDE}
APPLETDBINCLUDE = $${LIBDCPINCLUDE}/../appletdb
INCLUDEPATH += $${APPLETDBINCLUDE}
INCLUDEPATH += $${STUBSDIR}


TARGET = ut_dcpmainpage

TEST_SOURCES = \
    $$SRCDIR/page/dcpmainpage.cpp \
    $$SRCDIR/page/pages.cpp \
    $$SRCDIR/page/dcppage.cpp \

# unit test and unit
SOURCES += \
    ut_dcpmainpage.cpp \
    $$STUBSDIR/mapplication-fake.cpp \
    $$STUBSDIR/mapplicationpage-fake.cpp \
    $$STUBSDIR/dcpappletbuttons-fake.cpp \
    $$STUBSDIR/qgraphicsobject-fake.cpp \
    $$STUBSDIR/mapplicationwindow-fake.cpp \
    $$STUBSDIR/mgridlayoutpolicy-fake.cpp \
    $$STUBSDIR/maintranslations-fake.cpp \
    $$STUBSDIR/mabstractlayoutpolicy-fake.cpp \
    $$STUBSDIR/mlayout-fake.cpp \
    $$STUBSDIR/mlinearlayoutpolicy-fake.cpp \
    $$STUBSDIR/dcpremotebriefreceiver-fake.cpp \
    $$STUBSDIR/mcontainer-fake.cpp \
    $$STUBSDIR/dcpcontentitem-fake.cpp \
    $$STUBSDIR/mwidgetcontroller-fake.cpp \
    $$LIBDCPFAKES/mgconfitem-fake.cpp \
    $$LIBDCPFAKES/mimagewidget-fake.cpp \
#    $$STUBSDIR/dcppage-fake.cpp \
    $$STUBSDIR/dcpcomponent-fake.cpp \
    $$STUBSDIR/dcpappletdb-fake.cpp \
    $$STUBSDIR/dcpappletmetadata-fake.cpp \
    $$STUBSDIR/dcpappletplugin-fake.cpp \
    $$STUBSDIR/dcpretranslator-fake.cpp \
    $$STUBSDIR/mbasiclistitem-fake.cpp \
    $$STUBSDIR/dcpsinglecomponent-fake.cpp \
    $$STUBSDIR/dcpcategorycomponent-fake.cpp \
    $$STUBSDIR/dcpmaincategory-fake.cpp \
    $$STUBSDIR/pagefactory-fake.cpp \
    $$STUBSDIR/qgraphicslinearlayout-fake.cpp \
    $$TEST_SOURCES \ 

# base classes
SOURCES += \


# unit test and unit
HEADERS += \
    ut_dcpmainpage.h \
    $$SRCDIR/page/dcpmainpage.h \
    $$SRCDIR/page/dcpappletbuttons.h \
    $$SRCDIR/page/dcppage.h \
    $$SRCDIR/page/pagefactory.h \
    $$SRCDIR/page/pages.h \
    $$SRCDIR/page/dcpcategorycomponent.h \
    $$SRCDIR/component/dcpcomponent.h \
    $$SRCDIR/component/dcpmaincategory.h \
    $$SRCDIR/component/dcpsinglecomponent.h \
    $$STUBSDIR/dcpappletplugin-applet.h \

# base classes
HEADERS += \


# service classes
HEADERS += \


