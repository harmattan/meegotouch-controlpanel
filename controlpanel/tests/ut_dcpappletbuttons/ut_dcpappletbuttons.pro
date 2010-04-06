include(../common_top.pri)

CONFIG += dui duicontrolpanel

INCLUDEPATH += $$system(find $$SRCDIR -type d)
INCLUDEPATH += $${LIBDCPINCLUDE}
APPLETDBINCLUDE = $${LIBDCPINCLUDE}/../appletdb
INCLUDEPATH += $${APPLETDBINCLUDE}
INCLUDEPATH += $${LIBDCPFAKES}
INCLUDEPATH += $${STUBSDIR}

TARGET = ut_dcpappletbuttons

TEST_SOURCES = \
    $$SRCDIR/page/dcpappletbuttons.cpp \
    $$SRCDIR/page/pages.cpp \
    $$SRCDIR/component/dcpcomponent.cpp \
    $$SRCDIR/component/dcpbriefcomponent.cpp \
    $$SRCDIR/component/dcpmaincategory.cpp \
    $$STUBSDIR/pagefactory-fake.cpp \
    $$STUBSDIR/dcppage-fake.cpp \
    $$STUBSDIR/duilayout-fake.cpp \
    $$STUBSDIR/qgraphicswidget-fake.cpp \

# unit test and unit
SOURCES += \
    ut_dcpappletbuttons.cpp \
    $$TEST_SOURCES \

# base classes
SOURCES += \


# unit test and unit
HEADERS += \
    ut_dcpappletbuttons.h \
    $$SRCDIR/page/dcpappletbuttons.h \
    $$SRCDIR/page/dcppage.h \
    $$SRCDIR/page/pagefactory.h \
    $$SRCDIR/component/dcpmaincategory.h \
    $$SRCDIR/component/dcpbriefcomponent.h \
    $$SRCDIR/component/dcpcomponent.h \

# base classes
HEADERS += \


# service classes
HEADERS += \


