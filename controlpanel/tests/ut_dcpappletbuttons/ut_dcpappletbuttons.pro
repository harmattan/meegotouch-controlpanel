include(../common_top.pri)

CONFIG += m mcontrolpanel

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

# unit test and unit
SOURCES += \
    ut_dcpappletbuttons.cpp \
    $$STUBSDIR/mgridlayoutpolicy-fake.cpp \
    $$STUBSDIR/maintranslations-fake.cpp \
    $$STUBSDIR/mabstractlayoutpolicy-fake.cpp \
    $$STUBSDIR/mlayout-fake.cpp \
    $$STUBSDIR/mlinearlayoutpolicy-fake.cpp \
    $$STUBSDIR/mgconfitem-fake.cpp \
    $$STUBSDIR/dcpappletdb-fake.cpp \
    $$STUBSDIR/dcpappletmetadata-fake.cpp \
    $$STUBSDIR/dcpappletplugin-fake.cpp \
    $$STUBSDIR/dcpretranslator-fake.cpp \
    $$STUBSDIR/dcpbriefcomponent-fake.cpp \
    $$TEST_SOURCES \

# base classes
SOURCES += \


# unit test and unit
HEADERS += \
    ut_dcpappletbuttons.h \
    $$STUBSDIR/mgconfitem_priv.h \
    $$SRCDIR/page/dcpappletbuttons.h \
    $$SRCDIR/component/dcpmaincategory.h \
    $$SRCDIR/component/dcpbriefcomponent.h \
    $$SRCDIR/component/dcpcomponent.h \

# base classes
HEADERS += \


# service classes
HEADERS += \


