include(../common_top.pri)

CONFIG += meegotouch

INCLUDEPATH += $$system(find $$SRCDIR -type d)
INCLUDEPATH += $${LIBDCPINCLUDE}
APPLETDBINCLUDE = $${LIBDCPINCLUDE}/../appletdb
INCLUDEPATH += $${APPLETDBINCLUDE}
INCLUDEPATH += $${STUBSDIR}


TARGET = ut_dcpcategorycomponent

TEST_SOURCES = \
    $$SRCDIR/page/dcpcategorycomponent.cpp \
    $$SRCDIR/page/pages.cpp \

# unit test and unit
SOURCES += \
    ut_dcpcategorycomponent.cpp \
    $$STUBSDIR/mapplicationpage-fake.cpp \
    $$STUBSDIR/mapplication-fake.cpp \
    $$STUBSDIR/mapplicationwindow-fake.cpp \
    $$STUBSDIR/mgridlayoutpolicy-fake.cpp \
    $$STUBSDIR/maintranslations-fake.cpp \
    $$STUBSDIR/mabstractlayoutpolicy-fake.cpp \
    $$STUBSDIR/mlayout-fake.cpp \
    $$STUBSDIR/mlinearlayoutpolicy-fake.cpp \
    $$STUBSDIR/mcontainer-fake.cpp \
    $$STUBSDIR/mgconfitem-fake.cpp \
    $$STUBSDIR/dcppage-fake.cpp \
    $$STUBSDIR/dcpcomponent-fake.cpp \
    $$STUBSDIR/dcpappletdb-fake.cpp \
    $$STUBSDIR/dcpappletmetadata-fake.cpp \
    $$STUBSDIR/dcpappletbuttons-fake.cpp \
    $$STUBSDIR/dcpappletplugin-fake.cpp \
    $$STUBSDIR/dcpretranslator-fake.cpp \
    $$STUBSDIR/dcpbriefcomponent-fake.cpp \
    $$STUBSDIR/dcpsinglecomponent-fake.cpp \
    $$STUBSDIR/dcpmaincategory-fake.cpp \
    $$TEST_SOURCES \ 

# base classes
SOURCES += \


# unit test and unit
HEADERS += \
    ut_dcpcategorycomponent.h \
    $$SRCDIR/page/dcpcategorycomponent.h \
    $$SRCDIR/page/dcppage.h \
    $$SRCDIR/page/pages.h \
    $$SRCDIR/page/dcpcategorycomponent.h \
    $$SRCDIR/component/dcpcomponent.h \
    $$SRCDIR/component/dcpmaincategory.h \
    $$SRCDIR/component/dcpbriefcomponent.h \
    $$SRCDIR/component/dcpsinglecomponent.h \
    $$SRCDIR/page/dcpappletbuttons.h \

# base classes
HEADERS += \


# service classes
HEADERS += \


