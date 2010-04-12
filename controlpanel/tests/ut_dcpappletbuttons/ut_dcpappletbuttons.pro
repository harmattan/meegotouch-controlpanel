include(../common_top.pri)

CONFIG += dui duicontrolpanel

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
    $$SRCDIR/page/maintranslations.cpp \

# unit test and unit
SOURCES += \
    ut_dcpappletbuttons.cpp \
    $$STUBSDIR/duigridlayoutpolicy-fake.cpp \
    $$STUBSDIR/duiabstractlayoutpolicy-fake.cpp \
    $$STUBSDIR/duilayout-fake.cpp \
    $$STUBSDIR/duilinearlayoutpolicy-fake.cpp \
    $$STUBSDIR/duigconfitem-fake.cpp \
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
    $$STUBSDIR/duigconfitem_priv.h \
    $$SRCDIR/page/dcpappletbuttons.h \
    $$SRCDIR/component/dcpmaincategory.h \
    $$SRCDIR/component/dcpbriefcomponent.h \
    $$SRCDIR/component/dcpcomponent.h \

# base classes
HEADERS += \


# service classes
HEADERS += \


